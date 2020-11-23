// ./cco-02-p4-duathlon.yml
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

struct line {
    ld m, b;
    ld eval(ld x) {
        return x * m + b;
    }
};

const int MN = 20;
ld T,
   rs[MN], cs[MN];
line ls[MN];
int N;

ld check(ld rv) {
    ld minv = numeric_limits<ld>::infinity();
    for (auto i = 0; i < N-1; i++)
        mina(minv, ls[i].eval(rv));
    return minv - ls[N - 1].eval(rv);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (T) >> (N);
    for (auto i = 0; i < N; i++)
        cin >> (rs[i]) >> (cs[i]);
    for (auto i = 0; i < N; i++) {
        ls[i] = {1 / rs[i] - 1 / cs[i], T / cs[i]};
    }

    ld best = -LLINF, bestr = -1;
    for (auto i = 0; i < N-1; i++) {
        for (auto j = 0; j < N-1; j++) {
            auto a = ls[i], b = ls[j];
            if (a.m != b.m) {
                ld r = (b.b - a.b) / (a.m - b.m);
                ld alt = check(r);
                if (alt > best) {
                    best = alt;
                    bestr = r;
                }
            }
        }
    }

    ld alt = check(0);
    if (alt > best) {
        best = alt;
        bestr = 0;
    }
    alt = check(T);
    if (alt > best) {
        best = alt;
        bestr = T;
    }

    if (best < 0)
        printf("The cheater cannot win.\n");
    else {
        printf("The cheater can win by %d seconds with r = %.2fkm and k = %.2fkm.\n", (int)round(60 * 60 * best), (double)bestr, (double)(T - bestr));
    }

    return 0;
}