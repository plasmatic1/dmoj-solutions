// ./cco-16-p2-splitting-hares.yml
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

using tri = pair<pii, int>;

ostream& operator<<(ostream& out, const pii o) {
    out << "(fs=" << o.fs << ", sn=" << o.sn << ")";
    return out;
}
ostream& operator<<(ostream& out, const tri o) {
    out << "(fs=" << o.fs << ", sn=" << o.sn << ")";
    return out;
}

const int MN = 4001;
int N,
    W[MN];
pii pos[MN];

ll cross(const pii &a, const pii &b) {
    return (ll)a.fs * b.sn - (ll)a.sn * b.fs;
}

bool cmpTri(const tri &a, const tri &b) {
    bool za = a.fs < mpr(0, 0), zb = b.fs < mpr(0, 0);
    if (za != zb) return za < zb;
    return cross(a.fs, b.fs) < 0LL;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N);
    for (auto i = 0; i < N; i++)
        cin >> (pos[i].fs) >> (pos[i].sn) >> (W[i]);

    // Get ans
    int ans = -INF;
    for (auto i = 0; i < N; i++) {
        // Make and sort pre-existing vectors
        vector<tri> pts;
        for (auto j = 0; j < N; j++) {
            if (i == j) continue;
            pts.eb(mpr(pos[j].fs - pos[i].fs, pos[j].sn - pos[i].sn), W[j]);
        }
        sort(all(pts), cmpTri);

        // Insert new vectors to allow for lines that aren't constructed
        vector<tri> nv;
        for (auto j = 0; j < N - 1; j++) {
            auto &p1 = pts[j].fs;
            int dx = p1.sn >= 0 ? 1 : -1, dy = p1.fs <= 0 ? 1 : -1; // Determine whether x and y should be increased to increase the angle based on quadrant
            nv.eb(mpr(p1.fs * 1000 + dx, p1.sn * 1000 + dy), 0); // Given that coordinates max out at +-1e6, this new vector is definitely between vectors
        }
        pts.insert(pts.end(), all(nv));
        sort(all(pts), cmpTri);

        // Angular linesweep
        int sz = SZ(pts), r = 0, csum = W[i];
        for (auto l = 0; l < sz; l++) {
            while (r < sz + l && cross(pts[l].fs, pts[r % sz].fs) <= 0LL) {
                csum += pts[r % sz].sn;
                r++;
            }
            maxa(ans, csum);
            csum -= pts[l].sn;
        }
    }

    cout << (ans) << '\n';

    return 0;
}