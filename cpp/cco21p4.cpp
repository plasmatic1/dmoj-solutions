// ./cco-21-p4-travelling-merchant.yml
#include "bits/stdc++.h"
using namespace std;

// Refines
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
// PBRS order statistic tree
#include <ext/pb_ds/assoc_container.hpp> // Common file 
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds; 
template <typename T, class comp = less<T>> using os_tree = tree<T, null_type, comp, rb_tree_tag, tree_order_statistics_node_update>;
template <typename K, typename V, class comp = less<K>> using treemap = tree<K, V, comp, rb_tree_tag, tree_order_statistics_node_update>;
// HashSet
#include <ext/pb_ds/assoc_container.hpp>
template <typename T, class Hash> using hashset = gp_hash_table<T, null_type, Hash>;
template <typename K, typename V, class Hash> using hashmap = gp_hash_table<K, V, Hash>;
const ll RANROM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash { ll operator()(ll x) const { return x ^ RANROM; } };
#endif
// More utilities
int SZ(string &v) { return v.length(); }
template <typename C> int SZ(C &v) { return v.size(); }
template <typename C> void UNIQUE(vector<C> &v) { sort(v.begin(), v.end()); v.resize(unique(v.begin(), v.end()) - v.begin()); }
template <typename T, typename U> void maxa(T &a, U b) { a = max(a, b); }
template <typename T, typename U> void mina(T &a, U b) { a = min(a, b); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 2e5 + 1;
int N, M,
    outdeg[MN], ans[MN], A[MN], B[MN], R[MN], P[MN];
bool skipNode[MN], done[MN];
vector<pii> rg[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    for (auto i = 0; i < M; i++) {
        int a, b, r, p; cin >> a >> b >> r >> p; a--; b--;
        rg[b].eb(a, i);
        outdeg[a]++;

        A[i] = a; B[i] = b; R[i] = r; P[i] = p;
    }

    // pop
    queue<int> q;
    for (auto i = 0; i < N; i++)
        if (outdeg[i] == 0)
            q.push(i);
    while (!q.empty()) {
        int c = q.front(); q.pop();
        skipNode[c] = true;
        for (auto [to, toi] : rg[c]) {
            done[toi] = true;
            if (--outdeg[to] == 0)
                q.push(to);
        }
    }

    memset(ans, 0x3f, sizeof ans);
    priority_queue<pii> pq;
    for (auto i = 0; i < M; i++)
        if (!done[i])
            pq.emplace(R[i], i);
    while (!pq.empty()) {
        auto [w, idx] = pq.top(); pq.pop();
        if (done[idx]) continue;
        done[idx] = true;

        if (--outdeg[A[idx]] == 0) {
            ans[A[idx]] = w;
            for (auto [rto, ridx] : rg[A[idx]])
                if (!done[ridx])
                    pq.emplace(w-P[ridx], ridx);
        }
    }

    for (auto i = 0; i < N; i++)
        cout << (ans[i] == INF ? -1 : ans[i]) << " \n"[i == N-1];

    return 0;
}