// ./dmpg-19-s5-secret-sort.yml
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

ostream& operator<<(ostream& out, const pii o) {
    out << "(fs=" << o.fs << ", sn=" << o.sn << ")";
    return out;
}

const int MN = 2001;
int N;

#ifdef LOCAL
vector<int> A;
int ask(int i, int j) {
    swap(A[i - 1], A[j - 1]);
    int res = 0;
    for (auto i = 0; i < N; i++)
        for (auto j = i + 1; j < N; j++)
            res += A[i] > A[j];
    return res;
}
#else
int ask(int a, int b) {
    cout << a << ' ' << b << '\n'; cout.flush();
    int res; cin >> res;
    return res;
}
#endif

/*

1 2 3 4 5 
5 2 3 4 1

x, y -> y, x

(# > x) + (# < y) - (# > y) - (# < x)
= (N - x) + (y - 1) - (N - y) - (x - 1)
= (-x - (-y)) + (y - x)
= -(x - y) + (y - x)
= 2 * (y - x) - (1 in abs)

If (x>y) then +1 (overall will be <=0)
If (x<y) then -1 (overall will be >=0)

#(x < ? <= y) + #(x <= ? < y) -> same thing as removing <=
-> 2 * #(x < ? < y) + (y > x ? -1 : 1)

Let's say Delta(inv) = D

(D + D/abs(D)) / 2 -> y-x

a b c d
3 4 1 2
-> init
d b c a
2 4 1 3
-> find diff = -1 (a - 1 = d) 
c b d a
1 4 2 3
-> find diff = -1 (d - 1 = c)
b c d a
4 1 2 3
-> find diff = +1 (c + 1 = b) (WA?)

a -( -1 )> d -( -1 )> c -( +1 )> b

-> Note: permutation after the initial compare checks
a b c d e (Init)
e b c d a
d b c e a
c b d e a
b c d e a (Final)

*/

int getDiff(int invDiff) {
    int sign = invDiff / abs(invDiff);
    return (invDiff + sign) / 2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N);

#ifdef LOCAL
    A.resize(N);
    for (auto &x : A)
        cin >> x;
#endif

    // Compute relatives differences of permutation
    map<int, int> have;
    int preInv = ask(1, 1), preDiff = 0; have[0] = 1;
    for (auto i = N; i >= 2; i--) {
        int ninv = ask(1, i), D = ninv - preInv,
            diff = getDiff(D);

        int cur = preDiff, rem = diff, sign = rem / abs(rem);
        while (rem != 0) {
            cur += sign;
            rem -= sign;
            while (have.count(cur))
                cur += sign;
        }
        have[cur] = i;

        preInv = ninv;
        preDiff = cur;
    }

    // Build current permutation (after relative difference checks)
    vector<int> curArr(N);
    int ctr = 0;
    for (auto p : have) {
        int tpos = ((p.sn - 1) - 1 + N) % N;
        curArr[tpos] = ++ctr;
    }

    // Sort permutation
    for (auto i = 0; i < N - 1; i++) {
        int idx = -1;
        for (auto j = i; j < N; j++) {
            if (curArr[j] == i + 1) {
                idx = j;
                break;
            }
        }
        ask(i + 1, idx + 1);
        swap(curArr[i], curArr[idx]);
    }

    // done
#ifdef LOCAL
    bool good = true;
    for (auto i = 0; i < N; i++)
        good &= A[i] == i + 1;
    if (good)
        cout << ("AC") << '\n';
    else {
        cout << ("WA") << '\n';
        cout << "A=["; for (auto x:A)cout<<x<<", "; cout<<"], "; cout << endl; // db I:A
    }
#else
    cout << "0\n";
    cout.flush();
#endif

    return 0;
}