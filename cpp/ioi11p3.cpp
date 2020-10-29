// ./ioi-11-p3-rice-hub.yml
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

int besthub(int N, int _L, int X[], long long B) {
    int ans = 0, l = 0, mid = 0;
    ll msum = 0;
    auto extend = [&] (int r) -> ll {
        ll cntL = mid - l + 1, cntR = r - mid;
        return msum + (cntL - cntR) * (X[mid + 1] - X[mid]);
    };
    auto optimizeMid = [&] (int r) {
        while (mid < r && extend(r) <= msum) {
            msum = extend(r);
            mid++;
        }
    };
    for (auto r = 0; r < N; r++) {
        msum += X[r] - X[mid];
        optimizeMid(r);
        while (msum > B) {
            if (mid == l) {
                msum = extend(r);
                mid++;
            }
            msum -= X[mid] - X[l++];
            optimizeMid(r);
        }
        maxa(ans, r - l + 1);
    }
    return ans;
}

#ifdef LOCAL
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N = 5, L = 20, B = 6;
    int X[5] = {1, 2, 10, 12, 14};
    cout<<"N="<<(N)<<", "; cout<<"L="<<(L)<<", "; cout<<"B="<<(B)<<", "; cout<<"X=["; for(int i=0; i<(5); i++)cout<<X[i]<<", "; cout<<"], ";cout << endl; // db N,L,B,A:5:X
    cout<<"besthub(N, L, X, B)="<<(besthub(N, L, X, B))<<", "; cout << endl; // db besthub(N, L, X, B)
    cout<<"[ans]: "; cout<<"3="<<(3)<<", "; cout << endl; // db l:ans,3

    return 0;
}
#endif