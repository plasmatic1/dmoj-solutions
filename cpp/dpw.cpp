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

struct Seg {
    int l, r; ll v;
};

Cmpfn(cmpr, Seg) { return a.r < b.r; }
Inop(Seg) { in >> o.l >> o.r >> o.v; return in; }

const int MN = 2e5 + 1;
int N, M;
ll dp[MN]; // Solution with first 1 indices assuming that the ith bit was set to 1
Seg segs[MN];

struct {
    ll seg[MN << 2], lazy[MN << 3];
    void push(int i) {
        if (lazy[i]) {
            seg[i] += lazy[i];
            lazy[i << 1] += lazy[i];
            lazy[i << 1 | 1] += lazy[i];
            lazy[i] = 0;
        }
    }
    ll _query(int i, int l, int r, int ql, int qr) {
        if (r < ql || l > qr) return -LLINF;
        push(i);
        if (l >= ql && r <= qr) return seg[i];
        int mid = (l + r) >> 1;
        return max(_query(i << 1, l, mid, ql, qr), _query(i << 1 | 1, mid + 1, r, ql, qr));
    }
    ll _update(int i, int l, int r, int ql, int qr, ll v) {
        push(i);
        if (r < ql || l > qr) return seg[i];
        if (l >= ql && r <= qr) {
            lazy[i] = v;
            push(i);
            return seg[i];
        }
        int mid = (l + r) >> 1;
        return seg[i] = max(_update(i << 1, l, mid, ql, qr, v), _update(i << 1 | 1, mid + 1, r, ql, qr, v));
    }
    int N;
    void init(int n0) { N = n0; }
    ll query(int l, int r) { return _query(1, 1, N, l, r); }
    void update(int l, int r, ll v) { _update(1, 1, N, l, r, v); }
} seg;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    scan(N, M);
    repi(0, M)
        scan(segs[i]);

    // dp
    sort(segs, segs + M, cmpr);
    int sptr = 0;
    seg.init(N);
    seg.update(1, 1, 0);
    repi(2, N + 1) {
        while (sptr < M && segs[sptr].r < i) {
            // dblb("adv ptr"); db(i); db(sptr); dbp("seg", segs[sptr].l, segs[sptr].r, segs[sptr].v); dbp("upd", 1, segs[sptr].l); dbln;
            seg.update(segs[sptr].l, segs[sptr].r, segs[sptr].v);
            sptr++;
        }
        dp[i] = max(0LL, seg.query(1, i - 1));
        // dblb("upd seg ii"); db(i); db(dp[i]); db(add[i]); dba("actual", dp[i] - add[i]); dbln;
        seg.update(i, i, dp[i]);
    }
    while (sptr < M) {
        seg.update(segs[sptr].l, segs[sptr].r, segs[sptr].v);
        sptr++;
    }

    // dbarr(dp, N + 1); dbln;
    // dbarr(add, N + 1); dbln;

    // output
    ll ans = max(0LL, seg.query(1, N));
    println(ans);

    return 0;
}