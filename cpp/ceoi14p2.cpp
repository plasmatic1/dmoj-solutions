// ceoi-14-p2-fangorn.yml
#include "bits/stdc++.h"
using namespace std;

// Defines
#define pb push_back
#define fs first
#define sn second
#define mpr make_pair
#define mtp make_tuple
#define all(x) (x).begin(), (x).end()
// Basic type definitions
using ll = long long; using ull = unsigned long long;
using pii = pair<int, int>; using pll = pair<long, long>;
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
template <typename C> int sz(C &v) { return v.size(); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

ostream& operator<<(ostream& out, const pair<double, int> o) {
    out << "(first=" << o.first << ", second=" << o.second << ")";
    return out;
}

struct Pt {
    int x, y;
    Pt neg() { return {-x, -y}; }
};

istream& operator>>(istream &in, Pt &o) {
    in >> o.x >> o.y;
    return in;
}

const int MN = 2001, MC = 10001;
int W, H, C, N;
Pt st,
   camps[MC], trees[MN];
double regStart[MN], regEnd[MN];

double getAng(Pt &center, const Pt out) {
    return atan2(out.y - center.y, out.x - center.x); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (W) >> (H) >> (st) >> (C);
    for (auto i = 0; i < C; i++)
        cin >> (camps[i]);
    cin >> (N);
    for (auto i = 0; i < N; i++)
        cin >> (trees[i]);

    for (auto i = 0; i < N; i++) {
        vector<pair<double, int>> ptsAng;
        for (auto j = 0; j < N; j++) {
            if (j == i) continue;
            ptsAng.emplace_back(atan2(trees[i].y - trees[j].y, trees[i].x - trees[j].x), j); // note the A.x - B.x rather than B.x - A.x (this is intentional)
        }
        ptsAng.emplace_back(getAng(trees[i], st), -1);
        sort(all(ptsAng));

        int ind = -1;
        for (auto j = 0; j < sz(ptsAng); j++) {
            if (ptsAng[j].second == -1) {
                ind = j;
                break;
            }
        }

        regStart[i] = ptsAng[(ind + 1) % sz(ptsAng)].first;
        regEnd[i] = ptsAng[(ind - 1 + sz(ptsAng)) % sz(ptsAng)].first;

        // cout << "i=" << (i) << ", "; cout << "regStart[i]=" << (regStart[i]) << ", "; cout << "regEnd[i]=" << (regEnd[i]) << ", "; cout << endl; // db i,regStart[i],regEnd[i]
        // cout << "ptsAng=["; for (auto x : ptsAng) cout << x << ", "; cout << "], "; cout << endl; // db I:ptsAng
    }

    vector<int> ans;
    for (auto i = 0; i < C; i++) {
        bool good = true;
        for (auto j = 0; j < N; j++) {
            double ang = getAng(trees[j], camps[i]);
            double angles[3] = {ang, regStart[j], regEnd[j]};
            sort(angles, angles + 3);

            // cout << "i=" << (i) << ", "; cout << "j=" << (j) << ", "; cout << "ang=" << (ang) << ", "; cout << "regStart[j]=" << (regStart[j]) << ", "; cout << "regEnd[j]=" << (regEnd[j]) << ", "; cout << endl; // db i,j,ang,regStart[j],regEnd[j]

            int ind = -1;
            for (auto k = 0; k < 3; k++) {
                if (angles[k] == ang) {
                    ind = k;
                    break;
                }
            }

            if (angles[(ind + 1) % 3] != regStart[j] || angles[(ind + 2) % 3] != regEnd[j]) {
                good = false;
                // cout << "[bad]: "; cout << endl; // db l:bad
                break;
            }
        }
        if (good)
            ans.pb(i);
    }

    cout << (sz(ans)) << '\n';
    for (auto x : ans)
        cout << (x + 1) << ' ';
    cout << '\n';

    return 0;
}