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

/*
Strategy: Assign each hour that a chef uses to a different meal.  If a chef can work for more than N hours, then treat the extra hours as "leftover hours".  After all meals have had 
K hours assigned, use all remaining leftover hours to finish the rest of the meals.  This assumes that the subset of chefs we picked can work (in total) enough hours to complete all
N meals.  Any remaining leftover hours that weren't used to finish the rest of the meals contribute towards the hours wasted (paid for but not used).

Thus, we can reduce the question down to 0-1 knapsack with the following parameters:

Items: chefs
- weight: Amount of hours a chef can work for
- value: Amount of hours a chef can contribute to the "K chefs per meal" total (equal to min(weight, N))

Therefore, dp[i][j] -> Maximum amount contributed towards (N meals with K chefs) where the total amount of hours paid is j.
We initialize all dp[0][1..] to -infinity and dp[0][0] to 0.

To compute the answer, we check all dp[M][x].  If x >= (sum of hours needed to cook all meals) and dp[M][x] >= N*K, then x-(sum of hours needed to cook all meals) is a potential answer.
Obviously, we just want to find the minimum x that satisfies these conditions.
*/

const int MN = 301, MV = (MN - 1) * (MN - 1) + 1;
int N, M, K,
    B[MN], dp[MV];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(N, M, K);
    int tsum = 0;
    repi(0, N) {
        scn(int, x);
        tsum += x;
        if (x < K) {
            println("Impossible");
            return 0;
        }
    }
    repi(1, M + 1)
        scan(B[i]);

    fill(dp, dp + MV, -INF);
    dp[0] = 0;
    repi(1, M + 1) {
        reprev(j, MV - 1, B[i] - 1)
            maxa(dp[j], dp[j - B[i]] + min(B[i], N));
    }

    int ans = -1;
    repi(tsum, MV) {
        if (dp[i] >= N * K) {
            ans = i - tsum;
            break;
        }
    }
    println(ans == -1 ? "Impossible" : to_string(ans));

    return 0;
}