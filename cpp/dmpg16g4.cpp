// 1.yml
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
using ll = long long; using ull = unsigned long long; using ld = long double;
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

// dp[i] -> Answer from all indices 1..(i-1)
// transition from j->i, assume we start blocking type[j] at time j and stop early enough such that we can start blocking again at time i
const int MN = 1e5 + 10;
int N, M,
    dp[MN], type[MN], waitTime[MN];
vector<int> cnt[MN];

int getCnt(int l, int r, int v) {
    return upper_bound(all(cnt[v]), r) - lower_bound(all(cnt[v]), l);
}

int best[MN], csub[MN];
vector<int> rem[MN * 2];
multiset<int> possible;

void updBest(int id, int newv) {
    auto ptr = possible.find(best[id]);
    if (ptr != possible.end())
        possible.erase(ptr);
    best[id] = newv;
    possible.insert(newv);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> (N) >> (M);
    for (auto i = 1; i <= N; i++) {
        cin >> (type[i]);
        cnt[type[i]].pb(i);
        csub[type[i]]++;
    }
    for (auto i = 1; i <= M; i++)
        cin >> (waitTime[i]);
    for (auto i = 1; i <= N; i++)
        rem[i + waitTime[type[i]]].pb(type[i]);

    for (auto i = 1; i <= N; i++) {
        if (i >= 2)
            dp[i] = *(--possible.end());
        updBest(type[i], max(best[type[i]], dp[i] + getCnt(i, N, type[i]) - csub[type[i]]));
        
        for (auto x : rem[i]) {
            csub[x]--;
            updBest(x, best[x] + 1);
        }
    }

    int ans = 0;
    for (auto i = 1; i <= N; i++)
        ans = max(ans, dp[i] + getCnt(i, N, type[i]));
    cout << (ans) << '\n';

    return 0;
}