#pragma region
#include <bits/stdc++.h>
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

const int MN = 1e5 + 1;
int N, Q,
    dp1[MN], dp2[MN], par[MN], cid[MN]; // cid -> child number
vi vals[MN], g[MN], lhsDown[MN], rhsDown[MN];
vec<pii> lhs[MN], rhs[MN];

// more stuff
int lv[MN];

void dfs(int c, int p, int ccid) {
    par[c] = p;
    cid[c] = ccid;
    lv[c] = p == -1 ? 0 : lv[p] + 1;

    int mx1 = 0, mx2 = 0, sz = g[c].size();
    lhs[c].resize(sz);
    lhsDown[c].resize(sz);
    repi(0, sz) {
        int to = g[c][i];
        if (to ^ p) {
            dfs(to, c, i);
            dp2[c] = max(dp2[c], dp2[to]);
            int alt = dp1[to] + 1;
            if (alt >= mx1) {
                mx2 = mx1;
                mx1 = alt;
            }
            else if (alt >= mx2)
                mx2 = alt;
        }
        lhs[c][i] = {mx1, mx2};
        lhsDown[c][i] = i > 0 ? max(lhsDown[c][i - 1], dp2[to]) : dp2[to];
    }
    dp1[c] = mx1;
    dp2[c] = max(dp2[c], mx1 + mx2);

    // build rhs 
    mx1 = 0, mx2 = 0;
    rhs[c].resize(sz);
    rhsDown[c].resize(sz);
    reprev(i, sz - 1, -1) {
        int to = g[c][i];
        if (to ^ p) {
            int alt = dp1[to] + 1;
            if (alt >= mx1) {
                mx2 = mx1;
                mx1 = alt;
            }
            else if (alt >= mx2)
                mx2 = alt;
        }
        rhs[c][i] = {mx1, mx2};
        rhsDown[c][i] = i < sz - 1 ? max(rhsDown[c][i + 1], dp2[to]) : dp2[to];
    }

    // db(c); db(dp1[c]); db(dp2[c]); dbln;
}

int top2(int a, int b, int c, int d) {
    static int vals[4];
    vals[0] = a; vals[1] = b; vals[2] = c; vals[3] = d;
    sort(vals, vals + 4);
    return vals[3] + vals[2];
}

int dpup1[MN], dpup2[MN];

void up(int c) {
    if (dpup1[c] != -1) return;
    if (par[c] == -1) {
        dpup1[c] = dpup2[c] = 0;
        return;
    }
    up(par[c]); // first do parent

    // we do not speak of this
    int gpsz = g[par[c]].size(), cc = cid[c];
    vi vals{0, 0};
    if (cc > 0) {
        auto tmp = lhs[par[c]][cc - 1];
        vals.pb(tmp.first);
        vals.pb(tmp.second);
        int tmp2 = lhsDown[par[c]][cc - 1];
        dpup1[c] = max(dpup1[c], max(tmp.first, tmp.second));
        dpup2[c] = max(dpup2[c], tmp2);
    }
    if (cc < gpsz - 1) {
        auto tmp = rhs[par[c]][cc + 1];
        vals.pb(tmp.first);
        vals.pb(tmp.second);
        int tmp2 = rhsDown[par[c]][cc + 1];
        dpup1[c] = max(dpup1[c], max(tmp.first, tmp.second));
        dpup2[c] = max(dpup2[c], tmp2);
    }
    dpup1[c] = max(dpup1[c], dpup1[par[c]]);
    dpup1[c]++;
    vals.pb(dpup1[par[c]] - 1 + 1);
    sort(all(vals), greater<int>());
    // db(c); db(vals); db(dpup1[c]); dbln;
    dpup2[c] = max(dpup2[c], vals[0] + vals[1]);
    dpup2[c] = max(dpup2[c], dpup2[par[c]]);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(N, Q);
    repi(1, N) {
        int a, b;
        scan(a, b);
        g[a].pb(b);
        g[b].pb(a);
    }

    // preprocess
    memset(dpup1, -1, sizeof dpup1);
    dfs(1, -1, -1);
    // dbarr(dp1 + 1, N); dbln;
    repi(1, N + 1)
        up(i);
    repi(1, N + 1) {
        for (int to : g[i])
            if (to ^ par[i])
                vals[i].pb(dp2[to]);
        if (i != 1) vals[i].pb(dpup2[i]);
        sort(all(vals[i]), greater<int>());
        // assert(vals[i].size() == g[i].size());

        // db(i); db(vals[i]); dbln;
    }

    // answer queries
    while (Q--) {
        int a, b;
        scan(a, b);
        if (vals[a].size() < (size_t)b)
            println(-1);
        else
            println(vals[a][b - 1] + 1);
    }

    return 0;
}