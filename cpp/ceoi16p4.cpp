// 1.yml
#include "bits/stdc++.h"
using namespace std;

// Defines
#define pb push_back
#define fs first
#define sn second
#define mpr make_pair
#define mtp make_tuple
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

const ll MOD[2] = {1000000007, 1000000009}, BASE[2] = {131, 71};
ll madd(ll a, ll b, ll mod) { return (a + b) % mod; }
ll msub(ll a, ll b, ll mod) { return (a - b + mod) % mod; }
ll mmul(ll a, ll b, ll mod) { return (a * b) % mod; }
ll fpow(ll x, ll y, ll mod) {
    if (!y) return 1LL;
    return mmul(fpow(mmul(x, x, mod), y >> 1, mod), (y & 1) ? x : 1LL, mod);
}
ll mdiv(ll x, ll y, ll mod) { return mmul(x, fpow(y, mod - 2, mod), mod); }

ll comb(ll lo, ll hi) { return (hi << 32LL) | lo; }
ll glo(ll hsh) { return hsh & ((1LL << 32) - 1); }
ll ghi(ll hsh) { return hsh >> 32LL; }
ll append(ll hsh, int v) {
    ll lo = glo(hsh), hi = ghi(hsh);
    return comb(madd(mmul(lo, BASE[0], MOD[0]), v, MOD[0]), madd(mmul(hi, BASE[1], MOD[1]), v, MOD[1]));
}

int let(char c) { return c - 'a'; }

const int MN = 1e5 + 1;
int N;
string s;
map<pair<ll, ll>, vector<int>> ps[26];
ll hsh[MN];
bool done[MN];
string ans;

// get same stack as end, same letter as begin, greatest index
void solve(int l, int r) {
    if (l > r) return;

    vector<int> &tf = ps[let(s[l])][make_pair(hsh[l], hsh[r])];

    int p = *(--upper_bound(tf.begin(), tf.end(), r));
    // cout << "[match]: ";
    // cout << "l=" << (l) << ", ";
    // cout << "p=" << (p) << ", ";
    // cout << endl;
    ans[l] = '('; ans[p] = ')';
    done[l] = done[p] = true;
    solve(l + 1, p - 1); solve(p + 1, r);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (s);
    N = s.length();

    vector<pair<ll, char>> stk;
    stk.emplace_back(0, '0');
    for (auto i = 0; i < N; i++) {
        if (s[i] == stk.back().second)
            stk.pop_back();
        else
            stk.emplace_back(append(stk.back().first, let(s[i]) + 1), s[i]);

        hsh[i] = stk.back().first;
    }
    for (auto i = 1; i < N; i++) {
        ps[let(s[i])][make_pair(hsh[i - 1], hsh[i])].push_back(i);
    }

    if (sz(stk) > 1) {
        cout << (-1) << '\n';
        return 0;
    }

    ans.resize(N);
    solve(0, N - 1);
    cout << (ans) << '\n';

    return 0;
}