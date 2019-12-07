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
#define Cmplt(...) bool operator<(const __VA_ARGS__ &o) const
#define Cmpgt(...) bool operator>(const __VA_ARGS__ &o) const
#define Cmpfn(name, ...) bool name(const __VA_ARGS__ &a, const __VA_ARGS__ &b)
#define Inop(...) istream& operator>>(istream& in, __VA_ARGS__ &o)
#define Outop(...) ostream& operator<<(ostream& out, __VA_ARGS__ o)
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

Outop(pair<int, ll>) {
    out << "(" << o.first << ", " << o.second << ")";
    return out;
}

Outop(map<int, ll>) {
    out << "[";
    for (auto p : o)
        out << "(" << p.first << ", " << p.second << "), ";
    out << "]";
    return out;
}

/*
d: 1 3 5
v: 5 7 9

d: 2 4 5
v: 3 5 8

mx = 0, 0
1
5

mx = 5, 0
1 2
5 8

mx = 5, 3
1 2 3
5 8 10

mx = 7, 3
1 2 3 4
5 8 10 12

mx = 7, 5
1 2 3 4 5
5 8 10 12 14

mx = 9, 5
1 2 3 4 5
5 8 10 12 17

hasFruit: d=4, v=5
1 2 3 4
5 8 10 17

IDEA:
https://codeforces.com/blog/entry/68748

Sparse Representation Idea: https://dmoj.ca/submission/1738880
- vector of pair<int, ll> denoting values
When merging, keep current max for both sparse arrays, and add it to the values when merging
When adding fruits, add it as how you would merge any other value except you remove values past it so that the sparse representation stays monotonous

Sparse Rep. to full solution:
- Small to large merging
- Switch to map<int, ll> and keep a difference array instead of explicit values
*/

struct fruit {
    int d, w;
};
 
const int MN = 1e5 + 1;
int n, m, k;
vi g[MN];
fruit fruits[MN];
bool hasFruit[MN];

using Sparse = map<int, ll>;

Sparse make() {
    Sparse ret;
    ret[0] = 0LL;
    return ret;
}

Sparse stk[MN];

void mergeSparse(int spa, int spb) {
    Sparse &a = stk[spa], &b = stk[spb];
    if (a.size() < b.size()) swap(a, b);

    for (auto p : b)
        a[p.first] += p.second;
}

void rec(int v, int lay) {
    Sparse& ret = stk[lay];
    ret = make();

    for (int to : g[v]) {
        // db(v); db(to); dbln;
        rec(to, lay + 1);
        mergeSparse(lay, lay + 1);
        stk[lay + 1].clear();
    }

    if (hasFruit[v]) {
        ll save = fruits[v].w;
        ret[fruits[v].d] += fruits[v].w;

        auto st = ret.upper_bound(fruits[v].d), en = st;
        while (en != ret.end() && save >= en->second) {
            save -= en->second;
            en++;
        }
        ret.erase(st, en);

        if (en != ret.end())
            en->second -= save;
    }

    // db(v); db(ret); dbln;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, m, k);

    repi(2, n + 1) {
        int p; scan(p);
        g[p].pb(i);
    }

    repi(0, m) {
        int v, d, w; scan(v, d, w);
        hasFruit[v] = true;
        fruits[v] = {d, w};
    }

    // output
    rec(1, 0);
    ll tot = 0LL;
    for (auto p : stk[0])
        tot += p.second;
    println(tot);

    return 0;
}
