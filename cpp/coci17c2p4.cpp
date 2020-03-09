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

const int MN = 41, MSUB = (1 << 20) + 2;
ll N, K,
    h[MN], v[MN];
int bit[MSUB];
void add(int x, int v) {
    for (; x < MSUB; x += x & -x)
        bit[x] += v;
}
int sum(int x) {
    int sum = 0;
    for (; x; x -= x & -x)
        sum += bit[x];
    return sum;
}
vl ranks;
int grank(ll x) {
    return lower_bound(all(ranks), x) - ranks.begin() + 1;
}

void solve(int L, int R, vector<pair<int, ll>> &res, bool takeLast) {
    int sz = R - L + 1, msub = 1 << sz;
    repi(1, msub) {
        int last = -1, fst = -1;
        ll sum = 0;
        bool good = true;
        repj(0, sz) {
            if ((i >> j) & 1) {
                if (fst == -1) fst = h[j + L];
                if (h[j + L] < last) {
                    good = false;
                    break;
                }
                last = h[j + L];
                sum += v[j + L];
            }
        }
        if (good)
            res.emplace_back(takeLast ? last : fst, sum);
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(N, K);
    repi(0, N) scan(h[i], v[i]);

    if (N == 1) {
        println(v[0] >= K);
        return 0;
    }

    int mid = N / 2;
    vector<pair<int, ll>> resL, resR;
    solve(0, mid - 1, resL, true); solve(mid, N - 1, resR, false);
    for (auto pp : resL) ranks.pb(pp.second);
    sort(all(ranks));
    ranks.resize(unique(all(ranks)) - ranks.begin());

    sort(all(resL)); sort(all(resR));
    int sz = resR.size(), ptr = 0, szl = sz(resL), tadd = 0;
    ll tot = 0;
    repi(0, sz) {
        while (ptr < szl && resL[ptr].first <= resR[i].first) {
            add(grank(resL[ptr].second), 1);
            tadd++;
            // dblb("ins"); db(tadd); db(ptr); db(szl); dbp("resL", resL[ptr].first, resL[ptr].second); dbln;
            ptr++;
        }
        // db(i); db(ptr); db(szl); dbp("resR", resR[i].first, resR[i].second); dbln;
        tot += tadd - sum(grank(K - resR[i].second) - 1);
    }
    // db(tot); dbln;
    for (auto pp : resL) tot += pp.second >= K;
    for (auto pp : resR) tot += pp.second >= K;
    println(tot);
    return 0;
}