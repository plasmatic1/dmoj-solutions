// ./baltic-oi-18-p5-genetics.yml
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
template <typename T, typename U> void maxa(T &a, U b) { a = max(a, b); }
template <typename T, typename U> void mina(T &a, U b) { a = min(a, b); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 4101;
int N, M, K, CMP[256];
char val[MN][MN];
ull cnt[MN][4], WN[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for (auto i = 0; i < 4; i++)
        CMP["ACGT"[i]] = i;

    cin >> (N) >> (M) >> (K);

    mt19937_64 mt(RANDOM);
    uniform_int_distribution<ull> dis(0ULL, 100000000000ULL);
    // uniform_int_distribution<ull> dis(0ULL, 10ULL);
    ull rsum = 0;
    for (auto i = 1; i <= N; i++) {
        string tmp;
        cin >> tmp;
        for (auto j = 1; j <= M; j++)
            val[i][j] = CMP[tmp[j - 1]];
        rsum += (WN[i] = dis(mt));
    }

    for (auto i = 1; i <= M; i++) {
        for (auto j = 0; j < 4; j++) {
            for (auto k = 1; k <= N; k++) {
                // psum[i][j][k] = psum[i][j][k - 1] + (val[k][i] == j); 
                if (val[k][i] == j)
                    cnt[i][j] += WN[k];
            } } }

    for (auto i = 1; i <= N; i++) {
        ull hsh = 0;
        for (auto j = 1; j <= M; j++) {
            hsh += cnt[j][val[i][j]] - WN[i];
            // cout<<"i="<<(i)<<", "; cout<<"j="<<(j)<<", "; cout<<"cnt[j][val[i][j]]="<<(cnt[j][val[i][j]])<<", "; cout<<"WN[i]="<<(WN[i])<<", "; cout << endl; // db i,j,cnt[j][val[i][j]], WN[i]
        }

        // cout<<"i="<<(i)<<", "; cout<<"hsh="<<(hsh)<<", "; cout<<"WN[i]="<<(WN[i])<<", "; cout << endl; // db i,hsh,WN[i]
        if (hsh == (rsum - WN[i]) * (M - K)) {
            cout << (i) << '\n';
            return 0;
        }
    }

    assert(0);

    return 0;
}