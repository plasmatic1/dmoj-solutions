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
// template<typename T> inline int sz(const T &x) { return x.size(); }
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

const int MN = 1e5 + 1, LG = 18;
int N, Q,
    A[MN], B[MN], lv[MN];
ll W, 
    weight[MN];
struct Ed {
    int i, v;
    ll w() { return weight[i]; }
};
vec<Ed> g[MN];

int sz[MN];
bool block[MN];

// centroid stuff
int gsz(int c, int p) {
    sz[c] = 1;
    for (auto to : g[c])
        if (to.v != p && !block[to.v])
            sz[c] += gsz(to.v, c);
    return sz[c];
}
int gcent(int c, int p, int req) {
    for (auto to : g[c])
        if (to.v != p && !block[to.v] && sz[to.v] > req)
            return gcent(to.v, c, req);
    return c;
}

// wesley's iterative point update segtree
struct CombinePair {
  using Data = pll;
  using Lazy = pll;
  const Data qdef = {0, 0};
  Data merge(const Data &l, const Data &r) const {
      if (l.first > r.first) {
          return {l.first, max(l.second, r.first)};
      }
      return {r.first, max(r.second, l.first)};
  }
  Data applyLazy(const Data &l, const Lazy &r) const { return r; }
};
struct CombineSingle {
  using Data = ll;
  using Lazy = ll;
  const Data qdef = -LLINF;
  Data merge(const Data &l, const Data &r) const { return max(l, r); }
  Data applyLazy(const Data &l, const Lazy &r) const { return r; }
};
template <class Combine> struct SegmentTreeBottomUp {
  using Data = typename Combine::Data; using Lazy = typename Combine::Lazy;
  Combine C; int N; vector<Data> TR;
  void init(int N0, const Data &vdef) {
    N = N0;
    TR = vec<Data>(N * 2, C.qdef);
    fill(TR.begin() + N, TR.end(), vdef);
    for (int i = N - 1; i > 0; i--)
      TR[i] = C.merge(TR[i * 2], TR[i * 2 + 1]);
  }
  void update(int i, const Lazy &v) {
    for (i += N, TR[i] = C.applyLazy(TR[i], v); i /= 2;)
      TR[i] = C.merge(TR[i * 2], TR[i * 2 + 1]);
  }
  Data query(int l, int r) {
    Data ql = C.qdef, qr = C.qdef;
    for (l += N, r += N; l <= r; l /= 2, r /= 2) {
      if (l & 1) ql = C.merge(ql, TR[l++]);
      if (!(r & 1)) qr = C.merge(TR[r--], qr);
    }
    return C.merge(ql, qr);
  }
};

// Wesley's iterative lazy segtree
struct Combine {
  using Data = ll;
  using Lazy = ll;
  const Data qdef = -LLINF;
  const Lazy ldef = 0;
  Data merge(const Data &l, const Data &r) const { return max(l, r); }
  Data applyLazy(const Data &l, const Lazy &r) const { return l + r; }
  Lazy getSegmentVal(const Lazy &v, int k) const { return v; }
  Lazy mergeLazy(const Lazy &l, const Lazy &r) const { return l + r; }
};
template <class Combine> struct SegmentTreeLazyBottomUp {
  using Data = typename Combine::Data; using Lazy = typename Combine::Lazy;
  Combine C; int N, lgN; vector<Data> TR; vector<Lazy> LZ;
  void apply(int i, const Lazy &v, int k) {
    TR[i] = C.applyLazy(TR[i], C.getSegmentVal(v, k));
    if (i < N) LZ[i] = C.mergeLazy(LZ[i], v);
  }
  void pushup(int i) {
    for (int k = 2; i /= 2; k *= 2) {
      TR[i] = C.merge(TR[i * 2], TR[i * 2 + 1]);
      if (LZ[i] != C.ldef)
        TR[i] = C.applyLazy(TR[i], C.getSegmentVal(LZ[i], k));
    }
  }
  void propagate(int i) {
    int h = lgN + 1, k = 1 << lgN, ii = i >> h;
    for (; h > 0; ii = i >> --h, k /= 2) if (LZ[ii] != C.ldef) {
      apply(ii * 2, LZ[ii], k); apply(ii * 2 + 1, LZ[ii], k); LZ[ii] = C.ldef;
    }
  }
  void init(int n0, const Data vdef) {
      N = n0;
      lgN = __lg(N);
      TR = vector<Data>(N * 2, C.qdef);
      LZ = vector<Data>(N, C.ldef); 
      fill(TR.begin() + N, TR.end(), vdef);
      for (int i = N - 1; i > 0; i--) TR[i] = C.merge(TR[i * 2], TR[i * 2 + 1]);
  }
  void update(int l, int r, const Lazy &v) {
    int l0 = l += N, r0 = r += N, k = 1; propagate(l); propagate(r);
    for (; l <= r; l /= 2, r /= 2, k *= 2) {
      if (l & 1) apply(l++, v, k);
      if (!(r & 1)) apply(r--, v, k);
    }
    pushup(l0); pushup(r0);
  }
  Data query(int l, int r) {
    propagate(l += N); propagate(r += N); Data ql = C.qdef, qr = C.qdef;
    for (; l <= r; l /= 2, r /= 2) {
      if (l & 1) ql = C.merge(ql, TR[l++]);
      if (!(r & 1)) qr = C.merge(TR[r--], qr);
    }
    return C.merge(ql, qr);
  }
};

