// ./back-from-summer-17-p5-confusing-codeforces-contest.yml
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

const ll MOD = 1e9 + 7;
ll madd(ll a, ll b, ll mod = MOD) { return (a + b) % mod; }
ll msub(ll a, ll b, ll mod = MOD) { return (a - b + mod) % mod; }
ll mmul(ll a, ll b, ll mod = MOD) { return (a * b) % mod; }
ll fpow(ll x, ll y, ll mod = MOD) {
    if (!y) return 1LL;
    return mmul(fpow(mmul(x, x, mod), y >> 1, mod), (y & 1) ? x : 1LL, mod);
}
ll mdiv(ll x, ll y, ll mod = MOD) { return mmul(x, fpow(y, mod - 2, mod), mod); }

/*
 *
 * Subtask 4 solution:
 * K <= 7, so we can consider every person in terms of the set of groups that they are a part of.  Then, the set of people they can reach is just all the people not part of any of the groups they are a part of.  Obviously, there are at most 2^K=128 possible set of people someone can reach, so we can just make an array of size 2^K where A[c] maintains the number of ways to reach person i given that they are part of the configuration of groups c (there are only 2^K possible configurations).  When updating, we just consider all possible group configurations that the current person can reach (as in, that person is not a member of any of those groups in that configuration).  We can do this naively in O(2^K) by checking all subsets.  Finally, for queries we just find the group configuration for the current person and return the current sum for that configuration.
 *
 * Full solution:
 * To get the full solution, we can split the work between the update and query operations.  Going back to the previous subtask, if we think of the group configuration as a set of bits, and the configuration of index i as C[i], an update operation is simply incrementing all subsets of ~C[i], and a query is simply just asking for C[i].  Splitting the work means split C[i] into hi[i] (high K/2 bits) and lo[i] (low K/2 bits), incrementing all subsets of ~hi[i] in the update, and summing all supersets of lo[i] in the query.  For more details, view the implementation below or the editorial.
 *
 * Overall, this yields us a complexity of O(2^(K/2)) for both the update and query, for O(N*sqrt(2^K)) overall.  This is enough to pass well within the time limit.
 *
 */

const int MN = 1e6 + 1, MK = 14, MSM = 7, MSMSUB = 1 << MSM;
int N, K, lo, hi,
    partOf[MN];
bool group[MK][MN];
ll dp[MN], sto[MSMSUB][MSMSUB];

int ghi(int x) { return x >> lo; }
int glo(int x) { return x & ((1 << lo) - 1); }
bool issubset(int big, int small) { return (big | small) == big; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (K);
    for (auto i = 0; i < K; i++) {
        int n;
        cin >> n;
        for (auto j = 0; j < n; j++) {
            int x;
            cin >> x;
            group[i][x] = true;
            partOf[x] |= 1 << i;
        }
    }
    hi = K / 2; lo = K - hi;

    int mmsk = (1 << K) - 1, hisub = 1 << hi, losub = 1 << lo;
    dp[1] = 1LL;
    for (auto i = 1; i <= N; i++) {
        if (i >= 2) {
            int chi = ghi(partOf[i]), clo = glo(partOf[i]);
            for (auto j = 0; j < losub; j++)
                if (issubset(j, clo))
                    dp[i] = madd(dp[i], sto[chi][j]);
        }
        
        int canGo = partOf[i] ^ mmsk, chi = ghi(canGo), clo = glo(canGo);
        for (auto j = 0; j < hisub; j++)
            if (issubset(chi, j))
                sto[j][clo] = madd(sto[j][clo], dp[i]);
    }

    cout << (dp[N]) << '\n';

    return 0;
}