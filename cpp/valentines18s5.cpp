// valentines-day-18-s5-carols-calculating-continuity.yml
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

ostream& operator<<(ostream& out, const pii o) {
    out << "(first=" << o.first << ", second=" << o.second << ")";
    return out;
}

const int MN = 1e6 + 1, MV = 1e5 + 1;
int N, K, 
    val[MN];

int pfcnt[MV];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Precalc Carol numbers
    for (auto i = 1; i < MV; i++) {
        int cur = i;
        for (int j = 2; j * j <= cur; j++) {
            while (cur % j == 0) {
                cur /= j;
                pfcnt[i]++;
            }
        }
        if (cur > 1) pfcnt[i]++;
    }

    // Input
    cin >> (N) >> (K);
    for (auto i = 0; i < N; i++) {
        cin >> (val[i]); }

    // Compute answer
    // Basic idea: GCD can only change at most log(N) times
    ll ans = pfcnt[val[0]] == K;
    vector<pii> fchange; fchange.emplace_back(0, val[0]);
    for (auto i = 1; i < N; i++) {
        for (auto &p : fchange)
            p.second = __gcd(p.second, val[i]);
        fchange.emplace_back(i, val[i]);

        // Do a custom std::unique (I want to preserve the pair with the greatest index for each value
        vector<pii> tmp;
        int pre = -1;
        for (auto it = fchange.rbegin(); it != fchange.rend(); it++) {
            if (it->second != pre) {
                tmp.pb(*it);
                pre = it->second;
            }
        }
        reverse(all(tmp));
        tmp.swap(fchange);

        // Add to current answer
        pre = -1;
        for (auto x : fchange) {
            if (pfcnt[x.second] == K)
                ans += x.first - pre;
            pre = x.first;
        }
    }

    cout << (ans) << '\n';

    return 0;
}