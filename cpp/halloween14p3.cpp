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

// rabin-karp
const int PC = 2, MOD[PC] = {1000000007, 1000000009}, BASE[PC] = {131, 151};
using HashType = ll;
struct Hash {
    vec<ll> pow[PC], hsh[PC];
    void init(string s) {
        int len = s.length();
        for (int i = 0; i < PC; i++) {
            pow[i].resize(len + 1);
            hsh[i].resize(len + 1);
        }
        for (int i = 0; i < PC; i++) {
            pow[i][0] = 1LL;
            for (int j = 1; j <= len; j++) {
                pow[i][j] = (pow[i][j - 1] * BASE[i]) % MOD[i];
                hsh[i][j] = (hsh[i][j - 1] * BASE[i] + s[j - 1]) % MOD[i];
            }
        }
    }
    inline ll hash(int i, int L, int R) {
        return (hsh[i][R] - (hsh[i][L - 1] * pow[i][R - L + 1]) % MOD[i] + MOD[i]) % MOD[i];
    }
    inline HashType hash(int L, int R) {
        HashType ret = 0; 
        for (int i = 0; i < PC; i++) {
            ret <<= 32LL;
            ret |= hash(i, L, R);
        }
        return ret;
    }
};

const int MN = 5001;
int N;
string s;
Hash h;
vl spells,
    hashes[MN];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(s);
    N = s.length();
    h.init(s);

    // get spells vector
    repi(1, N + 1) {
        int end = N * 2 - i + 1;
        repj(0, i) hashes[j].clear();
        repj(1, end + 1) hashes[(j - 1) % i].pb(h.hash(j, j + i - 1));

        repj(0, i) {
            int ind = j, preind = -1;
            ll pre = LLONG_MAX;
            for (auto hsh : hashes[j]) {
                if (hsh != pre) {
                    preind = ind;
                    pre = hsh;
                }
                else {
                    ll tmp = h.hash(preind + 1, ind + i - 1 + 1);
                    spells.pb(tmp);
                }
                ind += i;
            }
        }
    }

    // count number of unique spells
    sort(all(spells));
    spells.resize(unique(all(spells)) - spells.begin());
    println(spells.size());

    return 0;
}