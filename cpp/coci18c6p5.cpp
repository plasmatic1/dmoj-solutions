// coci-18-contest-6-5-mobitel.yml
// <3 <3 <3 <3 <3 !!!
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

/*
Considering going from N to 1 instead of 1 to N

Consider an integer and decimal part of the current value (x+y) where x (in Z) and y<1

(divide by D) 
x/d + y/d -> x' + y'

Prove that the integer part of the new result (x') is equal to floor(x/d)

if A=floor(x/d), then x = Ad + B

If x' > floor(x/d), then A > floor(x/d).  The only way for that to be possible would be if B+y > d, but since B<d (B in Z) and y<1, this is never possible.
*/

const ll MOD = 1e9 + 7;
ll madd(ll a, ll b, ll mod = MOD) { return (a + b) % mod; }
ll msub(ll a, ll b, ll mod = MOD) { return (a - b + mod) % mod; }
ll mmul(ll a, ll b, ll mod = MOD) { return (a * b) % mod; }
ll fpow(ll x, ll y, ll mod = MOD) {
    if (!y) return 1LL;
    return mmul(fpow(mmul(x, x, mod), y >> 1, mod), (y & 1) ? x : 1LL, mod);
}
ll mdiv(ll x, ll y, ll mod = MOD) { return mmul(x, fpow(y, mod - 2, mod), mod); }

const int MN = 301, MV = 1e6 + 1, SQ = 2001;
int R, C, X,
    val[MN][MN];
ll dp[2][MN][SQ][2]; // (x+y) (x in Z, y<1) -> [valx][y>0]

vector<int> nums;
int idOf[MV];
bool seen[MV];

void compute(int x) {
    if (seen[x]) return;
    seen[x] = true;
    if (x == 1) return;

    vector<int> newv;
    for (int i = 1; i <= x; i++) newv.pb(x / i);
    sort(all(newv)); newv.resize(unique(all(newv)) - newv.begin());
    nums.insert(nums.end(), all(newv));
    for (int x : newv)
        compute(x);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (R) >> (C) >> (X);
    for (auto i = 1; i <= R; i++)
        for (auto j = 1; j <= C; j++)
            cin >> (val[i][j]);

    // "Compute" stuff
    nums.pb(0);
    compute(X);
    sort(all(nums)); nums.resize(unique(all(nums)) - nums.begin());
    for (auto i = 0; i < SZ(nums); i++)
        idOf[nums[i]] = i;
    assert(SZ(nums) < SQ);

    // do DP
    dp[0][1][idOf[X]][0] = 1LL;
    for (auto i = 0; i <= R; i++) {
        int cur = i & 1, nxt = cur ^ 1;
        memset(dp[nxt], 0, sizeof dp[nxt]);
        for (auto j = 1; j <= C; j++) {
            for (auto k = 0; k < SZ(nums); k++) {
                for (auto l = 0; l < 2; l++) {
                    ll &curv = dp[cur][j][k][l]; curv %= MOD;
                    if (!curv) continue; // :smirk:

                    if (i < R) {
                        int newVID = idOf[nums[k] / val[i + 1][j]], newMod = l || (nums[k] % val[i + 1][j] > 0);
                        dp[nxt][j][newVID][newMod] += curv;
                    }
                    if (i > 0 && j < C) {
                        int newVID = idOf[nums[k] / val[i][j + 1]], newMod = l || (nums[k] % val[i][j + 1] > 0);
                        dp[cur][j + 1][newVID][newMod] += curv;
                    }
                }
            }
        }
    }

    int end = R & 1;
    ll ans = madd(dp[end][C][idOf[1]][0], madd(dp[end][C][idOf[0]][0], dp[end][C][idOf[0]][1]));
    cout << (ans) << '\n';

    return 0;
}