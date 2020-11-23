// ./ray-needs-help.yml
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

const int MN = 101, LG = 31;
int N, M, Q;
ll mat[LG][MN][MN];

#define CRNG(var, a, b) assert((a) <= (var) && (var) <= (b));

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (M) >> (Q);
    CRNG(N, 1, 100);
    CRNG(M, 1, N * N);
    CRNG(Q, 1, 2000);
    memset(mat, 0x3f, sizeof mat);
    for (auto i = 0; i < M; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        CRNG(a, 1, N);
        CRNG(b, 1, N);
        CRNG(c, 1, 1000000000);
        mina(mat[0][b][a], (ll)c);
    }

    for (auto i = 1; i < LG; i++) {
        for (auto j = 1; j <= N; j++) {
            for (auto k = 1; k <= N; k++) {
                for (auto l = 1; l <= N; l++) {
                    mina(mat[i][j][k], mat[i - 1][j][l] + mat[i - 1][l][k]);
                }
            }
        }
    }

    while (Q--) {
        int u, v, k;
        cin >> u >> v >> k;
        CRNG(u, 1, N);
        CRNG(v, 1, N);
        CRNG(k, 1, 1000000000);

        ll vec[N + 1];
        memset(vec, 0x3f, sizeof vec);
        vec[u] = 0;
        for (auto i = 0; i < LG; i++) {
            if ((k >> i) & 1) {
                ll tmp[N + 1];
                memset(tmp, 0x3f, sizeof tmp);
                for (auto j = 1; j <= N; j++) {
                    for (auto k = 1; k <= N; k++) {
                        mina(tmp[j], mat[i][j][k] + vec[k]);
                    }
                }

                copy(tmp, tmp + N + 1, vec);
            }
        }

        if (vec[v] == LLINF)
            cout << (-1) << '\n';
        else
            cout << (vec[v]) << '\n';
    }

    return 0;
}