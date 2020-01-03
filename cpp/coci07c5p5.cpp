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

struct loc {
    int x, y, f;
};

struct ed {
    int v; ll w, req;
    Cmplt(ed) { return w > o.w; }
};

const int MN = 3e5 + 1, MK = 1e3 + 1, MX = 1e5 + 1;
int n, k,
    par[MN];
loc locs[MN];
vi row[MX], col[MX];

// dp 
ll dp[MN];
int rowptr[MX], colptr[MX], bestDpRow[MX], bestDpCol[MX];

Cmpfn(cmpByRow, int) { return locs[a].x < locs[b].x; }
Cmpfn(cmpByCol, int) { return locs[a].y < locs[b].y; }

int maxByDp(int a, int b) {
    if (a == -1) return b;
    if (b == -1) return a;
    return dp[a] > dp[b] ? a : b;
}

// int it=100;
void rec(int cur) {
    if (dp[cur] != -1) return;
    int x = locs[cur].x, y = locs[cur].y;
    int colid = lower_bound(all(col[y]), cur, cmpByRow) - col[y].begin(), rowid = lower_bound(all(row[x]), cur, cmpByCol) - row[x].begin();

    // db(cur); dbln;
    // assert(it--);

    // Recurse Children
    if (rowid > 0) 
        rec(row[x][rowid - 1]);
    if (colid > 0)
        rec(col[y][colid - 1]);

    // db(cur); db(rowid); db(colid); dbln;

    // Calculate dp
    if (cur != 1) {
        int best = maxByDp(bestDpRow[x], bestDpCol[y]);
        par[cur] = best;
        dp[cur] = dp[best] >= k ? dp[best] - k + locs[cur].f : -LLINF;
    }
    else {
        dp[1] = locs[1].f;
        par[1] = -1;
    }
    
    // Update PFX MAX arrays
    bestDpRow[x] = maxByDp(bestDpRow[x], cur);
    bestDpCol[y] = maxByDp(bestDpCol[y], cur);
    rowptr[x]++;
    colptr[y]++;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Input
    scan(n, k);
    repi(1, n + 1) {
        scn(int, x, y, f); 
        locs[i] = {x, y, f};
        row[x].pb(i);
        col[y].pb(i);
    }

    repi(1, MX)
        sort(all(row[i]), cmpByCol);
    repi(1, MX)
        sort(all(col[i]), cmpByRow);
    
    // Dp 
    memset(bestDpRow, -1, sizeof bestDpRow);
    memset(bestDpCol, -1, sizeof bestDpCol);
    memset(dp, -1, sizeof dp);
    rec(n);
    println(dp[n]);

    // backtrack
    vi v;
    int cur = n;
    while (cur != -1) {
        v.pb(cur);
        cur = par[cur];
    }
    reverse(all(v));

    println(v.size());
    for (auto x : v)
        println(locs[x].x, locs[x].y);
        
    return 0;
}
