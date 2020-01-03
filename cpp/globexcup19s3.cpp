// plasmatic is a big dum dum :)

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

using T = int128;
T gcd(T a, T b) { return b ? gcd(b, a % b) : a; }
struct frac {
    T n, d;
    void reduce() {
        T gcdv = gcd(n, d);
        n /= gcdv; d /= gcdv;
        if (d < 0) { n *= -1; d *= -1; }
    }
    bool less(frac &o) { return n * o.d < o.n * d; }
    bool eq(frac &o) { return n == o.n && d == o.d; }
};

const int MN = 2e5 + 10;
int n;
ll h[MN], d[MN], loc[MN], ans[2][MN];

// slope from j to i
frac slope(int j, int i) {
    frac ret = {h[i] - h[j], loc[i] - loc[j]};
    ret.reduce();
    return ret;
}

// whether j1 is better than j2 at i (j1 < j2 < i)
bool better(int j1, int j2, int i) {
    frac slope1 = slope(j1, i), slope2 = slope(j2, i);
    return slope1.less(slope2) || (slope1.eq(slope2) && h[j1] > h[j2]);
}

// slope
void run(ll ans[MN]) {
    // MAKE LOC PFX SUM
    loc[1] = 0LL;
    repi(2, n + 1) {
        loc[i] = loc[i - 1] + d[i];
    }

    ans[1] = -1;
    deque<int> dq;

    ll maxHeight = -1;
    repi(2, n + 1) {
        // Insert prev value
        dq.pb(i - 1);
        maxa(maxHeight, h[i - 1]);

        // further-back values become better as time goes on (this also knocks out irrelavent values)
        while (dq.size() >= 2 && better(dq[dq.size() - 2], dq.back(), i))
            dq.pop_back();

        ans[i] = h[dq.back()];
        if (ans[i] < h[i]) ans[i] = maxHeight;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // input
    scan(n);

    repi(1, n + 1) {
        scan(h[i]);
    }

    repi(2, n + 1) {
        scan(d[i]);
    }

    // run forwards and backwards
    run(ans[0]);
    reverse(h + 1, h + n + 1);
    reverse(d + 2, d + n + 1);
    // dblb("spl ----- "); dbln;
    run(ans[1]);
    reverse(ans[1] + 1, ans[1] + n + 1);

    repi(1, n + 1) {
        println(ans[0][i], ans[1][i]);
    }

    return 0;
}
