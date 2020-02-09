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

struct Loc {
    int x1, y1, x2, y2;
    Loc fix() {
        Loc ret{x1, y1, x2, y2};
        if (ret.x1 > ret.x2) { swap(ret.x1, ret.x2); }
        if (ret.y1 > ret.y2) { swap(ret.y1, ret.y2); }
        return ret;
    }
    void intersection(Loc &o) {
        maxa(x1, o.x1); maxa(y1, o.y1);
        mina(x2, max(x1 - 1, o.x2)); mina(y2, max(y1 - 1, o.y2));
    }
};

struct Val {
    int x, y, v;
    Cmplt(Val) {
        if (v == o.v) {
            if (x == o.x) return y < o.y;
            return x < o.x;
        }
        return v < o.v;
    }
};

const int MN = 2506, TMN = 2500 * 2500 + 1;
int N, K, Q, M;

// number of distinct shell types stuffs
int bitTsum = 0, sz,
    bit[TMN], dif[MN][MN], idxOf[MN][MN];
vec<Val> counts;

void add(int x, int v) {
    for (; x <= sz; x += x & -x)
        bit[x] += v;
}
int sum(int x) {
    int sum = 0;
    for (; x; x -= x & -x)
        sum += bit[x];
    return sum;
}

// 2D seg
bitset<MN * 4> seg[MN * 4];
bool innerQuery(int idx, int i, int l, int r, int ql, int qr) {
    if (r < ql || l > qr) return false;
    if (l >= ql || r <= qr) return seg[idx][i];
    int mid = (l + r) / 2;
    return innerQuery(idx, i << 1, l, mid, ql, qr) && innerQuery(idx, i << 1 | 1, mid + 1, r, ql, qr);
}
bool innerUpd(int idx, int remIdx, int i, int l, int r, int ql, int qr) {
    if (remIdx == -1) seg[idx][i] = seg[idx][i] || (seg[idx << 1][i] && seg[idx << 1 | 1][i]); // Draw from children
    if (seg[idx][i]) return true;
    if (r < ql || l > qr) return false; // if it was true, this part would've never been reached
    if (l >= ql || r <= qr) {
        if (l == r) {
            if (remIdx != -1) {
                // dblb("rem"); dba("x", remIdx); dba("y", l); dbln;
                add(idxOf[remIdx][l], 1);
                bitTsum++;
            }
            return seg[idx][i] = true;
        }
    }
    int mid = (l + r) / 2;
    return seg[idx][i] = innerUpd(idx, remIdx, i << 1, l, mid, ql, qr) & innerUpd(idx, remIdx, i << 1 | 1, mid + 1, r, ql, qr);
}
void upd(int i, int l, int r, int qlx, int qrx, int qly, int qry) {
    if (innerQuery(i, 1, 1, N - K + 1, qly, qry)) return; // Already set
    if (l > qrx || r < qlx) return;
    if (l >= qlx && r <= qrx && l == r) {
        innerUpd(i, l, 1, 1, N - K + 1, qly, qry);
        return;
    }
    int mid = (l + r) / 2;
    upd(i << 1, l, mid, qlx, qrx, qly, qry); upd(i << 1 | 1, mid + 1, r, qlx, qrx, qly, qry); 
    if (l >= qlx && r <= qrx && l != r) innerUpd(i, -1, 1, 1, N - K + 1, qly, qry);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(N, K, M);
    repi(0, M) {
        int n; scan(n);
        vec<Loc> loc;
        repj(0, n) {
            int x, y;
            scan(x, y);
            loc.pb({max(1, x - K + 1), max(1, y - K + 1), x, y});
        }

        int msub = 1 << n;
        repi(1, msub) {
            Loc rect{-INF, -INF, INF, INF};
            repj(0, n)
                if ((i >> j) & 1)
                    rect.intersection(loc[j]);
            if (rect.x1 > rect.x2 || rect.y1 > rect.y2) continue;
            
            // inclusion/exclusion
            int delta = (popcount(i) & 1) ? 1 : -1; 
            dif[rect.x1][rect.y1] += delta;
            dif[rect.x1][rect.y2 + 1] -= delta;
            dif[rect.x2 + 1][rect.y1] -= delta;
            dif[rect.x2 + 1][rect.y2 + 1] += delta;
        }
    }

    // difference array
    repi(1, N - K + 1 + 1)
        repj(1, N - K + 1 + 1)
            dif[i][j] += dif[i - 1][j] + dif[i][j - 1] - dif[i - 1][j - 1];
    
    // init DS
    counts.pb({-1, -1, -1});
    repi(1, N - K + 1 + 1)
        repj(1, N - K + 1 + 1)
            counts.pb({i, j, dif[i][j]});
    sort(all(counts));
    sz = counts.size() - 1;
    repi(1, sz + 1)
        idxOf[counts[i].x][counts[i].y] = i;
    
    // for (auto x : counts)
    //     db(x.x), db(x.y), db(x.v), dbln;

    // queries
    double div = N - K + 1; div *= div;
    setprec(cout, 7);
    scan(Q);
    while (Q--) {
        int T; scan(T);
        if (T == 1) {
            int xr, yr; scan(xr, yr);
            int xl = max(1, xr - K + 1), yl = max(1, yr - K + 1);
            mina(xr, N - K + 1); mina(yr, N - K + 1);
            upd(1, 1, N, xl, xr, yl, yr);
        }
        else {
            int v; scan(v);
            int idx = lower_bound(all(counts), Val{-INF, -INF, v}) - counts.begin();
            int ans = (sz - idx + 1) - (bitTsum - sum(idx - 1));
            // db(v); db(idx); db(ans); db(bitTsum); dbln;
            println(ans / div);
        }
    }

    return 0;
}