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

// Andrew dong knows all

struct p {
    ll x, y;
};
inline ll d2(const p &a, const p &b) { // distance squared (euclidian)
    ll dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}
inline double d1(const p &a, const p &b) { return sqrt(d2(a, b)); }

Inop(p) {
    in >> o.x >> o.y;
    return in;
}

using pd = pair<double, double>;
using vpd = vec<pd>;
const int MN = 503;
int N;
p pts[MN];
vpd ranges[2][MN];

bool check(int cur) {
    const double eps = 1e-10;
    repi(1, N + 1) {
        double d = d1(pts[i], pts[N + 1]);
        // db(i); db(j); db(d); dbln;
        for (auto range : ranges[cur][i]) {
            if (range.first - eps <= d && d <= range.second + eps)
                return true;
        }
    }
    return false;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(N);
    scan(pts[0], pts[N + 1]);
    repi(1, N + 1) scan(pts[i]);

    // Edge case
    if (pts[0].x == pts[N + 1].x && pts[0].y == pts[N + 1].y) {
        println(0);
        return 0;
    }

    // Initial distances
    repi(1, N + 1) {
        double d = d1(pts[0], pts[i]);
        ranges[1][i].emplace_back(d, d);
    }
    // ans = 1
    if (check(1)) {
        println(1);
        return 0;
    }

    repi(2, N + 1) {
        int cur = i & 1, pre = cur ^ 1;

        repj(1, N + 1) {
            // Compute ranges
            ranges[cur][j].clear();

            vpd reduce;
            repk(1, j) {
                double d = d1(pts[j], pts[k]);
                for (auto &range : ranges[pre][k]) {
                    // db(i); db(j); db(k); db(d); db(range.first); db(range.second); dbln;
                    reduce.emplace_back(max(max(0., range.first - d), d - range.second), d + range.second);
                    // assert(ranges[cur][j].back().first >= 0);
                }
            }

            // Collapse ranges
            sort(all(reduce));
            pd ins{-INF, -INF};
            for (auto &range : reduce) {
                if (range.first > ins.second) {
                    if (ins.first != -INF)
                        ranges[cur][j].pb(ins);
                    ins = range;
                }
                else 
                    maxa(ins.second, range.second);
            }
            if (ins.first != -INF)
                ranges[cur][j].pb(ins);

            // db(i); db(j); dbln;
            // for (auto x : ranges[cur][j]) dbp("r", x.first, x.second), dbln;
        }

        if (check(cur)) {
            println(i);
            return 0;
        }
    }

    println(-1);

    return 0;
}