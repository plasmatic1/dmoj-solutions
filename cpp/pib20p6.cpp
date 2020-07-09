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
#define popcountll __builtin_popcountll
#define clzll __builtin_clzll
#define ctzll __builtin_ctzll
#define finline __attribute__((always_inline))
// Shorthand Function Macros
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
template<typename T> inline int sz(const T &x) { return x.size(); }
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

#include <ext/pb_ds/assoc_container.hpp> // Common file 
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds; 
template <typename T, class comp = less<T>> using os_tree = tree<T, null_type, comp, rb_tree_tag, tree_order_statistics_node_update>;
template <typename K, typename V, class comp = less<K>> using treemap = tree<K, V, comp, rb_tree_tag, tree_order_statistics_node_update>;

ll Op(int type, ll a, ll b) {
    switch(type) {
        case 1: return a + b;
        case 2: return max(a, b);
    }
    return -1;
}
ll Default(int type) {
    switch(type) {
        case 1: return 0;
        case 2: return -LLINF;
    }
    return -1;
}

struct Qu {
    int id, kth;
};

const int MN = 1e5 + 1;
int N, Q,
    chid[MN], par[MN];
ll val[MN], ans[MN], dp[MN], dpUp[MN];
vec<ll> lhs[MN], rhs[MN];
vi g[MN];

void dfs(int c, int p, int op) {
    dp[c] = val[c];
    par[c] = p;

    lhs[c].assign(sz(g[c]) + 2, Default(op));
    rhs[c].assign(sz(g[c]) + 2, Default(op));
    repi(0, sz(g[c])) {
        int to = g[c][i];

        if (to != p) {
            chid[to] = i + 1;
            dfs(to, c, op);
            dp[c] = Op(op, dp[c], dp[to]);
            lhs[c][i + 1] = Op(op, lhs[c][i], dp[to]);
        }
        else
            lhs[c][i + 1] = lhs[c][i];
    }
    reprev(i, sz(g[c]), 0) {
        int to = g[c][i - 1];
        
        if (to != p)
            rhs[c][i] = Op(op, rhs[c][i + 1], dp[to]);
        else
            rhs[c][i] = rhs[c][i + 1];
    }
}
void up(int c, int op) {
    if (c == 1) return void(dpUp[1] = Default(op));
    if (dpUp[c] != -LLINF) return;
    up(par[c], op);
    dpUp[c] = Op(op, dpUp[par[c]], val[par[c]]);
    dpUp[c] = Op(op, dpUp[c], lhs[par[c]][chid[c] - 1]);
    dpUp[c] = Op(op, dpUp[c], rhs[par[c]][chid[c] + 1]);
}

os_tree<pair<ll, int>> pairs;
map<ll, int> cnt;
void ins(ll x) {
    pairs.insert(mpr(-x, cnt[x]));
    cnt[x]++;
}
void rem(ll x) {
    cnt[x]--;
    pairs.erase(mpr(-x, cnt[x]));
}
ll kth(int k) { // 0-indexed
    return -pairs.find_by_order(k)->first;
}
vec<Qu> qs[3][MN];

void init(int c, int p) {
    ins(dp[c]);
    for (int to : g[c])
        if (to != p)
            init(to, c);
}

void solve(int c, int p, int op) {
    for (auto q : qs[op][c])
        ans[q.id] = kth(q.kth - 1);
    for (int to : g[c]) {
        if (to != p) {
            ins(dpUp[to]);
            rem(dp[to]);
            solve(to, c, op);
            ins(dp[to]);
            rem(dpUp[to]);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    scan(N, Q);
    repi(1, N + 1) scan(val[i]);
    repi(0, N - 1) {
        scn(int, a, b);
        g[a].pb(b);
        g[b].pb(a);
    }
    repi(0, Q) {
        scn(int, T, node, kth);
        qs[T][node].pb({i, kth});
    }
    repi(1, 3) {
        fill(dpUp, dpUp + N + 1, -LLINF);
        dfs(1, -1, i);
        repj(1, N + 1)
            up(j, i);
        init(1, -1);
        solve(1, -1, i);
        pairs.clear();
        cnt.clear();
    }

    repi(0, Q)
        println(ans[i]);

    return 0;
}