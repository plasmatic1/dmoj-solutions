// fuck u why cant i use sqrt >:(

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

const int MN = 3e5 + 1, LG = 19;
int n, Q;
ll m,
    val[MN];

// rmq
struct {
    pair<ll, int> tb[LG][MN];
    void init(ll arr[MN]) {
        repi(1, n + 1)
            tb[0][i] = {arr[i], i};
        repi(1, LG) {
            int jmp = 1 << (i - 1), end = n - jmp;
            repj(1, n + 1)
                tb[i][j] = min(tb[i - 1][j], tb[i - 1][j + jmp]);
        }
    }
    pair<ll, int> Q(int l, int r) {
        if (l > r) return {0, 0};
        // assert(l <= r);
        int bit = 31 - clz(r - l + 1);
        return min(tb[bit][l], tb[bit][r - (1 << bit) + 1]);
    }
} rmq;

// other sparse table
struct {
    int nxt[LG][MN];
    void init() {
        repi(1, LG) {
            repj(1, n + 1) {
                int to = nxt[i - 1][j];
                nxt[i][j] = to == -1 ? -1 : nxt[i - 1][to];
            }
        }
    }
    int Q(int l, int r) {
        int amt = 0;
        reprev(i, LG - 1, -1) {
            // db(l); db(r); db(amt); db(nxt[i][l]); dbln;
            if (nxt[i][l] <= r && nxt[i][l] != -1) {
                amt += 1 << i;
                l = nxt[i][l];
            }
        }
        return amt;
    }
} jump;

// more shit
struct p {
    int i; ll v;
    Cmplt(p) { return v == o.v ? i < o.i : v < o.v; }
};
vec<p> vals;
ll pfx[MN];

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    scan(n, m, Q);
    repi(1, n + 1)
        scan(val[i]);
    
    // preprocess
    repi(1, n + 1)
        pfx[i] = pfx[i - 1] + val[i];
    rmq.init(pfx);
    // dbarr(pfx, n + 1); dbln;
    repi(1, n + 1)
        vals.pb({i, pfx[i]});
    sort(all(vals));

    set<int> idx;
    for (auto v : vals) {
        auto ptr = idx.upper_bound(v.i);
        jump.nxt[0][v.i] = ptr == idx.end() ? -1 : *ptr;
        idx.insert(v.i);
    }
    jump.init();

    while (Q--) {
        scn(int, a, b);

        auto left = rmq.Q(a, b);
        left.first -= pfx[a - 1];
        if (left.first >= -m)
            println(pfx[b] - pfx[a - 1] + m, 0);
        else {
            int l = a - 1, r = b;
            while (l + 1 < r) {
                int mid = (l + r) >> 1;
                // db(a); db(b); db(l); db(r); db(mid); db(m); db(rmq.Q(a, mid).first - pfx[a - 1]); dbln;
                if (rmq.Q(a, mid).first - pfx[a - 1] >= -m)
                    l = mid;
                else
                    r = mid;
            }

            // db(a); db(b); db(r); dbln;

            println(pfx[b] - pfx[left.second], jump.Q(r, b) + 1);
        }
    }
}