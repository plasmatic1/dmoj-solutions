#pragma region
#include <bits/stdc++.h>
using namespace std;
// Common Type shorteners and int128
using ll = long long; using ull = unsigned long long;
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

using ld = double;
using cd = complex<ld>;

Inop(cd) {
    ll x, y;
    in >> x >> y;
    o.real(x); o.imag(y);
    return in;
}

const int MN = 5e5 + 1;
int N;
cd seq1[MN], seq2[MN];

// power array
const int PC = 2, MOD[PC] = {1000000007, 1000000009}, BASE[PC] = {131, 151};
vec<ll> powSto[PC];
void initPow(int N) {
    for (int i = 0; i < PC; i++) {
        powSto[i].resize(N + 1);
        powSto[i][0] = 1LL;
        for (int j = 1; j <= N; j++)
            powSto[i][j] = (powSto[i][j - 1] * BASE[i]) % MOD[i];
    }
}

// rabin-karp, 43 lines
const ld SCALE = 1e8;
using HashType = ll;
struct Hash {
    vec<ll> hsh[PC];
    void init(int N, ld arr[MN]) {
        for (int i = 0; i < PC; i++)
            hsh[i].resize(N + 1);
        for (int i = 0; i < PC; i++) {
            for (int j = 1; j <= N; j++) {
                hsh[i][j] = (hsh[i][j - 1] * BASE[i] + (ll)round(arr[j - 1] * SCALE)) % MOD[i];
                hsh[i][j] = (hsh[i][j] + MOD[i]) % MOD[i];
            }
        }
    }
    inline ll hash(int i, int L, int R) {
        return (hsh[i][R] - (hsh[i][L - 1] * powSto[i][R - L + 1]) % MOD[i] + MOD[i]) % MOD[i];
    }
    inline HashType hash(int L, int R) {
        HashType ret = 0; 
        for (int i = 0; i < PC; i++) {
            ret <<= 32LL;
            ret |= hash(i, L, R);
        }
        return ret;
    }
    inline ll hashOther(int i, int N, ld arr[MN]) {
        ll ret = 0;
        repj(0, N)
            ret = ((ret * BASE[i]) + (ll)round(arr[j] * SCALE)) % MOD[i];
        ret = (ret % MOD[i] + MOD[i]) % MOD[i];
        return ret;
    }
    inline HashType hashOther(int N, ld arr[MN]) {
        HashType ret = 0;
        for (int i = 0; i < PC; i++) {
            ret <<= 32LL;
            ret |= hashOther(i, N, arr);
        }
        return ret;
    }
};

ld dot(const cd& x, const cd& y) {
    return (conj(x) * y).real();
}
ld cross(const cd& x, const cd& y) {
    return (conj(x) * y).imag();
}

ld mag1[MN], mag2[MN * 2],
    dot1[MN], dot2[MN * 2],
    cross1[MN], cross2[MN * 2];
Hash hmag, hdot, hcross;

void compute(int trueN, int N, cd* pts, ld* magarr, ld* dotarr, ld* crossarr) {
    repi(0, N - 2) {
        cd v1 = pts[(i + 1) % trueN] - pts[i], v2 = pts[(i + 2) % trueN] - pts[(i + 1) % trueN];
        ld mag1 = abs(v1), mag2 = abs(v2), magMul = mag1 * mag2;
        magarr[i] = mag2 / mag1;
        dotarr[i] = dot(v1, v2) / magMul;
        crossarr[i] = cross(v1, v2) / magMul;
        // db(N); db(i); db(magarr[i]); db(dotarr[i]); db(crossarr[i]); dbln;
    }
}

void solve() {
    if (N == 2) { // always true
        println(1); 
        return;
    }    

    int N2 = N * 2;
    compute(N, N, seq1, mag1, dot1, cross1);
    compute(N, N + 2, seq2, mag2, dot2, cross2);
    copy(mag2, mag2 + N - 2, mag2 + N);
    copy(dot2, dot2 + N - 2, dot2 + N);
    copy(cross2, cross2 + N - 2, cross2 + N);
    hmag.init(N2 - 2, mag2);
    hdot.init(N2 - 2, dot2);
    hcross.init(N2 - 2, cross2);

    ll hshMag = hmag.hashOther(N - 2, mag1), hshDot = hmag.hashOther(N - 2, dot1), hshCross = hmag.hashOther(N - 2, cross1);
    // db(hshMag); db(hshDot); db(hshCross); dbln;
    repi(1, N + 1) {
        ll h1 = hmag.hash(i, i + N - 2 - 1), h2 = hdot.hash(i, i + N - 2 - 1), h3 = hcross.hash(i, i + N - 2 - 1);
        // db(i); db(h1); db(h2); db(h3); dbln;
        if (h1 == hshMag && h2 == hshDot && h3 == hshCross) {
            println(i);
            return;
        }
    }

    println(0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    initPow(MN * 2);

    int T; cin >> T;
    while (T--) {
        // Input
        scan(N);
        repi(0, N) scan(seq1[i]);
        repi(0, N) scan(seq2[i]);

        // Reset
        

        solve();
    }
}