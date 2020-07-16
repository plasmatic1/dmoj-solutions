// cco-09-p4-bottle-caps.yml
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

mt19937 mt(RANDOM);
int randint(int a, int b) {
    return uniform_int_distribution<int>(a, b)(mt);
}

const int MN = 10001;
int N,
    capSize[MN], botSize[MN];

#ifdef LOCAL
const int _SZ[2][4] = {
    {4, 1, 2, 3},
    {1, 4, 2, 3}
};
int ask(int i, int j) {
    i--; j--;
    if (_SZ[0][i] < _SZ[1][j]) return -1;
    if (_SZ[0][i] == _SZ[1][j]) return 0;
    return 1;
}
#else
int ask(int i, int j) {
    static int opc = 0;
    assert(opc++ <= 500000);
    cout << "0 " << i << ' ' << j << endl;
    int res; cin >> res; return res;
}
#endif

int idOf[MN];
void finish() {
    for (auto i = 1; i <= N; i++)
        idOf[botSize[i]] = i;
    for (auto i = 1; i <= N; i++) {
        cout << "1 " << i << ' ' << idOf[capSize[i]] << endl; }
}

void solve(int l, int r, vector<int> caps, vector<int> bottles) {
    if (l > r) return;
    if (l == r) {
        capSize[caps[0]] = botSize[bottles[0]] = l; return; }

    int id = randint(0, SZ(caps) - 1);
    vector<int> gtB, ltB; int eqB = -1;
    for (auto x : bottles) {
        int res = ask(caps[id], x);
        if (res == 1) ltB.pb(x);
        else if (res == -1) gtB.pb(x);
        else eqB = x;
    }

    int mid = SZ(ltB) + l;
    capSize[caps[id]] = botSize[eqB] = mid;

    vector<int> gtC, ltC;
    for (auto x : caps) {
        if (x == caps[id]) continue;
        int res = ask(x, eqB);
        if (res == 1) gtC.pb(x);
        else if (res == -1) ltC.pb(x);
    }

    solve(l, mid - 1, ltC, ltB);
    solve(mid + 1, r, gtC, gtB);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

#ifndef LOCAL
    cin >> (N);
#else
    N = 4;
    cout<<"_SZ[0]=["; for(int i=0; i<(N); i++)cout<<_SZ[0][i]<<", "; cout<<"], ";cout<<"_SZ[1]=["; for(int i=0; i<(N); i++)cout<<_SZ[1][i]<<", "; cout<<"], ";cout << endl; // db A:N:_SZ[0], A:N:_SZ[1]
#endif

    vector<int> vec(N); iota(all(vec), 1);
    solve(1, N, vec, vec);

#ifndef LOCAL
    finish();
#else
    cout<<"(capSize + 1)=["; for(int i=0; i<(N); i++)cout<<(capSize + 1)[i]<<", "; cout<<"], ";cout << endl; // db A:N:(capSize + 1)
    cout<<"(botSize + 1)=["; for(int i=0; i<(N); i++)cout<<(botSize + 1)[i]<<", "; cout<<"], ";cout << endl; // db A:N:(botSize + 1)
#endif

    return 0;
}