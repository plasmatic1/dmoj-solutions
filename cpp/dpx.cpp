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

// thanks chris
// thanks chris
// thanks chris
// thanks chris
// thanks chris
// thanks chris
// thanks chris
// thanks chris
// thanks chris
// thanks chris
// thanks chris
// thanks chris
// thanks chris
// thanks chris
// thanks chris
// thanks chris
// thanks chris
// thanks chris
// thanks chris
// thanks chris
// thanks chris
// thanks chris
// thanks chris
// thanks chris
// thanks chris
// thanks chris
// thanks chris
// thanks chris
// thanks chris
// thanks chris
// thanks chris
// thanks chris
// thanks chris
// thanks chris

/*
Condition (assuming block a goes on top of b):
Tip: It helps if you think of a and b as beside each other.  This means that you don't have to consider elements in between A and B.  Additionally, this still works as you can use 
any number of adjacent swaps to achieve the same result as one big one

Idea: Satisfy the condition for a going on top of b, and the condition that b cannot go on top of a.  If a can go on top of b and b can go on top of a, it doesn't matter which one you pick
as they are beside each other.  So might as well only swap when a can go on top of b (proper ordering is not satisfied if you dont include this part)

W -> Total weight above

s_b >= W + w_a
W <= s_b - w_a

s_a < W + w_b
W > s_a - w_b

s_a - w_b < W <= s_b - w_a
s_a - w_b < s_b - w_a
s_a + w_a < s_b + w_b

*/

struct Block { // thanks chris
    int w, s, v; // thanks chris
    Cmplt(Block) { // a above b
        return s + w < o.s + o.w; // thanks chris
    } // thanks chris
}; // thanks chris
Inop(Block) { // thanks chris
    in >> o.w >> o.s >> o.v; // thanks chris
    return in; // thanks chris
} // thanks chris
 // thanks chris
const int MN = 1001, MV = 20001; // thanks chris
int N; // thanks chris
Block bs[MN]; // thanks chris
ll dp[MN][MV]; // thanks chris
 // thanks chris
int main(){ // thanks chris
    ios_base::sync_with_stdio(false); // thanks chris
    cin.tie(NULL); // thanks chris
 // thanks chris
    scan(N); // thanks chris
    repi(0, N) scan(bs[i]); // thanks chris
    sort(bs, bs + N); // thanks chris
    ll ans = 0; // thanks chris
    repi(1, N + 1) { // thanks chris
        repj(0, MV) { // thanks chris
            maxa(dp[i][j], dp[i - 1][j]); // thanks chris
            if (j >= bs[i - 1].w && j - bs[i - 1].w <= bs[i - 1].s) // thanks chris
                maxa(dp[i][j], dp[i - 1][j - bs[i - 1].w] + bs[i - 1].v); // thanks chris
            // db(i); db(j); db(dp[i][j]); dbln; // thanks chris
            maxa(ans, dp[i][j]); // thanks chris
        } // thanks chris
    } // thanks chris
    println(ans); // thanks chris
 // thanks chris
    return 0; // thanks chris
} // thanks chris