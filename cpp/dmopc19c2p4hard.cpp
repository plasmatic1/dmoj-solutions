// generating function woohoo!!!!

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
#define pb push_back
#define popcount __builtin_popcount
#define clz __builtin_clz
#define ctz __builtin_ctz
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
#define db(x) cout << (#x) << ": " << x << ", "
#define dblb(s) cout << "[" << s << "] "
#define dbbin(x, n) cout << (#x) << ": " << bitset<n>(x) << ", "
#define dbarr(x, n) cout << (#x) << ": " << arrayStr((x), (n)) << ", "
#define dbln cout << endl;
#pragma endregion

/*
(x+1)(x^3+1)=

x^4+x^3+x+1


x^3 + x^2 + x + 1
*/

using Poly = vl; // first -> coeff, second -> pow

const ll MOD = 1e9 + 7;
const int MN = 2001;
int n, t, Q,
    ts[MN];
ll dp[MN];
Poly poly;

inline void madd(ll &a, ll b) { a = (a + b) % MOD; }
inline void msub(ll &a, ll b) { a = (a - b) % MOD + MOD; while (a >= MOD) a -= MOD; }

// divides a polynomial by (x^pow+1)
inline void div(Poly &p, int pow) {
    int sz = p.size();

    repi(pow, sz) {
        msub(p[i], p[i - pow]);
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, t, Q);

    // make dp
    dp[0] = 1;
    repi(1, n + 1) {
        scan(ts[i]);

        reprev(j, t, ts[i] - 1)
            madd(dp[j], dp[j - ts[i]]);
    }

    // make polynomial
    poly = Poly(dp, dp + t + 1);
    // db(poly); dbln;

    // queries
    while (Q--) {
        scn(int, a, b, q);

        if (ts[a] + ts[b] > q) {
            println(0);
            continue;
        }
        
        // divide by polynomial and sum coefficients
        Poly ansPoly = poly;
        div(ansPoly, ts[a]);
        div(ansPoly, ts[b]);
        // db(a); db(b); db(ansPoly); dbln;

        ll ans = 0LL;
        int en = q - ts[a] - ts[b];
        repi(0, en + 1)
            madd(ans, ansPoly[i]);
        println(ans);
    }

    return 0;
}
