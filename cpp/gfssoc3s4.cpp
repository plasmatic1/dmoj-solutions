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

const ll MOD = 1e9 + 7;
const int MR = 101, MC = 22, MCSUB = 1 << MC, BAD = SHRT_MAX;
int r, c,
    dp[2][BAD], revStateMap[BAD];
short stateMap[MCSUB]; // refer to editorial (under 6000 valid bitmasks for C=22)
bitset<MC> curSub, nxtSub;

void madd(int &a, int b) { a = (a + b) % MOD; }

// if star is free
inline bool isFree(int col) {
    if (col == 0 || col == c - 1) return false;
    return !curSub[col] && !nxtSub[col - 1] && !nxtSub[col] && !nxtSub[col + 1];
}

// compress bitmask state
inline int getCompState(int mask) {
    static int ctr = -1;
    if (stateMap[mask] == -1) { 
        // assert()
        stateMap[mask] = ++ctr;
        revStateMap[ctr] = mask;
        assert(ctr < BAD);
    }
    return stateMap[mask];
}

// transition to next row from state
void pushStates(int curRow, int startCol, int toAdd) {
    if (startCol == c) {
        madd(dp[curRow ^ 1][getCompState(nxtSub.to_ulong())], toAdd);
        return;
    }

    // dont add star
    pushStates(curRow, startCol + 1, toAdd);
    if (isFree(startCol)) { // add star
        curSub[startCol] = nxtSub[startCol - 1] = nxtSub[startCol] = nxtSub[startCol + 1] = true;
        pushStates(curRow, startCol + 1, toAdd);
        curSub[startCol] = nxtSub[startCol - 1] = nxtSub[startCol] = nxtSub[startCol + 1] = false;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(r, c);

    // do dp
    memset(stateMap, -1, sizeof stateMap);
    dp[1][getCompState(0)] = 1;
    repi(1, r) {
        int cur = i & 1, nxt = cur ^ 1;
        memset(dp[nxt], 0, sizeof dp[nxt]);
        repj(0, BAD) {
            if (dp[cur][j]) {
                curSub = bitset<MC>(revStateMap[j]);
                pushStates(cur, 0, dp[cur][j]);
            }
        }
    }

    // sum total
    int ans = MOD - 1, cur = r & 1; // MOD - 1 == -1
    repi(0, BAD) {
        madd(ans, dp[cur][i]);
        // db(i); dbbin(i, 4); db(dp[cur][i]); dbln;
    }
    println(ans);

    return 0;
}