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

struct Pt {
    ll x, y, t;
    Cmplt(Pt) { return x < o.x; }
};

const int MN = 1e5 + 1;
int N, M, R, C, K;
vl xs, ys;
Pt pts[MN];

int grnk(vl &v, ll x) {
    return lower_bound(all(v), x) - v.begin() + 1;
}

vl seg, lazy;
void push(int i) {
    if (lazy[i]) {
        seg[i] += lazy[i];
        if (i * 2 < int(lazy.size())) lazy[i * 2] += lazy[i];
        if (i * 2 + 1 < int(lazy.size())) lazy[i * 2 + 1] += lazy[i];
        lazy[i] = 0;
    }
}
ll query(int ql, int qr, int i = 1, int l = 1, int r = ys.size()) {
    if (l > qr || r < ql) return -LLINF;
    push(i);
    if (l >= ql && r <= qr) return seg[i];
    int mid = (l + r) / 2;
    return max(query(ql, qr, i * 2, l, mid), query(ql, qr, i * 2 + 1, mid + 1, r));
}
ll update(int ql, int qr, ll v, int i = 1, int l = 1, int r = ys.size()) {
    push(i);
    if (l > qr || r < ql) return seg[i];
    if (l >= ql && r <= qr) {
        lazy[i] = v;
        push(i);
        return seg[i];
    }
    int mid = (l + r) / 2;
    return seg[i] = max(update(ql, qr, v, i * 2, l, mid), update(ql, qr, v, i * 2 + 1, mid + 1, r));
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(R, C, N, M, K);
    repi(0, K) {
        scn(ll, x, y, t);

        // xs
        xs.pb(x);
        xs.pb(x - 1);
        xs.pb(x + R - 1);
        xs.pb(x + R);
        // ys
        ys.pb(y);
        ys.pb(y - 1);
        ys.pb(y + C - 1);
        ys.pb(y + C);

        pts[i] = {x, y, t};
    }

    // make rnk
    for (auto &x : xs)
        x = max(ll(R), min(ll(N), x));
    sort(all(xs));
    xs.resize(unique(all(xs)) - xs.begin());
    
    for (auto &x : ys)
        x = max(ll(C), min(ll(M), x));
    sort(all(ys));
    ys.resize(unique(all(ys)) - ys.begin());

    // init segtree
    seg.resize(ys.size() * 4);
    lazy.resize(ys.size() * 4);

    // sort points
    sort(pts, pts + K);

    // linesweep
    ll ans = -LLINF;
    int rptr = 0, lptr = 0;
    for (auto x : xs) {
        // dblb("testing"); db(x); dbln;
        while (rptr < K && pts[rptr].x <= x) {
            // dblb("add"); dbp("pt", pts[rptr].x, pts[rptr].y, pts[rptr].t); dbln;
            ll y = pts[rptr].y;
            update(grnk(ys, y), grnk(ys, y + C) - 1, pts[rptr].t);
            rptr++;
        }
        while (lptr < rptr && pts[lptr].x <= x - R) {
            // dblb("rem"); dbp("pt", pts[lptr].x, pts[lptr].y, pts[lptr].t); dbln;
            ll y = pts[lptr].y;
            update(grnk(ys, y), grnk(ys, y + C) - 1, -pts[lptr].t);
            lptr++;
        }

        maxa(ans, query(1, ys.size()));
    }

    println(ans);

    return 0;
}