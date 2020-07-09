// coci-19-contest-5-3-matching.yml
#include "bits/stdc++.h"
using namespace std;

// Defines
#define pb push_back
#define mpr make_pair
#define mtp make_tuple
#define all(x) (x).begin(), (x).end()
// Basic type definitions
using ll = long long; using ull = unsigned long long; using ld = long double;
using pii = pair<int, int>; using pll = pair<long long, long long>;
// PBDS order statistic tree
#include <ext/pb_ds/assoc_container.hpp> // Common file 
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds; 
template <typename T, class comp = less<T>> using os_tree = tree<T, null_type, comp, rb_tree_tag, tree_order_statistics_node_update>;
template <typename K, typename V, class comp = less<K>> using treemap = tree<K, V, comp, rb_tree_tag, tree_order_statistics_node_update>;
// HashSet
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
const ll RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash { ll operator()(ll x) const { return x ^ RANDOM; } };
template <typename T, class Hash> using hashset = gp_hash_table<T, null_type, Hash>;
template <typename K, typename V, class Hash> using hashmap = gp_hash_table<K, V, Hash>;
// More utilities
template <typename C> int SZ(C &v) { return v.size(); }
template <typename T, typename U> void maxa(T &a, U b) { a = max(a, b); }
template <typename T, typename U> void mina(T &a, U b) { a = min(a, b); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

struct Pt {
    int x, y;
};

istream& operator>>(istream &in, Pt &o) {
    in >> o.x >> o.y;
    return in;
}

const int MN = 1e5 + 1;
int N;
Pt pts[MN];

vector<int> g[MN];
int onX[MN][2], onY[MN][2];
vector<pii> ans;

int fst(int x[2]) {
    return x[0] != -1;
}

// segtree
#define MID int mid = (l + r) / 2, lhs = i + 1, rhs = i + (mid - l + 1) * 2; 
struct Segt {
    int n;
    set<int> seg[MN * 2];
    void _chLine(int ql, int qr, int y, bool add, int i, int l, int r) {
        if (l > qr || r < ql) return;
        if (l >= ql && r <= qr) {
            if (add) seg[i].insert(y); else seg[i].erase(y);
            return; }
        MID;
        _chLine(ql, qr, y, add, lhs, l, mid); _chLine(ql, qr, y, add, rhs, mid + 1, r);
    }
    void chLine(int a, int b, int c, bool ch) { _chLine(min(a, b), max(a, b), c, ch, 1, 1, n); }
    int _get(int q, int yl, int yr, int i, int l, int r) {
        MID;
        auto ptr = seg[i].lower_bound(yl);
        int res = ptr != seg[i].end() && *ptr <= yr ? *ptr : INF;
        if (l == q && q == r) return res;
        if (q <= mid) return min(res, _get(q, yl, yr, lhs, l, mid));
        else return min(res, _get(q, yl, yr, rhs, mid + 1, r));
    }
    int get(int q, int yl, int yr) { return _get(q, min(yl, yr), max(yl, yr), 1, 1, n); }
    void init(int n0) { n = n0; }
};
Segt hor, ver;

void chLine(int i, int j, bool add) {
    if (pts[i].x == pts[j].x) { // vertical
        ver.chLine(pts[i].y, pts[j].y, pts[i].x, add); }
    else {
        hor.chLine(pts[i].x, pts[j].x, pts[i].y, add); }
}

int getInter(int i, int j) {
    if (pts[i].x == pts[j].x) { // vertical
        return hor.get(pts[i].x, pts[i].y, pts[j].y); }
    else {
        return ver.get(pts[i].y, pts[i].x, pts[j].x); }
}

void orient(vector<int> &cycle, int ori, bool add) {
    int h = SZ(cycle) / 2;
    for (auto i = 0; i < h; i++) {
        int cur = (ori + 2 * i) % SZ(cycle), nxt = (cur + 1) % SZ(cycle);
        chLine(cycle[cur], cycle[nxt], add);
    }
}

// detection stuff
#define DIE cout << "NE" << '\n'; \
    exit(0);

vector<int> found;
vector<vector<int>> paths, cycles;
bool vis[MN], isCyc[MN], cycDone[MN];
int cycId[MN], idInCyc[MN];
queue<pii> nxt;

void officialOrientLine(int a, int b) {
    int inter = getInter(a, b);
    while (inter != INF) {
        bool ver = pts[a].x == pts[b].x;
        int id = ver ? onY[inter][0] : onX[inter][0];
        if (!isCyc[id]) { DIE; }
        else {
            if (cycDone[cycId[id]]) { DIE; }

            auto &cycle = cycles[cycId[id]];
            int sz = SZ(cycle), cycCur = cycle[idInCyc[id]], cycNxt = cycle[(idInCyc[id] + 1) % sz],
                badStart = ((pts[cycCur].x == pts[cycNxt].x) == ver) ^ (idInCyc[id] & 1);

            orient(cycle, badStart, false); // remove
            nxt.emplace(cycId[id], badStart ^ 1);
        }

        inter = getInter(a, b);
    }
}

void dfs(int c) {
    if (vis[c]) return;
    vis[c] = true;
    found.pb(c);
    for (int to : g[c])
        dfs(to);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    memset(onX, -1, sizeof onX);
    memset(onY, -1, sizeof onY);

    cin >> (N);
    for (auto i = 1; i <= N; i++) {
        cin >> (pts[i]);
        onX[pts[i].x][fst(onX[pts[i].x])] = i;
        onY[pts[i].y][fst(onY[pts[i].y])] = i;
    }

    // build graph
    for (auto i = 1; i < MN; i++) {
        if (onX[i][0] != -1 && onX[i][1] != -1) {
            g[onX[i][0]].pb(onX[i][1]); g[onX[i][1]].pb(onX[i][0]); }
        if (onY[i][0] != -1 && onY[i][1] != -1) {
            g[onY[i][0]].pb(onY[i][1]); g[onY[i][1]].pb(onY[i][0]); }
    }

    // discriminate cycles from paths
    hor.init(MN - 1); ver.init(MN - 1);
    for (auto i = 1; i <= N; i++) {
        if (!vis[i]) {
            found.clear();
            dfs(i);

            bool cyc = true;
            for (auto x : found)
                cyc &= SZ(g[x]) == 2;
            for (auto x : found)
                isCyc[x] = cyc;
            if (cyc) cycles.pb(found);
            else {
                int st = -1;
                for (auto x : found) {
                    if (SZ(g[x]) & 1) st = x;
                    vis[x] = false;
                }
                found.clear();
                dfs(st);
                paths.pb(found);
            }
        }
    }

    // start queue stuff
    int cid = 0;
    for (auto &cycle : cycles) {
        orient(cycle, 0, true); orient(cycle, 1, true);
        for (auto i = 0; i < SZ(cycle); i++) {
            idInCyc[cycle[i]] = i;
            cycId[cycle[i]] = cid;
        }
        cid++;
    }

    for (auto &path : paths) {
        if (SZ(path) & 1) {
            cout << ("NE") << '\n';
            return 0;
        }

        for (int i = 0; i < SZ(path); i += 2) {
            officialOrientLine(path[i], path[i + 1]);
            chLine(path[i], path[i + 1], true);
            ans.emplace_back(path[i], path[i + 1]);
        }
    }

    while (!nxt.empty()) {
        auto c = nxt.front(); nxt.pop();
        if (cycDone[c.first]) continue;
        cycDone[c.first] = true;
        auto &cycle = cycles[c.first];
        int sz = SZ(cycle);

        for (int i = 0; i < sz / 2; i++) {
            int cur = (c.second + 2 * i) % sz, nxt = (cur + 1) % sz;
            officialOrientLine(cycle[cur], cycle[nxt]);
            ans.emplace_back(cycle[cur], cycle[nxt]);
        }
    }

    // just do vertical lol
    for (auto i = 0; i < SZ(cycles); i++) {
        if (!cycDone[i]) {
            bool off = pts[cycles[i][0]].x != pts[cycles[i][1]].x;
            int sz = SZ(cycles[i]);
            auto &cycle = cycles[i];

            for (int j = 0; j < sz / 2; j++) {
                int cur = (off + 2 * j) % sz, nxt = (cur + 1) % sz;
                ans.emplace_back(cycle[cur], cycle[nxt]);
            }
        }
    }
    
    // print ans
    cout << ("DA") << '\n';
    for (auto p : ans)
        cout << (p.first) << ' ' << (p.second) << '\n';

    return 0;
}