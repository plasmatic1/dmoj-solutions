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

/*
ba&
aba
4

a 2
b 3
a 5

abcdefa
acf

a 1
c 3
f 6
a 7
c 3
f 6
a 7
c 3
f 6
a 7
c 3
f 6

acfdacfacf
acf

a 1
c 2
f 3
a 5
c 6
f 7
a 8
c 9
f 10
a 1
c 2
f 3

*/

const int MN = 7510;
string s, t;
int sl, tl;
ll n;
vi id[26];

// graph
umap<int, pair<ll, ll>> dis[MN]; // for T, 

void resetDis() {
    repi(0, tl)
        dis[i].clear();
}

void makeTo() {
    string ss = s + s;
    repi(0, sl * 2) {
        int let = ss[i] - 'a';
        if (ss[i] == '&')
            repj(0, 26)
                id[j].pb(i);
        else
            id[let].pb(i);
    }
}

inline int to(int idx, int sidx) {
    int nxt = t[(idx + 1) % tl] - 'a';
    auto ptr = upper_bound(id[nxt].begin(), id[nxt].end(), sidx);
    if (ptr == id[nxt].end()) { // definitely not possible
        println(0);
        exit(0);
    }

    // dblb("to"); db(idx); db(sidx); db(nxt); dbln;
    return *ptr;
}

// [ts]idx -> Index of string, [ts]idxm -> Index of string (modded by length)
// int its=100;
ll rec(ll tidx, ll sidx, ll parTidx, ll parSidx) {
    // assert(its--);
    if (sidx >= n * sl)
        return tidx / tl; // actually (tidx + 1) - 1 (+1 because string is 0-indexed, -1 because this index is past the boundary)

    ll tidxm = tidx % tl, sidxm = sidx % sl;

    if (tidx != -1 && sidx != -1 && dis[tidxm].find(sidxm) != dis[tidxm].end()) {
        auto oldDis = dis[tidxm][sidxm];
        ll cycledelta = sidx - oldDis.second, C = (n * sl - parSidx) / cycledelta;
        // dblb("jump"); db(tidx); db(sidx); db(tidxm); db(sidxm); db(dis[tidxm][sidxm]); db(cycledelta); db(C); dbln;

        /*
        sidx + C * cycledelta <= n * sl
        C * cycledelta <= n * sl - sidx
        C <= (n * sl - sidx) / cycledelta
        */

        resetDis();
        return rec(parTidx + C * (tidx - oldDis.first), parSidx + C * cycledelta, tidx, sidx);
    }

    if (tidxm >= 0 && sidxm >= 0) dis[tidxm][sidxm] = {tidx, sidx};
    int add = to(tidxm, sidxm) - sidxm;
    // db(tidx); db(sidx); db(tidxm); db(sidxm); db(add); dbln;
    // if (tidxm >= 0 && sidxm >= 0) { db(t[tidxm]); dbln; }
    return rec(tidx + 1, sidx + add, tidx, sidx);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(s, t, n);
    sl = s.length();
    tl = t.length();

    makeTo();
    ll ans = rec(-1, -1, -1, -1);
    println(ans);

    return 0;
}
