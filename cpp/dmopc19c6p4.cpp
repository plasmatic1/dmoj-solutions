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

const int MN = 500001, B = 181, D = 90, D2 = 500000;
int N, Q,
    bit[B][MN], val[MN];
umap<int, int> bsp[MN * 2];

void add(int bit[MN], int x, int v) {
    for (; x <= N; x += x & -x) {
        bit[x] += v;
    }
}
int sum(int bit[MN], int x) {
    int sum = 0;
    for (; x; x -= x & -x) sum += bit[x];
    return sum;
}
void addSp(umap<int, int> &bit, int x, int v) {
    for (; x <= N; x += x & -x) {
        if ((bit[x] += v) == 0)
            bit.erase(bit.find(x));
    }
}
int sumSp(umap<int, int> &bit, int x) {
    int sum = 0;
    for (; x; x -= x & -x) { 
        auto ptr = bit.find(x);
        if (ptr != bit.end()) sum += ptr->second;
    }
    return sum;
}

void ch(int pos, int v, int amt) {
    v += D;
    if (v < 0 || v >= B) {
        v += D2 - D;
        addSp(bsp[v], pos, amt);
    }
    else add(bit[v], pos, amt);
}
int get(int l, int r, int v) {
    v += D;
    if (v < 0 || v >= B) {
        v += D2 - D;
        return sumSp(bsp[v], r) - sumSp(bsp[v], l - 1);
    }
    return sum(bit[v], r) - sum(bit[v], l - 1);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    // db(get(1, N, 0)); dbln;

    scan(N, Q);
    repi(1, N + 1) ch(i, 0, 1);
    while (Q--) {
        int T; scan(T);
        if (T == 3) {
            scn(int, l, r, x);
            println(get(l, r, x));
        }
        else {
            scn(int, x);
            if (T == 1)
                ch(x, val[x]++, -1);
            else 
                ch(x, val[x]--, -1);
            ch(x, val[x], 1);
        }
    }

    return 0;
}