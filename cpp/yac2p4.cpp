// ./p4-no-more-arithmetic.yml
// why
// did
// you
// make
// us
// do
// prim
// why?????????????????????????
#include <bits/stdc++.h>
#define DEBUG 0
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

const int MN = 2000;
int N, M;
ll A[MN];

int cost(ll a, ll b) {
    a = A[a]; b = A[b];
    if (a < b) swap(a, b);
    ll ret = max({(a + b) % M, (a - b) % M, (a * b) % M});
    if (a % b == 0) ret = max(ret, (a / b) % M);
    return ret;
}

bool done[MN];
int dis[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    for (auto i = 0; i < N; i++)
        cin >> A[i];

    // run prim... mst....
    ll ans = 0;
    fill(dis, dis+N, -INF);
    dis[0] = 0;

    while (1) {
        int c = -1, best = -INF;
        for (auto i = 0; i < N; i++) {
            if (!done[i] && dis[i] > best) {
                best = dis[i];
                c = i;
            }
        }
        if (c == -1) break;
        done[c] = true;
        ans += dis[c];

        for (auto i = 0; i < N; i++) {
            if (!done[i]) {
                maxa(dis[i], cost(c, i));
            }
        }
    }

    cout << (ans) << '\n';

    return 0;
}