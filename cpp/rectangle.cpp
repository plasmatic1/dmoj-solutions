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

struct Fr {
    ll n, d;
    void reduce() {
        ll gv = __gcd(abs(n), abs(d));
        n /= gv; d /= gv;
        if (d < 0) {
            n *= -1; d *= -1;
        }
    }
    Fr(ll a, ll b) : n(a), d(b) { reduce(); }
    Fr(ll x) : n(x), d(1) { reduce(); }
    Fr inv() const { return Fr(d, n); }
    Fr neg() const { return Fr(-n, d); }
    Fr mul(Fr f) const { return Fr(n * f.n, d * f.d); }
    Fr div(Fr f) const { return mul(f.inv()); }
    Fr add(Fr f) const { return Fr(n * f.d + f.n * d, d * f.d); }
    Fr sub(Fr f) const { return add(f.neg()); }
    bool operator==(const Fr o) const { return n == o.n && d == o.d; }
    bool operator<(const Fr o) const { return n == o.n ? d < o.d : n < o.n; }
};
ostream& operator<<(ostream &out, const Fr o) {
    out << o.n << " / " << o.d;
    return out;
}

struct Pt {
    int x, y;
};

Inop(Pt) {
    in >> o.x >> o.y;
    return in;
}

const int MN = 1001;
int N;
Pt pts[MN];
map<Fr, vpi> slopes;

ll disSq(int x, int y) {
    ll xd = pts[y].x - pts[x].x, yd = pts[y].y - pts[x].y;
    return xd * xd + yd * yd;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(N);
    repi(0, N) scan(pts[i]);

    repi(0, N) {
        repj(i + 1, N) {
            if (pts[i].x == pts[j].x) continue;
            Fr slope(pts[j].y - pts[i].y, pts[j].x - pts[i].x);
            slopes[slope].pb(mpr(i, j));
            // db(i); db(j); db(slope); dbln;
        }
    }

    ll ans = 0, ansAxisAligned = 0;
    for (auto &pp : slopes) {
        if (pp.first == Fr(0)) {
            map<pair<ll, int>, int> cnt;
            for (auto &line : pp.second) {
                int minx = min(pts[line.first].x, pts[line.second].x);
                cnt[mpr(disSq(line.first, line.second), minx)]++;
            }
            for (auto &ppp : cnt) {
                ansAxisAligned += (ppp.second * (ppp.second - 1)) / 2;
            }
        }
        else {
            Fr recip = pp.first.inv().neg();
            // db(pp.first); db(recip); dbln;
            map<pair<ll, Fr>, int> cnt;
            for (auto &line : pp.second) {
                int minp = pts[line.first].x < pts[line.second].x ? line.first : line.second;
                // db(line.first); db(line.second); db(disSq(line.first, line.second)); dbln;
                cnt[mpr(disSq(line.first, line.second), Fr(pts[minp].y).sub(recip.mul(Fr(pts[minp].x))))]++;
            }
            for (auto &ppp : cnt) {
                // db(ppp.first.second); db(ppp.second); dbln;
                ans += (ppp.second * (ppp.second - 1)) / 2;
            }
        }
    }
    // db(ans); db(ansAxisAligned); dbln;
    println(ans / 2 + ansAxisAligned);

    return 0;
}