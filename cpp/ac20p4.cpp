// ./appleby-contest-20-p4-philosophy-class.yml
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

bool cmp(const vector<int> a, const vector<int> b) {
    if (SZ(a) != SZ(b)) return SZ(a) < SZ(b);
    for (auto i = 0; i < SZ(a); i++) {
        if (a[i] < b[i])
            return true;
        else if (a[i] > b[i])
            return false;
    }
    return false;
}

const int MN = 3001;
int N, M,
    A[MN], B[MN];
vector<int> g[MN];
bool con[MN][MN];

void C(int k, int a, int b) {
    assert(a <= k && k <= b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (M);
    C(N, 2, 3000);
    C(M, 1, 3000);
    for (auto i = 0; i < M; i++) {
        cin >> (A[i]) >> (B[i]);
        C(A[i], 1, N);
        C(B[i], 1, N);
        assert(A[i] != B[i]);
        g[A[i]].pb(B[i]);
        g[B[i]].pb(A[i]);
        con[A[i]][B[i]] = con[B[i]][A[i]] = true;
    }

    // N=3
    vector<int> ans(5, INF);
    for (auto i = 1; i <= N; i++) {
        for (auto x : g[i]) {
            for (auto y : g[i]) {
                if (x != y && con[x][y]) {
                    vector<int> tmp{i, x, y};
                    sort(all(tmp));
                    ans = min(ans, tmp, cmp);
                }
            }
        }
    }
    // N=4
    for (auto i = 0; i < M; i++) {
        for (auto j = i+1; j < M; j++) {
            vector<int> tmp{A[i], B[i], A[j], B[j]};
            UNIQUE(tmp);
            if (SZ(tmp) > 3)
                ans = min(ans, tmp, cmp);
        }
    }

    if (SZ(ans) > 4) cout << "-1\n";
    else {
        cout << (SZ(ans)) << '\n';
        for (auto x : ans) cout << x << ' ';
        cout << '\n';
    }

    return 0;
}