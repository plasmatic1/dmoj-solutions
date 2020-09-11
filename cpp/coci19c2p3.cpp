// ./coci-19-contest-2-3-checker.yml
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

void die() {
    cout << ("neispravna triangulacija") << '\n';
    exit(0);
}
void invalid() {
    cout << ("neispravno bojenje") << '\n';
    exit(0);
}

using ed = pair<pii, int>;
ostream& operator<<(ostream& out, const pii o) {
    out << "(fs=" << o.fs << ", sn=" << o.sn << ")";
    return out;
}
ostream& operator<<(ostream& out, const ed o) {
    out << "(fs=" << o.fs << ", sn=" << o.sn << ")";
    return out;
}

const int MN = 2e5 + 1;
int N, subtask,
    val[MN], deg[MN];
set<pii> out;
priority_queue<pair<int, ed>> pq;

int succ(int x, int times = 1) {
    auto ptr = out.lower_bound(mpr(x, -INF));
    while (times--) {
        ptr++;
        if (ptr == out.end()) ptr = out.begin();
    }
    return ptr->fs;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // input
    cin >> (subtask) >> (N);
    string buf;
    cin >> buf;
    for (auto i = 1; i <= N; i++) {
        val[i] = buf[i - 1] - '1';
        out.emplace(i, val[i]);
    }
    for (auto i = 0; i < N-3; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        if (a > b) swap(a, b);
        c--;

        deg[a]++; deg[b]++;
        int dis = min(b - a, (N - b + 1) + (a - 1));
        pq.emplace(-dis, mpr(mpr(a, b), c)); // priority queue is a max queue, so we multiply by -1 to make it a min queue
    }

    // do a search
    vector<tuple<int, int, int>> tris;
    while (!pq.empty()) {
        auto c = pq.top().sn; pq.pop();
        auto &vs = c.fs;
        
        // Get edge colours and middle node
        int clr[2], mid = -1;
        if (succ(vs.fs, 2) != vs.sn) swap(vs.fs, vs.sn);
        auto ptr = out.lower_bound(mpr(vs.fs, -INF));
        for (auto i = 0; i < 2; i++) {
            if (i == 1) mid = ptr->fs;
            clr[i] = ptr->sn;
            ptr++;
            if (ptr == out.end()) ptr = out.begin();
        }

        // add new triangle
        if (deg[mid]) die();
        tris.eb(clr[0], clr[1], c.sn);

        // update data structures
        ptr = out.lower_bound(mpr(mid, -INF)); out.erase(ptr); 
        ptr = out.lower_bound(mpr(vs.fs, -INF)); out.erase(ptr);
        out.emplace(vs.fs, c.sn);
        deg[vs.fs]--; deg[vs.sn]--;

        // cout<<"[rem tri]: "; cout<<"vs="<<(vs)<<", "; cout<<"mid="<<(mid)<<", "; cout<<"clr[0]="<<(clr[0])<<", "; cout<<"clr[1]="<<(clr[1])<<", "; cout<<"c.sn="<<(c.sn)<<", "; cout << endl; // db l:rem tri,vs,mid,clr[0],clr[1],c.sn
    }

    // last triangle
    vector<pii> tmp(all(out));
    assert(SZ(tmp) == 3);
    tris.eb(tmp[0].sn, tmp[1].sn, tmp[2].sn);

    // check triangles
    assert(SZ(tris) == N-2);
    for (auto &c : tris) {
        vector<int> v{get<0>(c), get<1>(c), get<2>(c)};
        sort(all(v));
        for (auto i = 0; i < 3; i++)
            if (i != v[i])
                invalid();
    }
    cout << ("tocno") << '\n';

    return 0;
}