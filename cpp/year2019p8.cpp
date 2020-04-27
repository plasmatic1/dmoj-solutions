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

const int MN = 1e5 + 1, MN2 = 5e5 + 1;
int N, M;
ll X[MN], L[MN], R[MN];

// tarj
vi g[MN2], g2[MN2];
int cord = 0, compNum = 0, 
    to[MN2], low[MN2], ord[MN2], cost[MN2];
bitset<MN2> instk;
stack<int> stk;
void tarj(int c) {
    ord[c] = low[c] = ++cord;
    instk[c] = true; stk.push(c);
    for (int to : g[c]) {
        if (!ord[to]) {
            tarj(to);
            mina(low[c], low[to]);
        }
        else if (instk[to])
            mina(low[c], ord[to]);
    }
    if (ord[c] == low[c]) {
        int u; compNum++;
        do {
            u = stk.top();
            stk.pop();
            instk[u] = false;
            to[u] = compNum;
            cost[compNum] += u <= N;
        } while (u != c);
    }
}

// Construct graph
void insExit(int i, int l, int r, int ql, int qr, int ind) {
    if (ql > r || qr < l) return;
    if (l >= ql && r <= qr) {
        g[N + i].pb(ind);
        return;
    }
    int mid = (l + r) / 2;
    insExit(i * 2, l, mid, ql, qr, ind); insExit(i * 2 + 1, mid + 1, r, ql, qr, ind);
}
void insEnter(int i, int l, int r, int q, int ind) {
    if (l > q || r < q) return;
    if (l <= q && q <= r) {
        g[ind].pb(N + i);
        if (l == r) return;
    }
    int mid = (l + r) / 2;
    insEnter(i * 2, l, mid, q, ind); insEnter(i * 2 + 1, mid + 1, r, q, ind);
}

// dp
int dp[MN2];
bitset<MN2> vis;
void dfs(int c) {
    if (vis[c]) return;
    vis[c] = true;
    dp[c] = 0;
    for (int to : g2[c]) {
        dfs(to);
        maxa(dp[c], dp[to]);
    }
    dp[c] += cost[c];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(N, M);
    repi(1, M + 1)
        scan(X[i], L[i], R[i]);

    // Create graph
    repi(1, M + 1)
        insExit(1, 1, N, L[i], R[i], X[i]);
    repi(1, N + 1)
        insEnter(1, 1, N, i, i);

    // Tarjan
    int graphSz = N * 5;
    repi(1, graphSz + 1)
        if (!ord[i])
            tarj(i);
    repi(1, graphSz + 1) {
        int a = to[i];
        for (int to_ : g[i]) {
            int b = to[to_];
            if (a != b)
                g2[a].pb(b);
        }
    }
    repi(1, compNum + 1) {
        sort(all(g2[i]));
        g2[i].resize(unique(all(g2[i])) - g2[i].begin());
    }

    // dp and get ans
    dfs(to[1]);
    println(dp[to[1]]);

    return 0;
}