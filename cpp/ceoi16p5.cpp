// ceoi-16-p5-popeala.yml
#include "bits/stdc++.h"
using namespace std;

// Defines
#define pb push_back
#define fs first
#define sn second
#define mpr make_pair
#define mtp make_tuple
#define all(x) (x).begin(), (x).end()
// Basic type definitions
using ll = long long; using ull = unsigned long long;
using pii = pair<int, int>; using pll = pair<long, long>;
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
template <typename C> int sz(C &v) { return v.size(); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

/*
assume 1<=i<=K, 1<=k<j<=T

dp[i][j] <- dp[i - 1][k] + cnt(k + 1, j) * (psum[j] - psum[k])

Let A = cnt(k + 1, j)
dp[i][j] = (A * psum[j]) + (dp[i - 1][k] - A * psum[k])
Let B = A * psum[j] (fixed)
Let C = dp[i - 1][k] - A * psum[k] (variable)

cnt(x, y) == A represents a continuous range:
- If we increase the right boundary, the cnt may decrease
- If we increase the left boundary, the cnt may increase

Begin: (for each K, we calculate for every possible value of A)
- Increase right boundary until cnt(x, y) == A
  - Increase right boundary until we find the last cnt(x, y) >= A
  - If right boundary < A, increase left boundary until cnt(x, y) >= A
  - Note: cnt(x, y) < A is fine as it's a strictly worse answer than if we used A' where A' > A (we would get a better answer when we were looping for A')
*/

const int MT = 20001, MN = 55, MK = 55;
int N, T, K,
    pre[MN][MT], lpos[MN][MT]; 
bitset<MT> ver[MN];
ll dp[MK][MT], psum[MT];

ll vcost(int i, int k, int A) {
    return dp[i - 1][k] - A * psum[k]; }

deque<int> best[MN];
int ptr[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (T) >> (K);
    for (auto i = 1; i <= T; i++)
        cin >> (psum[i]);
    partial_sum(psum, psum + T + 1, psum);
    for (auto i = 1; i <= N; i++) {
        string buf; cin >> buf;
        for (auto j = 1; j <= T; j++)
            ver[i][j] = buf[j - 1] == '1';
    }

    // precalc
    for (auto i = 1; i <= N; i++) {
        int pree = 0;
        for (auto j = 1; j <= T; j++) {
            if (!ver[i][j])
                pree = j;
            pre[i][j] = pree; // Prev 0 for person i
        }
    }

    // lpos[i][j] = k where k is the minimal position such that cnt(k, j) = i
    for (auto i = 1; i <= T; i++) {
        vector<int> pos;
        for (auto j = 1; j <= N; j++)
            pos.pb(pre[j][i]);
        sort(all(pos), greater<int>()); 
        int cur = N;
        for (auto x : pos) {
            lpos[cur][i] = x + 1;
            cur--;
        }
        while (cur >= 0) {
            lpos[cur][i] = -INF;
            cur--;
        }
        lpos[N + 1][i] = i + 1;
    }

    // dp
    memset(dp, 0x3f, sizeof dp);
    dp[0][0] = 0;
    for (auto i = 1; i <= K; i++) {
        for (auto j = 0; j <= N; j++)
            best[j].clear();
        fill(ptr, ptr + N + 1, 0);

        for (auto j = 1; j <= T; j++) {
            for (auto k = 0; k <= N; k++) { // increasing DQ
                while (ptr[k] < j && ptr[k] + 1 < lpos[k + 1][j]) {
                    while (!best[k].empty() && vcost(i, best[k].back(), k) > vcost(i, ptr[k], k))
                        best[k].pop_back();
                    best[k].pb(ptr[k]);
                    ptr[k]++;
                }
                while (!best[k].empty() && best[k].front() + 1 < lpos[k][j])
                    best[k].pop_front();
            }

            for (auto k = 0; k <= N; k++) {
                if (!best[k].empty())
                    dp[i][j] = min(dp[i][j], k * psum[j] + vcost(i, best[k].front(), k));
            }
        }

        cout << (dp[i][T]) << '\n';
    }

    return 0;
}