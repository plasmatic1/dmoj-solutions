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

const int C = 16, CD = 4;
using Func = vec<int>;

// function composition
void compose(Func &f, const Func &a, const Func &b) {
    f.resize(C);
    repi(0, C)
        f[i] = a[b[i]];
}

const int MN = 100001;
int n, q;
Func ops[MN], seg[MN << 2];

void build(int i, int l, int r) {
    if (l == r) return void(seg[i] = ops[l]);
    int mid = (l + r) >> 1;
    build(i << 1, l, mid); build(i << 1 | 1, mid + 1, r);
    compose(seg[i], seg[i << 1 | 1], seg[i << 1]);
}
void upd(int i, int l, int r, int q, Func &v) {
    if (l > q || r < q) return;
    if (l == q && r == q) return void(seg[i] = v);
    int mid = (l + r) >> 1;
    upd(i << 1, l, mid, q, v); upd(i << 1 | 1, mid + 1, r, q, v);
    compose(seg[i], seg[i << 1 | 1], seg[i << 1]);
}

// building function
const int DIR[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int grid[CD][CD], tmpGrid[CD][CD];
Func curFunc;
void initGrid() {
    int ptr = -1;
    repi(0, CD)
        repj(0, CD)
            grid[i][j] = ++ptr;
}
void rot(int r, int c, int rad) {
    if (rad == 1) return;
    int x = r, y = c, its = 4 * rad - 4;
    repi(0, its) {
        int dirIdx = i / (rad - 1);
        tmpGrid[x + DIR[dirIdx][0]][y + DIR[dirIdx][1]] = grid[x][y];
        x += DIR[dirIdx][0];
        y += DIR[dirIdx][1];
    }
    x = r, y = c;
    repi(0, its) {
        int dirIdx = i / (rad - 1);
        grid[x][y] = tmpGrid[x][y];
        x += DIR[dirIdx][0];
        y += DIR[dirIdx][1];
    }
}
void assignCurFun() {
    curFunc.resize(C);
    int ptr = 0;
    repi(0, CD) 
        repj(0, CD) 
            curFunc[grid[i][j]] = ptr++;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, q);
    repi(1, n + 1) {
        int r, c, k;
        scan(r, c, k);

        // set up function
        initGrid();
        rot(r - 1, c - 1, k);
        assignCurFun();
        ops[i] = curFunc;
    }
    build(1, 1, n);

    // answer queries
    while (q--) {
        int idx, r, c, k;
        scan(idx, r, c, k);

        // set up rotation
        initGrid();
        rot(r - 1, c - 1, k);
        assignCurFun();
        upd(1, 1, n, idx, curFunc);

        // output
        repi(0, C) {
            int to = seg[1][i], x = to / 4, y = to % 4;
            grid[x][y] = i;
        }
        repi(0, CD) {
            repj(0, CD - 1)
                print(grid[i][j] + 1, ' ');
            println(grid[i][CD - 1] + 1);
        }
    }

    return 0;
}