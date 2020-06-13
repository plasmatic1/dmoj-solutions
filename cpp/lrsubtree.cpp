#pragma region
#include "bits/stdc++.h"
using namespace std;
// Common Type shorteners and int128
using ll = long long; using ull = unsigned long long; using ld = long double;
using pii = pair<int, int>; using pll = pair<ll, ll>;
template <typename T> using vec = vector<T>;
template <typename K, typename V> using umap = unordered_map<K, V>; template <typename K> using uset = unordered_set<K>;
using vi = vec<int>; using vl = vec<ll>; using vpi = vec<pii>; using vpl = vec<pll>;
#ifdef __SIZEOF_INT128__
using int128 = __int128_t; using uint128 = __uint128_t;
#endif
template<typename I> string intStr(I x) { string ret; while (x > 0) { ret += (x % 10) + '0'; x /= 10; } reverse(ret.begin(), ret.end()); return ret; } // Int to string
// Shorthand Macros
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
#define mpr make_pair
#define mtup make_tuple
#define pb push_back
#define popcount __builtin_popcount
#define clz __builtin_clz
#define ctz __builtin_ctz
#define finline __attribute__((always_inline))
// Shorthand Function Macros
#define sz(x) ((int)((x).size()))
#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for (__typeof(a) i = a; i < b; i++)
#define reprev(i, a, b) for (__typeof(a) i = a; i > b; i--)
#define repi(a, b) rep(i, a, b)
#define repj(a, b) rep(j, a, b)
#define repk(a, b) rep(k, a, b)
#define Cmplt(type) bool operator<(const type &o) const
#define Cmpgt(type) bool operator>(const type &o) const
#define Cmpfn(name, type) bool name(const type &a, const type &b)
#define Inop(type) istream& operator>>(istream& in, type &o)
#define Outop(type) ostream& operator<<(ostream& out, type o)
#define Pow2(x) (1LL << (x))
#define scn(type, ...) type __VA_ARGS__; scan(__VA_ARGS__) // scn -> Short for SCan New
// Shorthand Functions
template<typename T> inline void maxa(T& st, T v) { st = max(st, v); }
template<typename T> inline void mina(T& st, T v) { st = min(st, v); }
inline void setprec(ostream& out, int prec) { out << setprecision(prec) << fixed; }
// Out operators and printing for arrays and vectors
template <typename T> ostream& operator<<(ostream& out,vector<T> iter){out<<"[";for(auto t:iter){out<<t<<", ";}out<<"]";return out;}
template <typename T> string arrayStr(T *arr,int sz){string ret = "[";for(int i=0;i<sz;i++){ret+=to_string(arr[i])+", "; } return ret + "]";}
template <typename T> void printArray(T *arr,int sz){for(int i=0;i<sz;i++){cout<<arr[i]<<" "; } cout<<"\n";}
// I/O Operations
inline void scan(){}
template<typename F, typename... R> inline void scan(F &f,R&... r){cin>>f;scan(r...);}
template <typename F> inline void println(F t){cout<<t<<'\n';}
template<typename F, typename... R> inline void println(F f,R... r){cout<<f<<" ";println(r...);}
inline void print(){}
template<typename F, typename... R> inline void print(F f,R... r){cout<<f;print(r...);}
// Debugging
#define db(x) cout << (#x) << ": " << (x) << ", "
#define dblb(s) cout << "[" << (s) << "] "
#define dba(alias, x) cout << (alias) << ": " << (x) << ", "
template<typename F> inline string __generic_tostring(F f) { stringstream ss; ss << f; return ss.str(); }
template<typename F> inline string __join_comma(F f) {return __generic_tostring(f);}
template<typename F, typename... R> string __join_comma(F f, R... r) { return __generic_tostring(f) + ", " + __join_comma(r...); }
#define dbp(alias, ...) cout << (alias) << ": (" << __join_comma(__VA_ARGS__) << "), "
#define dbbin(x, n) cout << (#x) << ": " << bitset<n>(x) << ", "
#define dbarr(x, n) cout << (#x) << ": " << arrayStr((x), (n)) << ", "
#define dbln cout << endl;
#pragma endregion

using pil = pair<int, ll>;
Outop(pil) {
    out << "(" << o.first << ", " << o.second << ")";
    return out;
}

const int MN = 5e5 + 1;
int N, Q,
    dep[MN], val[MN], fst[MN], lst[MN];
vi euler, g[MN];

void dfsEuler(int c, int p) {
    dep[c] = p == -1 ? 0 : dep[p] + 1;
    euler.pb(c);
    for (int to : g[c])
        if (to ^ p)
            dfsEuler(to, c);
    euler.pb(c);
}

// persistent segtree
struct Node {
    int l, r;
    ll v;
};
Node seg[21000000];
int nodeCtr = 1, root[MN * 2];
int make(ll v) {
    seg[nodeCtr] = {0, 0, v};
    return nodeCtr++;
}
int make(int l, int r) {
    seg[nodeCtr] = {l, r, seg[l].v + seg[r].v};
    return nodeCtr++;
}
int build(int l, int r) {
    if (l == r) return make(0);
    int mid = (l + r) / 2;
    return make(build(l, mid), build(mid + 1, r));
}
int update(int rt, int l, int r, int q, int v) {
    if (l == r) return make(seg[rt].v + ll(v));
    int mid = (l + r) / 2;
    if (q <= mid) return make(update(seg[rt].l, l, mid, q, v), seg[rt].r);
    return make(seg[rt].l, update(seg[rt].r, mid + 1, r, q, v));
}
ll query(int rt, int l, int r, int ql, int qr) {
    if (l > qr || r < ql) return 0LL;
    if (l >= ql && r <= qr) return seg[rt].v;
    int mid = (l + r) / 2;
    return query(seg[rt].l, l, mid, ql, qr) + query(seg[rt].r, mid + 1, r, ql, qr);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(N, Q);
    repi(1, N + 1) scan(val[i]);
    repi(1, N) {
        scn(int, a, b);
        g[a].pb(b);
        g[b].pb(a);
    }

    // setup euler tour
    euler.pb(-1);
    dfsEuler(1, -1);
    memset(fst, -1, sizeof fst);
    memset(lst, -1, sizeof lst);
    int sz = sz(euler) - 1;
    repi(1, sz + 1) {
        if (fst[euler[i]] == -1) fst[euler[i]] = i;
        else if (lst[euler[i]] == -1) lst[euler[i]] = i;
    }

    // build pseg
    root[0] = build(0, N - 1);
    repi(1, sz + 1)
        root[i] = update(root[i - 1], 0, N - 1, dep[euler[i]], val[euler[i]]);

    ll lastAns = 0;
    while (Q--) {
        scn(ll, v, l, r);
        v ^= lastAns; l ^= lastAns; r ^= lastAns;

        l += dep[v]; r += dep[v];
        lastAns = (query(root[lst[v]], 0, N - 1, l, r) - query(root[fst[v] - 1], 0, N - 1, l, r)) / 2;
        println(lastAns);
    }

    return 0;
}