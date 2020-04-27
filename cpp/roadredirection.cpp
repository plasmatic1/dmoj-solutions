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

#define T int
#define Default 0
#define Op(a, b) (a) += (b)
struct BIT {
    int N;
    vector<T> bit;
    void init(int n) { N = n; bit.resize(N + 1); }
    void add(int x, T v) { for (; x <= N; x += x & - x) Op(bit[x], v); }   
    T sum(int x) { T sum = Default; for (; x; x -= x & -x) Op(sum, bit[x]); return sum; }
};
#undef T
#undef Default
#undef Op

const int MN = 2e5 + 1;
int N, Q,
    fst[MN], lst[MN], A[MN], B[MN];
vi euler;
vec<pair<int, bool>> g[MN];
BIT bit;

// dfs for euler and initial state
int dp[MN], par[MN], dep[MN];
bool parEd[MN];

int dfs(int c, int p, bool edState) {
    // db(c); db(p); db(edState); db(chNo_); dbln;
    par[c] = p;
    dep[c] = p == -1 ? 0 : (dep[p] + 1);
    parEd[c] = edState;
    euler.pb(c);
    int tot = 0;
    for (auto to : g[c])
        if (to.first ^ p)
            tot += dfs(to.first, c, to.second) + to.second;
    euler.pb(c);
    return tot;
}

int up(int c) {
    if (dp[c] != -1) return dp[c];
    dp[c] = up(par[c]) + (parEd[c] ? -1 : 1);
    return dp[c];
}

bool minByDep(int a, int b) {
    return dep[a] < dep[b];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(N, Q);
    repi(0, N - 1) {
        scan(A[i], B[i]);
        g[A[i]].emplace_back(B[i], false);
        g[B[i]].emplace_back(A[i], true);
    }

    // init
    memset(dp, -1, sizeof dp);
    euler.pb(-1);
    dp[1] = dfs(1, -1, false);
    // assert(0);
    repi(1, N + 1)
        up(i);
    repi(1, sz(euler)) {
        if (!fst[euler[i]]) fst[euler[i]] = i;
        else if (!lst[euler[i]]) lst[euler[i]] = i;
    }
    bit.init(euler.size() - 1);

    // assert(0);

    // answer queries
    while (Q--) {
        scn(int, t, v);
        if (t == 1) {
            int ans = dp[v] + bit.sum(fst[v]);
            // db(v); db(dp[v]); db(bit.sum(fst[v])); dbln;
            println(ans);
        }
        else {
            // dblb("upd"); db(v); dbln;
            v--;
            int toChildChange = dep[A[v]] < dep[B[v]] ? -1 : 1, bottom = max(A[v], B[v], minByDep);
            bit.add(fst[bottom], toChildChange * 2);
            bit.add(lst[bottom], -toChildChange * 2);
            bit.add(1, -toChildChange);
            bit.add(sz(euler) - 1, toChildChange);
            swap(A[v], B[v]);
        }
    }

    return 0;
}