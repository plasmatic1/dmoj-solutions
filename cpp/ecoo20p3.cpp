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

const bool HAS[10][7] = {{1, 1, 1, 0, 1, 1, 1},
    {0, 0, 1, 0, 0, 1, 0}, 
    {1, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 0, 1, 1},
    {0, 1, 1, 1, 0, 1, 0},
    {1, 1, 0, 1, 0, 1, 1},
    {1, 1, 0, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 1, 0},
    {1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 0, 1, 1}};
const int MN = 501;
string grid[MN];

pii fstLst(int row) {
    int len = grid[row].length(), mx = -INF, mn = INF;
    repi(0, len) {
        if (grid[row][i] == '*') {
            maxa(mx, i);
            mina(mn, i);
        }
    }
    return mpr(mn, mx);
}
bool special(const pii &x, const pii &bounds) {
    if (x.first == INF) return true;
    return x.first != bounds.first && x.second != bounds.second;
}
bool empty(const pii &x) { return x.first == INF; }

int solve(int R, int C) {
    pii bounds{INF, -INF};
    repi(0, R) {
        auto pp = fstLst(i);
        mina(bounds.first, pp.first);
        maxa(bounds.second, pp.second);
    }
    if (bounds.first == bounds.second) return 1; // 1 case

    if ((bounds.second - bounds.first) % 2 != 0) // monkas
        bounds.first--;
    int startCol = bounds.first;

    // do stuff
    int midRow = -1;
    repi(1, R - 1) {
        auto pre = fstLst(i - 1), cur = fstLst(i), nxt = fstLst(i + 1);
        if (empty(cur)) {
            if (!empty(pre) && !empty(nxt)) {
                midRow = i;
                break;
            }
        }
        else {
            if (!empty(pre) && !empty(nxt) && special(cur, bounds)) {
                midRow = i;
                break;
            }
            if (!empty(pre) && !empty(nxt) && cur.first == startCol + 1) {
                midRow = i;
                break;
            }
        }
    }

    // res
    bool curHas[7];
    fill(curHas, curHas + 7, false);

    // check funs
    int c = midRow;

    auto checkHor = [&] () {
        return grid[c][startCol + 1] == '*';
    };
    auto checkVer = [&] (int ind1, int ind2) {
        int cnt = 0;
        repi(0, C)
            cnt += grid[c][i] == '*';
        bool fstIs = grid[c][startCol] == '*';

        if (cnt == 2) {
            curHas[ind1] = curHas[ind2] = true;
        }
        else if (cnt == 1) {
            if (fstIs) curHas[ind1] = true;
            else curHas[ind2] = true;
        }
    };

    // do check
    curHas[3] = checkHor();
    c--;

    checkVer(1, 2);
    while (c >= 0 && !special(fstLst(c), bounds))
        c--;

    if (c >= 0)  // not end
        curHas[0] = checkHor();

    // again
    c = midRow + 1;

    checkVer(4, 5);
    while (c < R && !special(fstLst(c), bounds))
        c++;

    if (c < R) // not end
        curHas[6] = checkHor();

    // Check digit
    repi(0, 10) {
        bool good = true;
        repj(0, 7)
            good &= curHas[j] == HAS[i][j];
        if (good) return i;
    }

    return -1;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scn(int, T);

    for (int ttt = 0; ttt < T; ttt++) {
        // Input
        scn(int, N);
        vi ans;

        repi(0, N) {
            scn(int, r, c);
            repj(0, r)
                scan(grid[j]);
            ans.pb(solve(r, c));
        }

        for (auto x : ans)
            print(x);
        print('\n');
    }

    return 0;
}