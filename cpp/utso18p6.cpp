// 1.yml
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

const int MN = 18, MHI = 9, MLO = MN - MHI, HISUB = 1 << MHI, LOSUB = 19683 + 1;
int N, Nsub, Q, lo, hi, loSub, hiSub,
    val[1 << MN];
ll dp[HISUB][LOSUB], tmp[MLO + 1][LOSUB];

int ternary[1 << MLO][1 << MLO], modOf[MLO][LOSUB];

void rebuild(int hiMsk) {
    int hiMskHi = hiMsk << lo;
    for (auto i = 0; i < (1 << lo); i++)
        tmp[0][ternary[i][0]] = val[i | hiMskHi];

    int cpow = 3, pre = 1;
    for (auto i = 1; i <= lo; i++) {
        for (auto j = 0; j < loSub; j++) {
            int maskMod = modOf[i - 1][j];
            tmp[i][j] = tmp[i - 1][j];
            if (maskMod == 2) tmp[i][j] += tmp[i - 1][j - pre] + tmp[i - 1][j - 2 * pre];
        }
        pre = cpow;
        cpow *= 3;
    }
    for (auto i = 0; i < loSub; i++)
        dp[hiMsk][i] = tmp[lo][i];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (Q);
    Nsub = 1 << N;
    for (auto i = 0; i < Nsub; i++)
        cin >> (val[i]);

    lo = N / 2; loSub = 1;
    for (auto i = 0; i < lo; i++) loSub *= 3;
    hi = N - lo; hiSub = 1 << hi;

    // build and preprocess
    for (auto i = 0; i < (1 << lo); i++) {
        int pow3 = 1;
        for (auto j = 0; j < lo; j++) {
            ternary[i][0] += pow3 * ((i >> j) & 1);
            pow3 *= 3;
        }

        for (auto j = 1; j < (1 << lo); j++) {
            int tt = ternary[i][0], cpow = 1;
            for (auto k = 0; k < lo; k++) {
                if ((j >> k) & 1)
                    tt += cpow * (2 - ((i >> k) & 1));
                cpow *= 3;
            }
            ternary[i][j] = tt;
        }
    }
    for (auto i = 0; i < loSub; i++) {
        int cpow = 3, pre = 1;
        for (auto j = 0; j < lo; j++) {
            modOf[j][i] = (i % cpow - i % pre) / pre;
            pre = cpow;
            cpow *= 3;
        }
    }
    for (auto i = 0; i < hiSub; i++)
        rebuild(i);

    // query
    while (Q--) {
        int T, a, b;
        cin >> T >> a >> b;
        if (T == 1) {
            int dif = b - val[a];
            val[a] = b;
            
            int hiMsk = a >> lo, loMsk = a & ((1 << lo) - 1);
            for (auto i = 0; i < (1 << lo); i++) {
                dp[hiMsk][ternary[loMsk][i]] += dif; }
        }
        else {
            ll ans = 0;
            if ((b & a) == a) {
                int loA = a & ((1 << lo) - 1), loB = b & ((1 << lo) - 1), hiA = a >> lo, hiB = b >> lo;

                int cpow = 1, loMsk = 0;
                for (auto i = 0; i < lo; i++) {
                    int bitA = (loA >> i) & 1, bitB = (loB >> i) & 1,
                        bitVal = bitA == bitB ? bitA : 2; // assume bitA < bitB
                    loMsk += cpow * bitVal;
                    cpow *= 3;
                }

                for (auto i = 0; i < hiSub; i++) {
                    if ((i & hiA) == hiA && (i & hiB) == i)
                        ans += dp[i][loMsk];
                }
            }

            cout << (ans) << '\n';
        }
    }

    return 0;
}