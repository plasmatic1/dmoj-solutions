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

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

Cmpfn(cmpVec, vi) {
    assert(a.size() == b.size());
    repi(0, int(a.size()))
        if (a[i] != b[i])
            return a[i] < b[i];
    return false;
}

const int MN = 5e4 + 1;
int N,
    seq[MN];

bool done[MN];
bool sortByK(int sz, int k, vi &res) {
    if (done[k]) return false;
    static vi vals[MN];
    static int cnt[MN];

    // "countingsort"
    repi(0, sz) vals[i].clear();
    repi(0, N) vals[seq[i]].pb(i % k);

    assert(int(res.size()) == N);
    memset(cnt, 0, sizeof cnt);
    repi(0, sz) {
        for (auto group : vals[i]) {
            // db(i); db(group); db(k); db(cnt[group]); db(cnt[group] * k); db(cnt[group]*k+group); dbln;
            res[k * cnt[group] + group] = i;
            cnt[group]++;
        }
    }
    // db(res); dbln;
    return done[k] = true;
}

// coord compress
struct {
    vi comp;
    void init() {
        repi(0, N) comp.pb(seq[i]);
        sort(all(comp)); comp.resize(unique(all(comp)) - comp.begin());
    }
    inline int c(int x) { return lower_bound(all(comp), x) - comp.begin(); }
    inline int u(int x) { return comp[x]; }
} C;

// indexOf
vi idOf[MN];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vi tmp;
    scan(N);
    repi(0, N) {
        scan(seq[i]);
        tmp.pb(seq[i]);
    }
    sort(all(tmp));

    // remove all beginning elements already in order
    int toRemove = 0;
    repi(0, N) {
        if (seq[i] == tmp[i]) {
            toRemove++;
            print(seq[i], ' ');
        }
        else break;
    }
    copy(seq + toRemove, seq + N, seq);
    N -= toRemove;

    // elements are all sorted already
    if (!N) {
        print('\n');
        return 0;
    }

    // coord. compress
    C.init();
    repi(0, N) {
        seq[i] = C.c(seq[i]);
        idOf[seq[i]].pb(i);
    }

    // find smallest element out of order, brute force with all those indexes
    int mx = *max_element(seq, seq + N);
    vi ans(N, INF), tmpAns(N, INF);
    bool found = false;
    for (int initialElem = 0; initialElem < mx; initialElem++) {
        for (int i : idOf[initialElem]) {
            // only the prime numbers matter
            vi ks;
            int tmp = i;
            for (int j = 2; j * j <= tmp; j++) {
                if (tmp % j == 0) {
                    ks.pb(j);
                    while (tmp % j == 0) tmp /= j;
                }
            }
            if (tmp > 1) ks.pb(tmp);

            // try all valid K
            for (int k : ks) {
                if (!found) sortByK(C.comp.size(), k, ans);
                else {
                    bool isNewK = sortByK(C.comp.size(), k, tmpAns);
                    if (isNewK && cmpVec(tmpAns, ans)) // short circuit abuse :)
                        swap(tmpAns, ans);
                }
                found = true;
            }
        }
        if (found) break; // found working element
    }
    if (!found)
        copy(seq, seq + N, ans.begin());

    // output
    // db(ans); dbln;
    for (auto x : ans) print(C.u(x), ' ');
    print('\n');

    return 0;
}