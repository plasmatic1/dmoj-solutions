// ./coci-13-contest-2-3-slom.yml
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

const int MN = 1001;
int N, X,
    P[MN], Q[MN];
string s, ans;

void mul(int P[MN], int Q[MN], int R[MN]) { // R(x) = P(Q(x))
    for (auto i = 0; i < N; i++)
        R[i] = P[Q[i]];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (X) >> (s);
    N = SZ(s);

    for (int i = 0, ctr = 0; i < N; i += 2, ctr++)
        P[i] = ctr;
    for (int i = 1, ctr = N - 1; i < N; i += 2, ctr--)
        P[i] = ctr;
    int res[MN]; iota(res, res + N, 0);
    for (auto i = 0; i < 31; i++) {
        if ((X >> i) & 1) {
            int tmp[MN];
            mul(P, res, tmp);
            copy(tmp, tmp + N, res);
        }
        int tmp[MN];
        mul(P, P, tmp);
        copy(tmp, tmp + N, P);
    }
    ans = string(N, '0');
    for (auto i = 0; i < N; i++)
        ans[res[i]] = s[i];
    cout << (ans) << '\n';

    return 0;
}