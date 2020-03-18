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
const int PC = 2, MOD[PC] = {1000000007, 1000000009}, BASE[PC] = {131, 10007};
using HashType = ll;
struct Hash {
    vec<ll> pow[PC], hsh[PC];
    void init(string s, char zeroChar = 0) {
        int len = s.length();
        for (int i = 0; i < PC; i++) {
            pow[i].resize(len + 1);
            hsh[i].resize(len + 1);
        }
        for (int i = 0; i < PC; i++) {
            pow[i][0] = 1LL;
            for (int j = 1; j <= len; j++) {
                pow[i][j] = (pow[i][j - 1] * BASE[i]) % MOD[i];
                hsh[i][j] = (hsh[i][j - 1] * BASE[i] + s[j - 1] - zeroChar) % MOD[i];
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
    inline ll hashOther(int i, string &s, char zeroChar = 0) {
        ll ret = 0; for (auto ch : s) ret = (ret * BASE[i] + ch - zeroChar) % MOD[i];
        return ret;
    }
    inline HashType hashOther(string &s, char zeroChar = 0) {
        HashType ret = 0;
        for (int i = 0; i < PC; i++) {
            ret <<= 32LL;
            ret |= hashOther(i, s, zeroChar);
        }
        return ret;
    }
};

const int MN = 2011;
int N, M;
string s,
    mat[MN];
Hash h;
uset<ll> has;
bitset<MN> reach[MN];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(s, M);
    N = s.length();
    repi(0, M) scan(mat[i]);
    h.init(s);

    repi(0, M) {
        ll hsh = h.hashOther(mat[i]);
        has.insert(hsh);
    }

    // do the dp
    reprev(i, N, 0) {
        repj(i + 1, N + 2) {
            assert(h.hash(i, j - 1) >= 0);
            if (has.find(h.hash(i, j - 1)) != has.end()) {
                reach[i][j] = true;
                reach[i] |= reach[j];
            }
        }
    }

    // get ans
    int ans = 0;
    repi(1, N + 1) ans += reach[i].count();
    println(ans);

    return 0;
}