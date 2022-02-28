// ./p4-reindeer-racing.yml
#include <bits/stdc++.h>
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
#if __cplusplus == 201703L // CPP17 only things
template <typename T> using opt_ref = optional<reference_wrapper<T>>; // for some templates
#endif
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

const int MN = 2001;
int N, M, S, F, L, R,
    K[MN];
bool ana[MN][MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> S >> F >> L >> R;
    for (auto i = 1; i <= M; i++)
        cin >> K[i];

    if (R == 0 && S != F) {
        cout << (-1) << '\n';
        return 0;
    }

    int fnd = 0;
    for (auto i = 1; i <= M; i++)
        if (K[i] == F)
            fnd = i;

    if (fnd == 0 && S != F) {
        cout << (-1) << '\n';
        return 0;
    }

    if (L > N*M - (M - fnd)) {
        cout << (-1) << '\n';
        return 0;
    }

    if (S != F && L == 0) {
        L++;
        assert(L <= R);
    }

    int left = L-1, cur = S;
    bool isdone = false;
    if (fnd == 0) left++;
    for (auto i = 1; i <= M; i++) {
        for (auto j = 1; j <= N; j++) {
            if (!isdone && i == fnd && j == cur && left != -1) {
                ana[j][i] = true;
                isdone = true;
            }
            else if (left > 0 && (j != F || i <= fnd)) {
                ana[j][i] = true;
                left--;
            }
        }
        
        int pass = -1;
        if (ana[cur][i])
            pass = K[i];

        if (pass != -1) cur = pass;
    }

    cout << (L) << '\n';
    for (auto i = 1; i <= N; i++)
        for (auto j = 1; j <= M; j++)
            cout << ana[i][j] << " \n"[j == M];

    return 0;
}