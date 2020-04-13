#pragma GCC optimize "Ofast"
#pragma GCC optimize "unroll-loops"
#pragma GCC target "sse,sse2,sse3,sse4,abm,avx,mmx,popcnt"
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

const ll MOD = 262144, MODMASK = MOD - 1;
const int MN = 262145, B = 350;
int N, Q,
    val[MN], bid[MN];

#define md(x) ((x) & 262143)

// sqrt stuff
const int BCNT = MN / B + 2;
int psum[BCNT][MN], precalc[BCNT][BCNT], LB[BCNT], RB[BCNT];

struct {
    int cqid = -1;
    int cnt[MN], qid[MN];
    void reset() { cqid++; }
    finline int& operator[](int idx) {
        return qid[idx] == cqid ? cnt[idx] : (qid[idx] = cqid, cnt[idx] = 0);
    }
} cnt;

// brute force query
finline ll brute(int L, int R, int bl, int br) {
    ll tot = 0;
    repi(L, R + 1) {
        if (cnt.qid[val[i]] != cnt.cqid) {
            cnt.cnt[val[i]] = psum[bl][val[i]] - psum[br + 1][val[i]];
            cnt.qid[val[i]] = cnt.cqid;
        }
        tot += 2 * cnt.cnt[val[i]]++ + 1;
    }
    return tot;
}

// brute force query
finline ll bruteNo(int L, int R) {
    ll tot = 0;
    repi(L, R + 1) {
        tot += 2 * (cnt[val[i]]++) + 1;
    }
    return tot;
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(N, Q);
    memset(LB, 0x3f, sizeof LB);
    repi(0, N) {
        scan(val[i]);
        bid[i] = i / B;
        mina(LB[bid[i]], i);
        maxa(RB[bid[i]], i);
    }

    // setup blocks
    cnt.reset();
    repi(0, bid[N - 1] + 1) {
        cnt.reset();
        ll cans = 0;
        repj(LB[i], N) {
            int pre = cnt[val[j]]++;
            cans += 2 * pre + 1;
                precalc[i][bid[j]] = md(cans);
            psum[i][val[j]] = pre + 1;
        }
    }

    // answer queries
    ll lastAns = 0;
    while (Q--) {
        int l, r;
        scan(l, r);
        #ifndef NOENCRYPT
        l ^= lastAns; r ^= lastAns;
        #endif
        assert(l <= r); assert(0 <= l && l < N); assert(0 <= r && r < N);

        // do it based on whether any of the midpoints are contained
        int lb = bid[l] + 1, rb = bid[r] - 1;
        if (l == LB[bid[l]]) lb--;
        if (r == RB[bid[r]]) rb++;
        if (lb + 1 >= rb) {
            cnt.reset();
            lastAns = md(bruteNo(l, r));
        }
        else {
            ll ans = precalc[lb][rb];
            cnt.reset();
            ans += brute(l, LB[lb] - 1, lb, rb);
            ans += brute(RB[rb] + 1, r, lb, rb);

            lastAns = md(ans);
        }
        println(lastAns);
    }
    return 0;
}