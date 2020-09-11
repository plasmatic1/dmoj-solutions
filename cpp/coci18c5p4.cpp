// ./coci-18-contest-5-4-parametriziran.yml
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

const int MN = 5e4 + 1, MM = 6, MSUB = 1 << MM;
int N, M,
    vmsk[MN];
ll mhsh[MN][MSUB];
string ss[MN];
map<ll, int> cnt[MSUB];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (M);
    int msub = 1 << M, mmsk = msub - 1;
    for (auto i = 0; i < N; i++) {
        cin >> (ss[i]);
        for (auto j = 0; j < M; j++)
            if (ss[i][j] == '?')
                vmsk[i] |= 1 << j;
        for (auto j = 0; j < msub; j++) {
            for (auto k = 0; k < M; k++)
                if (((j >> k) & 1) && ss[i][k] != '?')
                mhsh[i][j] = mhsh[i][j] * 27LL + (ss[i][k] - 'a' + 1);
        }
    }
    
    ll ans = 0;
    for (int canMsk = 0; canMsk < msub; canMsk++) {
        for (auto i = 0; i < msub; i++)
            cnt[i].clear();
        for (auto i = 0; i < N; i++) {
            int need = (vmsk[i] | canMsk) ^ mmsk;
            ans += cnt[need][mhsh[i][need]];
            if (vmsk[i] == canMsk)
                for (auto j = 0; j < msub; j++)
                    if ((vmsk[i] & (j ^ mmsk)) == vmsk[i])
                        cnt[j][mhsh[i][j]]++;
        }
    }
    
    cout << (ans) << '\n';

    return 0;
}