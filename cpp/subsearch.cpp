// ./subarray-search.yml
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
#ifdef __GNUG__
// PBDS order statistic tree
#include <ext/pb_ds/assoc_container.hpp> // Common file 
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds; 
template <typename T, class comp = less<T>> using os_tree = tree<T, null_type, comp, rb_tree_tag, tree_order_statistics_node_update>;
template <typename K, typename V, class comp = less<K>> using treemap = tree<K, V, comp, rb_tree_tag, tree_order_statistics_node_update>;
// HashSet
#include <ext/pb_ds/assoc_container.hpp>
template <typename T, class Hash> using hashset = gp_hash_table<T, null_type, Hash>;
template <typename K, typename V, class Hash> using hashmap = gp_hash_table<K, V, Hash>;
const ll RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash { ll operator()(ll x) const { return x ^ RANDOM; } };
#endif
// More utilities
int SZ(string &v) { return v.length(); }
template <typename C> int SZ(C &v) { return v.size(); }
template <typename C> void UNIQUE(vector<C> &v) { sort(v.begin(), v.end()); v.resize(unique(v.begin(), v.end()) - v.begin()); }
template <typename T, typename U> void maxa(T &a, U b) { a = max(a, b); }
template <typename T, typename U> void mina(T &a, U b) { a = min(a, b); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MOD = 1e9+7, MN = 1e5 + 1;
int N, F,
    fre[MN];
ll S,
   A[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> F >> S;
    for (auto i = 0; i < N; i++)
        cin >> A[i];

    int r = 0;
    ll csum = 0, cntS = 0, cntF = 0, cntFS = 0;
    for (auto l = 0; l < N; l++){
        while (r < N && csum+A[r] <= S) {
            csum += A[r];
            r++;
        }
        cntS += r-l;
        csum -= A[l];
        // cout<<"[S]: "; cout<<"l="<<(l)<<", "; cout<<"r="<<(r)<<", "; cout << endl; // db l:S,l,r
    }

    r = 0;
    for (auto l = 0; l < N; l++) {
        while (r < N && fre[A[r]]+1 <= F) {
            fre[A[r]]++;
            r++;
        }
        cntF += r-l;
        fre[A[l]]--;
        // cout<<"[F]: "; cout<<"l="<<(l)<<", "; cout<<"r="<<(r)<<", "; cout << endl; // db l:F,l,r
    }
    memset(fre, 0, sizeof fre);

    csum = r = 0;
    for (auto l = 0; l < N; l++) {
        while (r < N && fre[A[r]]+1 <= F && csum+A[r] <= S) {
            fre[A[r]]++;
            csum += A[r];
            r++;
        }
        cntFS += r-l;
        fre[A[l]]--;
        csum -= A[l];
        // cout<<"[FS]: "; cout<<"l="<<(l)<<", "; cout<<"r="<<(r)<<", "; cout << endl; // db l:FS,l,r
    }

    // cout<<"cntS="<<(cntS)<<", "; cout<<"cntF="<<(cntF)<<", "; cout<<"cntFS="<<(cntFS)<<", "; cout << endl; // db cntS,cntF,cntFS

    // cntS -= cntFS;
    // cntF -= cntFS;
    cntS %= MOD;
    cntF %= MOD;
    cntFS %= MOD;
    ll ans = (cntS*cntF%MOD)*cntFS%MOD;
    cout << (ans) << '\n';

    return 0;
}