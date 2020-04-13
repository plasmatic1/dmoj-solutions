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

template <int MN, typename T>
struct SegmentTree {
    int n; T seg[MN << 2];
    void setVal(T& a, T b) { mina(a, b); }
    T merge(T a, T b) { return min(a, b); }
    T getDefault() { return LLINF; }
    T _query(int i, int bl, int br, int ql, int qr){
        if(br < ql || bl > qr) return getDefault();
        if(bl >= ql && br <= qr) return seg[i];
        int mid = (bl + br) >> 1;
        return merge(_query(i << 1, bl, mid, ql, qr), _query(i << 1 | 1, mid + 1, br, ql, qr));
    }
    T _update(int i, int bl, int br, int q, T v){
        if(q < bl || q > br) return seg[i];
        if(bl >= q && br <= q) { setVal(seg[i], v); return seg[i]; }
        int mid = (bl + br) >> 1;
        return seg[i] = merge(_update(i << 1, bl, mid, q, v), _update(i << 1 | 1, mid + 1, br, q, v));
    }
    void init(int n0) { n = n0; for (int i = 0; i < 4 * n; i++) seg[i] = getDefault(); }
    T query(int l, int r) { return _query(1, 1, n, l, r); }
    void update(int l, T v) { _update(1, 1, n, l, v); }
};

#define T int
struct Rank {
    vector<T> rank;
    void add(T x) { rank.push_back(x); }
    void init() {
        sort(rank.begin(), rank.end());
        rank.resize(unique(rank.begin(), rank.end()) - rank.begin());
    }
    int get(T x) { return lower_bound(rank.begin(), rank.end(), x) - rank.begin() + 1; }
};
#undef T

struct dev {
    int l, r, x; ll cost;
    Cmplt(dev) { return r < o.r; }
};

const int MM = 1e5 + 1;
int N, M;
dev devs[MM];
ll dp[2][2][MM];
SegmentTree<MM * 3, ll> seg[2];
Rank r;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(M, N);
    repi(1, M + 1) {
        scn(int, a, b, c, d);
        devs[i] = {a, b, c, d};
        r.add(a); r.add(b); r.add(c);
    }
    r.init();

    // init dp
    repi(0, 2) seg[i].init(sz(r.rank));
    memset(dp, 0x3f, sizeof dp);
    repi(1, M + 1) { // dp[0][0][x] is pointless.  Answer must form a Y-shape
        auto &dev = devs[i];

        ll minL = seg[0].query(r.get(dev.l), r.get(dev.r)), minR = seg[1].query(r.get(dev.l), r.get(dev.r));
        if (dev.l == 1) minL = 0;
        if (dev.r == N) minR = 0;
            
        mina(dp[1][0][i], minL + dev.cost);
        mina(dp[0][1][i], minR + dev.cost);
        mina(dp[1][1][i], minL + minR + dev.cost);
        seg[0].update(r.get(dev.x), dp[1][0][i]);
        seg[1].update(r.get(dev.x), dp[0][1][i]);
    }

    ll ans = LLINF;
    repi(1, M + 1)
        mina(ans, dp[1][1][i]);
    println(ans == LLINF ? -1 : ans);

    return 0;
}