// maintaining paths that pass through centroid
int fst[LG][MN], lst[LG][MN];
struct DS {
    int n, lg;
    vi tour;
    vector<pair<int, ll>> dis;
    SegmentTreeLazyBottomUp<Combine> seg;
    void dfs(int c, int p, ll cdis) {
        tour.pb(c);
        fst[lg][c] = tour.size() - 1;
        dis.emplace_back(c, cdis);
        for (auto to : g[c]) {
            if (to.v != p && !block[to.v]) {
                dfs(to.v, c, cdis + to.w());
            }
        }
        lst[lg][c] = tour.size() - 1;
    }
    void init(int c, int lg0) {
        // dfs and init tour
        // dblb("init"); db(c); db(pre); dbln;
        lg = lg0;
        dfs(c, -1, 0);
        // init seg
        n = tour.size();
        seg.init(n, -LLINF);
        sort(all(dis));
        for (auto p : dis) {
            int id = fst[lg][p.first];
            seg.update(id, id, LLINF + p.second); // to counteract the infinity (TM)
        }
    }
    ll get(int node) {
        return seg.query(fst[lg][node], lst[lg][node]);
    }
    int getBottomNode(int a, int b) {
        ll da = lower_bound(all(dis), mpr(a, -1LL))->second, db = lower_bound(all(dis), mpr(b, -1LL))->second;
        return da > db ? a : b;
    }
    void inc(int root, ll amt) {
        seg.update(fst[lg][root], lst[lg][root], amt);
    }
};
SegmentTreeBottomUp<CombineSingle> allDist;
SegmentTreeBottomUp<CombinePair> centDist[MN];
ll preAllDist[MN];
DS paths[MN];
int chForEdge[LG][MN];
vi hasEdge[MN]; // centroids that have that edge

void setupEdge(int c, int p, int cent, int chid) {
    for (auto to : g[c]) {
        if (to.v != p && !block[to.v]) {
            hasEdge[to.i].pb(cent);
            chForEdge[lv[cent]][to.i] = chid;
            setupEdge(to.v, c, cent, chid);
        }
    }
}

// build centroid tree
void decomp(int c, int clv) {
    gsz(c, -1);
    if (sz[c] == 1) return;
    int cent = gcent(c, -1, sz[c] / 2);
    lv[cent] = clv;

    paths[cent].init(cent, clv);
    centDist[cent].init(g[cent].size(), mpr(0, 0));
    repi(0, int(g[cent].size())) {
        auto to = g[cent][i];
        if (!block[to.v]) {
            centDist[cent].update(i, mpr(paths[cent].get(to.v), 0));

            setupEdge(to.v, cent, cent, i);
            hasEdge[to.i].pb(cent);
            chForEdge[clv][to.i] = i;
        }
    }

    pll dia = centDist[cent].query(0, g[cent].size() - 1);
    preAllDist[cent] = dia.first + dia.second;
    allDist.update(cent - 1, preAllDist[cent]);

    block[cent] = true;
    for (auto to : g[cent]) {
        if (!block[to.v])
            decomp(to.v, clv + 1);
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(N, Q, W);
    repi(0, N - 1) {
        scn(int, a, b);
        scn(ll, w);
        g[a].pb({i, b});
        g[b].pb({i, a});
        weight[i] = w;
        A[i] = a;
        B[i] = b;
    }

    // init
    allDist.init(N, -LLINF);
    decomp(1, 0);

    ll lastAns = 0;
    while (Q--) {
        scn(ll, e, w);
        e = (e + lastAns) % (N - 1);
        w = (w + lastAns) % W;
        
        // update centroid tree 
        ll dif = w - weight[e];
        for (int cent : hasEdge[e]) {
            int chid = chForEdge[lv[cent]][e], to = g[cent][chid].v;
            auto &ps = paths[cent];

            int bot = ps.getBottomNode(A[e], B[e]);
            ps.inc(bot, dif);
            centDist[cent].update(chid, mpr(ps.get(to), 0));
            pll dia = centDist[cent].query(0, g[cent].size() - 1);
            preAllDist[cent] = dia.first + dia.second;
            allDist.update(cent - 1, preAllDist[cent]);
        }
        weight[e] = w;

        // print ans
        lastAns = allDist.query(0, N - 1);
        println(lastAns);
    }

    return 0;
}