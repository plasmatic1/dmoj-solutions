// icpc-naq-2016-f-free-desserts.yml
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

const int MN = 18 + 1, MMSK = 59049, MNUM = 5000;
int N,
    val[MN];
ll P,
   dp[2][MMSK][2][2][2]; // dp {digit, mask of used digits, carry (yes/no), last digit was a 0 (yes/no)
vector<ll> nums[2][MMSK][2][2][2]; // why am i doing this to myself
bool phas[10];
int ternary[MMSK][10], pow3[10], idOf[10];
vector<int> validMsk;

string pt(int m) {
    string res;
    for (auto i = 0; i < 10; i++)
        res += ternary[m][i] + '0';
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (P);
    string tmp = to_string(P);

    // compute ternary precalc
    pow3[0] = 1;
    for (auto i = 1; i < 10; i++)
        pow3[i] = pow3[i - 1] * 3;
    for (auto i = 0; i < MMSK; i++) {
        ternary[i][0] = i % 3;
        for (auto j = 1; j < 10; j++) {
            ternary[i][j] = (i / pow3[j]) % 3; }
    }

    // convert digit values to numbers and check which digits are present in P
    N = tmp.length();
    for (auto i = 0; i < N; i++) {
        val[N - i - 1] = tmp[i] - '0';
        phas[val[N - i - 1]] = true;
    }
    
    // compute valid masks
    for (auto i = 0; i < MMSK; i++) {
        bool good = true;
        for (auto j = 0; j < 10; j++)
            if (phas[j] && ternary[i][j] != 0)
                good = false;
        if (good)
            validMsk.pb(i);
    }

    // do dp
    dp[0][0][0][0][0] = 1LL;
    nums[0][0][0][0][0].pb(0);
    ll pow10 = 1;
    for (auto i = 1; i <= N; i++) {
        int pre = (i - 1) & 1, cur = i & 1;

        // Reset dp and nums
        for (int j : validMsk) {
            for (auto k = 0; k < 2; k++) {
                for (auto l = 0; l < 2; l++) {
                    for (auto m = 0; m < 2; m++) {
                        nums[cur][j][k][l][m].clear();
                        dp[cur][j][k][l][m] = 0;
                    }
                }
            }
        }

        // Compute dp
        for (auto j : validMsk) { // ternary mask of used digits (0->unused, 1->used by num 1, 2->used by num 2)
            for (int carry = 0; carry < 2; carry++) { // carry over from previous digit
                for (int last0A = 0; last0A < 2; last0A++) { // last digit (on first num) was 0
                    for (int last0B = 0; last0B < 2; last0B++) { // last digit (on second num) was 0
                        if (!dp[pre][j][carry][last0A][last0B]) continue;
                        for (auto k = 0; k < 10; k++) { // loop over all the possible digits
                            for (auto forceCarry = 0; forceCarry < 2; forceCarry++) {
                                if (k && (ternary[j][k] == 2 || phas[k])) continue; // Already used (on other)
                                int l = val[i - 1] - carry - k + forceCarry * 10;
                                if (l > 9 || l < 0 || (l && k && l == k)) continue; // l can't be negative and l != k must be true
                                int newv = k + l + carry;
                                if (l && (ternary[j][l] == 1 || phas[l])) continue; // Same digit (second number)
                                if (last0A && k && (phas[0] || ternary[j][0] == 2)) continue; // Leading 0s become normal 0s (first number)
                                if (last0B && l && (phas[0] || ternary[j][0] == 1)) continue; // Leading 0s become normal 0s (second number)
                                if (last0A && k && last0B && l) continue; // 0s are going to be added to both numbers

                                int newMsk = j;
                                if (k && ternary[newMsk][k] == 0) newMsk += pow3[k];
                                if (l && ternary[newMsk][l] == 0) newMsk += 2 * pow3[l];
                                if (last0A && k && ternary[newMsk][0] == 0) newMsk++;
                                if (last0B && l && ternary[newMsk][0] == 0) newMsk += 2;

                                bool newCarry = newv >= 10, newLast0A = k == 0, newLast0B = l == 0;
                                dp[cur][newMsk][newCarry][newLast0A][newLast0B] += dp[pre][j][carry][last0A][last0B];
                                auto &v = nums[cur][newMsk][newCarry][newLast0A][newLast0B];
                                for (auto x : nums[pre][j][carry][last0A][last0B])
                                    v.pb(x + k * pow10);
                            }
                        }
                    }
                }
            }
        }

        // Update vectors
        for (int j : validMsk) {
            for (auto k = 0; k < 2; k++) {
                for (auto l = 0; l < 2; l++) {
                    for (auto m = 0; m < 2; m++) {
                        auto &v = nums[cur][j][k][l][m];
                        sort(all(v));
                        if (sz(v) > MNUM)
                            v.resize(MNUM);
                    }
                }
            }
        }

        pow10 *= 10;
    }

    // Sum ans
    int lst = N & 1;
    vector<ll> ansNums;
    ll ans = 0;
    for (int i : validMsk) {
        for (auto k = 0; k < 2; k++) {
            for (auto l = 0; l < 2; l++) {
                ansNums.insert(ansNums.end(), nums[lst][i][0][k][l].begin(), nums[lst][i][0][k][l].end());
                ans += dp[lst][i][0][k][l];
            }
        }
    }
    sort(all(ansNums));
    if (sz(ansNums) > MNUM)
        ansNums.resize(MNUM);

    // Print ans
    cout << (ans / 2) << '\n'; assert(!(ans % 2));
    for (auto x : ansNums)
        if (x < P - x)
            cout << (x) << ' ' << (P - x) << '\n';

    return 0;
}