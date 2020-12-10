// ./ioi-19-p3-rectangles.yml
#include "bits/stdc++.h"
using namespace std;

// Defines
#define fs first
#define sn second
#define pb push_back
#define eb emplace_back
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
int SZ(string &v) { return v.length(); }
template <typename C> int SZ(C &v) { return v.size(); }
template <typename C> void UNIQUE(vector<C> &v) { sort(v.begin(), v.end()); v.resize(unique(v.begin(), v.end()) - v.begin()); }
template <typename T, typename U> void maxa(T &a, U b) { a = max(a, b); }
template <typename T, typename U> void mina(T &a, U b) { a = min(a, b); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

// i love hugs <3

struct rect {
    short type, a, c, d; // type=0->horizontal, type=1->vertical
    bool operator<(const rect &o) const { 
        return a == o.a ? type > o.type : a < o.a;
    }
};
ostream& operator<<(ostream& out, const rect o) {
    out << "(type=" << o.type << ", a=" << o.a << ", c=" << o.c << ", d=" << o.d << ")";
    return out;
}

const int MN = 2501;
int N, M;
vector<vector<int>> val;
vector<short> hor[MN][MN], ver[MN][MN];
vector<rect> byb[MN];

// BIT along rows
struct { // cache locality please
    int val; short qid;
} bit[MN][MN];
short cqid = 0;
void reset() { cqid++; }
void poopoohead(int x, int y) { 
    if (bit[x][y].qid != cqid)
        bit[x][y] = {0, cqid};
}
void add(int r, int c) {
    for (; c < MN; c += c & -c) {
        poopoohead(r, c); // (:
        bit[r][c].val++;
    }
}
int sum(int r, int c) {
    int sum = 0;
    for (; c; c -= c & -c) {
        poopoohead(r, c); // (:
        sum += bit[r][c].val;
    }
    return sum;
}

long long count_rectangles(std::vector<std::vector<int>> _a) {
    val = _a;
    N = SZ(_a);
    M = SZ(_a[0]);

    // get ranges
    for (auto i = 0; i < N; i++) {
        vector<int> stk;
        for (auto j = 0; j < M; j++) {
            int pre = -1;
            for (auto it = stk.rbegin(); it != stk.rend(); it++) {
                if (pre >= val[i][j]) break;
                if (j - *it > 1)
                    hor[*it][j].pb(i);
                pre = val[i][*it];
            }
            while (!stk.empty() && val[i][stk.back()] <= val[i][j])
                stk.pop_back();
            stk.pb(j);
        }
    }
    for (auto i = 0; i < M; i++) {
        vector<int> stk;
        for (auto j = 0; j < N; j++) {
            int pre = -1;
            for (auto it = stk.rbegin(); it != stk.rend(); it++) {
                if (pre >= val[j][i]) break;
                if (j - *it > 1)
                    ver[*it][j].pb(i);
                pre = val[*it][i];
            }
            while (!stk.empty() && val[stk.back()][i] <= val[j][i])
                stk.pop_back();
            stk.pb(j);
        }
    }

    // build queries
    for (auto i = 0; i < M; i++) {
        for (auto j = i+2; j < M; j++) {
            sort(all(hor[i][j]));
            int pre = -INF, lb = -INF;
            for (auto ypos : hor[i][j]) {
                if (ypos > pre + 1)
                    lb = ypos;

                // rect a=i, b=j, c=lb, d=ypos (x-positions are [a,b], y-positions are [c,d])
                // squish x-range [a,b] by 1 as we want hatching pattern not square
                byb[j-1].pb({0, (short)(i+1), (short)lb, ypos});
                pre = ypos;
            }
        }
    }
    for (auto i = 0; i < N; i++) {
        for (auto j = i+2; j < N; j++) {
            sort(all(ver[i][j]));
            int pre = -INF, lb = -INF;
            for (auto xpos : ver[i][j]) {
                if (xpos > pre + 1)
                    lb = xpos;

                // rect a=lb, b=xpos, c=i, d=j (x-positions are [a,b], y-positions are [c,d])
                // squish y-range [c,d] by 1 as we want hatching pattern not square
                byb[xpos].pb({1, (short)lb, (short)(i+1), (short)(j-1)});
                pre = xpos;
            }
        }
    }

    // get ans
    ll ans = 0;
    for (auto i = 0; i < M; i++) {
        reset();
        sort(all(byb[i]));
        for (auto r : byb[i]) {
            r.c++; r.d++; // make 1-indexed
            if (r.type == 0) ans += sum(r.d, MN-1) - sum(r.d, r.c-1);
            else add(r.d, r.c);
        }
    }

    return ans;
}

#ifdef LOCAL
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N >> M;
    vector<vector<int>> a(N, vector<int>(M));
    for (auto i = 0; i < N; i++)
        for (auto j = 0; j < M; j++)
            cin >> (a[i][j]);
    ll ans = count_rectangles(a);
    cout << (ans) << '\n';

    return 0;
}
#endif