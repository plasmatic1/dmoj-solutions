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

// gp hash table LOL
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
const ll RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {
    ll operator()(ll x) const { return x ^ RANDOM; }
};
template <typename T, class Hash> using hashset = gp_hash_table<T, null_type, Hash>;
template <typename K, typename V, class Hash> using hashmap = gp_hash_table<K, V, Hash>;

ll madd(ll a, ll b, ll MOD) { return (a + b) % MOD; }
ll msub(ll a, ll b, ll MOD) { return (a - b + MOD) % MOD; }
ll mmul(ll a, ll b, ll MOD) { return (a * b) % MOD; }
ll fpow(ll x, ll y, ll MOD) {
    if (!y) return 1LL;
    return mmul(fpow(mmul(x, x, MOD), y >> 1, MOD), (y & 1) ? x : 1LL, MOD);
}
ll mdiv(ll x, ll y, ll MOD) { return mmul(x, fpow(y, MOD - 2, MOD), MOD); }

const int MN = 50001, PC = 2;
const ll MOD[PC] = {1000000007, 1000000009}, BASE[PC] = {131, 151};
int N;
string s;
vi g[MN];
ll pp[PC][MN];

// cent
using pll = pair<ll, ll>;
int sz[MN];
bool block[MN];
int gsz(int c, int p) {
    sz[c] = 1;
    for (int to : g[c])
        if (to != p && !block[to])
            sz[c] += gsz(to, c);
    return sz[c];
}
int gcent(int c, int p, int h) {
    for (int to : g[c])
        if (to != p && !block[to] && sz[to] > h)
            return gcent(to, c, h);
    return c;
}
pll push(pll &h, int node) {
    return mpr(madd(mmul(h.first, BASE[0], MOD[0]), s[node - 1], MOD[0]),
        madd(mmul(h.second, BASE[1], MOD[1]), s[node - 1], MOD[1]));
}
pll pushFront(pll &h, int node, int lv) {
    lv--;
    return mpr(madd(mmul(pp[0][lv], s[node - 1], MOD[0]), h.first, MOD[0]),
        madd(mmul(pp[1][lv], s[node - 1], MOD[1]), h.second, MOD[1]));
}
// takes the suffix of length len of the hash h (provided the prefix hpre)
ll suff(int baseIdx, int len, ll hpre, ll h) {
    // db(baseIdx); db(len); db(hpre); db(h); db(pp[baseIdx][len]); dbln;
    return msub(h, mmul(pp[baseIdx][len], hpre, MOD[baseIdx]), MOD[baseIdx]);
}
ll comb(ll first, ll second) {
    return (first << 32LL) | second;
}

// mode=0 -> update ds, mode=1 -> query ds
hashset<ll, chash> has;
pll lvStore[MN], lvStoreRev[MN];
bool dfs(int c, int p, int clv, bool mode, pll h, pll hrev, int checkLen) {
    h = push(h, c); hrev = pushFront(hrev, c, clv);
    if (mode && h == hrev && clv >= checkLen) return true;

    // db(c); db(p); db(clv); db(mode); db(h.first); db(h.second); db(hrev.first); db(hrev.second); dbln;

    if (mode) { // query
        lvStore[clv] = h; lvStoreRev[clv] = hrev;
        int prefLv = 2 * clv - checkLen; // can be 0 right?
        // db(len); db(prefLv); dbln;
        if (prefLv >= 0 && lvStore[prefLv] == lvStoreRev[prefLv]) {
            int endLv = clv - prefLv;
            ll find = comb(suff(0, endLv, lvStore[prefLv].first, h.first), suff(1, endLv, lvStore[prefLv].second, h.second));
            if (has.find(find) != has.end()) return true;
        }
    }
    else { // update
        has.insert(comb(h.first, h.second));
    }
    for (int to : g[c]) {
        if (to != p && !block[to]) {
            if (dfs(to, c, clv + 1, mode, h, hrev, checkLen))
                return true;
        }
    }
    return false;
}
int decomp(int c) {
    gsz(c, -1);
    if (sz[c] == 1) return 1;
    
    // dfs children & get centroid
    
    // setup
    int cent = gcent(c, -1, sz[c] >> 1), res = 1;
    pll zero = {0, 0}, base = push(zero, cent); // reverse of length 1 and 0 strings are itself
    lvStore[1] = lvStoreRev[1] = base;
    // dblb("start check children"); db(c); db(cent); db(sz[c]); dbln;

    auto check = [&] (int len) {
        has.clear();
        has.insert(0);
        for (int to : g[cent]) {
            if (!block[to]) {
                if (dfs(to, cent, 2, 1, base, base, len)) {
                    maxa(res, len);
                    return true;
                }
                dfs(to, cent, 1, 0, zero, zero, -1); // update
            }
        }
        has.clear();
        has.insert(0);
        for (auto it = g[cent].rbegin(); it != g[cent].rend(); it++) {
            int to = *it;
            if (!block[to]) {
                if (dfs(to, cent, 2, 1, base, base, len)) {
                    maxa(res, len);
                    return true;
                }
                dfs(to, cent, 1, 0, zero, zero, -1); // update
            }
        }

        return false;
    };

    // dfs
    int l = 0, r = N + 1;
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        // db(l); db(r); db(mid); db(mid*2+1); db(mid*2); dbln;
        if (check(mid * 2 + 1) || check(mid * 2))
            l = mid;
        else
            r = mid;
    }

    // to children
    block[cent] = true;
    for (int to : g[cent])
        if (!block[to])
            maxa(res, decomp(to));
    return res;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(N, s);
    repi(1, N) {
        scn(int, a, b);
        g[a].pb(b);
        g[b].pb(a);
    }
    repi(0, PC)
        repj(0, N + 1)
            pp[i][j] = fpow(BASE[i], j, MOD[i]);

    int ans = decomp(1);
    println(ans);

    return 0;
}