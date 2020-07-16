// apio-07-p3-zoo.yml
#include "bits/stdc++.h"
using namespace std;

// Defines
#define pb push_back
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
template <typename C> int SZ(C &v) { return v.size(); }
template <typename T, typename U> void maxa(T &a, U b) { a = max(a, b); }
template <typename T, typename U> void mina(T &a, U b) { a = min(a, b); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 10001, MC = 50001;
int N, C,
    pos[MC];
vector<int> endPos[MN], bad[MC], good[MC];

int dp[2][32][32]; // start mask, cur mask

void reset(int idx) {
    for (auto i = 0; i < 32; i++)
        for (auto j = 0; j < 32; j++)
            dp[idx][i][j] = -INF;
}

int cost[32];
void setCost(int pos) {
    fill(cost, cost + 32, 0);
    for (int child : endPos[pos]) {
        bool want[5], nwant[5]; fill(want, want + 5, 0); fill(nwant, nwant + 5, 0);
        for (int x : good[child]) {
            if (x > pos) x -= N;
            want[pos - x] = true;
        }
        for (int x : bad[child]) {
            if (x > pos) x -= N;
            nwant[pos - x] = true;
        }

        for (auto i = 0; i < 32; i++) {
            bool good = false;
            for (auto j = 0; j < 5; j++) {
                if ((i >> j) & 1) good |= want[j];
                else good |= nwant[j];
            }
            cost[i] += good;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (C);
    for (auto i = 0; i < C; i++) {
        cin >> (pos[i]);
        int nBad, nGood;
        cin >> nBad >> nGood;
        for (auto j = 0; j < nBad; j++) {
            int x;
            cin >> x;
            bad[i].pb(x);
        }
        for (auto j = 0; j < nGood; j++) {
            int x;
            cin >> x;
            good[i].pb(x);
        }
        endPos[(pos[i] - 1 + 4) % N + 1].pb(i);
    }

    // DP
    setCost(5);
    for (auto i = 0; i < 32; i++)
        dp[5 & 1][i][i] = cost[i];
    for (auto i = 5; i <= N + 3; i++) {
        int cur = i & 1, nxt = !cur;
        reset(nxt);
        setCost(i % N + 1);
        for (auto j = 0; j < 32; j++) {
            for (auto k = 0; k < 32; k++) {
                for (int use = 0; use < 2; use++) {
                    if (i + 1 > N && use != (j >> (5 - (i + 1 - N)) & 1)) continue;
                    int newMsk = ((k << 1) | use) & 31; // new mask of prev.
                    maxa(dp[nxt][j][newMsk], dp[cur][j][k] + cost[newMsk]);
                }
            }
        }
    }

    // print ans
    int end = (N + 4) & 1, ans = -INF;
    for (auto i = 0; i < 32; i++)
        for (auto j = 0; j < 32; j++)
            maxa(ans, dp[end][i][j]);
    cout << (ans) << '\n';

    return 0;
}