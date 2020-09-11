// ./dmpg-19-s6-a-strange-array.yml
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

/*

Idea (given l, r, x):
First find the subarray l..p with the greatest sum <= x ans p <= r and check if sum(l..r) < x (print no in that case)

if sum(l..p) == x then we're done, otherwise sum(l..p) == x - 1 (if it was even smaller, we could always just add another number and the sum would still be <= x so there is a contradiction)

Now we need to find two subarrays l..a and p+1..b such that a <= b, b <= r, and sum(p+1..b)-sum(l..a) = 1

Observe that A[p+1] == 2, because otherwise we could just increase p by 1 and make the sum x, and now look for the first index >=l where A[idx] == 1 (denoted as a') (along with the same for > p (denoted as b')).  

Let nlen = min(a' - l + 1, b' - p) -> this will be the length of p+1..b, meaning that b = p + nlen.  Additionally, we also set a = l + nlen - 1.  Now let's consider the possible cases:

Note that sum(l..a-1) == sum(p+1..b-1) always given how we constructed the subarray (values in A[l..a-1] and A[p+1..b-1] are all 2, and len(l..a-1) == len(p+1..b-1))

A[b] == 1 and A[a] == 1: Since sum(l..a) == sum(p+1..b) so we can simply reduce a by 1 to find a solution.
A[b] == 1 and A[a] == 2: Since sum(l..a) == sum(p+1..b) + 1 so we can simply reduce a by 1 to find a solution.
A[b] == 2 and A[a] == 1: sum(l..a) + 1 == sum(p+1..b) already.

Thus, the problem has now reduced to simply computing a and b, and since b > a (all numbers are positive and both sum(p+1..b) == sum(l..a) and p+1 > l hold) we just need to check if b <= r to see if we have an answer.

*/

const int MN = 1e6 + 1;
int N, Q,
    val[MN], nxt1[MN], psum[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (Q);
    for (auto i = 1; i <= N; i++) {
        cin >> (val[i]);
        psum[i] = psum[i - 1] + val[i];
    }
    for (auto i = N; i >= 1; i--)
        nxt1[i] = val[i] == 1 ? i : nxt1[i + 1];

    while (Q--) {
        int l, r, x;
        cin >> l >> r >> x;

        if (psum[r] - psum[l - 1] < x) {
            cout << ("NO") << '\n';
            continue;
        }

        int p = upper_bound(psum, psum + N + 1, psum[l - 1] + x) - 1 - psum;
        if (psum[p] - psum[l - 1] == x) {
            cout << ("YES") << '\n';
            continue;
        }
        else {
            assert(psum[p] - psum[l - 1] == x - 1);
            int nlen = min(nxt1[l] - l + 1, nxt1[p + 1] - p);
            cout << (p + nlen <= r ? "YES" : "NO") << '\n';
        }
    }

    return 0;
}