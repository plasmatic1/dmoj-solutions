#pragma region
#include "bits/stdc++.h"
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

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
const ll RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {
    ll operator()(ll x) const { return x ^ RANDOM; }
};
template <typename T, class Hash> using hashset = gp_hash_table<T, null_type, Hash>;
template <typename K, typename V, class Hash> using hashmap = gp_hash_table<K, V, Hash>;

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct Block {
    ll totGcd, totXor;
    hashmap<ll, hashmap<int, int, chash>, chash> gcds;
    void rebuild(ll *val, int l, int r) {
        gcds.clear();
        totXor = totGcd = 0;
        repi(l, r + 1) {
            ll v = val[i];
            totGcd = gcd(totGcd, v);
            totXor ^= v;
            
            auto &curMp = gcds[totGcd];
            if (curMp.find(totXor) == curMp.end()) {
                curMp[totXor] = i;
                // dblb("add"); db(i); db(v); db(totGcd); db(totXor); dbln;
            }
        }
    }
};

const int MN = 1e5 + 1, B = 600, MB = MN / B + 10;
int N, Q, blockCnt,
    bid[MN], L[MB], R[MB];
ll val[MN];
vec<Block*> bs;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(N);
    memset(L, 0x3f, sizeof L);
    repi(0, N) {
        bid[i] = i / B;
        scan(val[i]);
        mina(L[bid[i]], i);
        maxa(R[bid[i]], i);
    }
    blockCnt = bid[N - 1] + 1;

    repi(0, blockCnt) {
        Block *b = new Block;
        b->rebuild(val, L[i], R[i]);
        bs.pb(b);
    }

    scan(Q);
    while (Q--) {
        scn(int, T);
        if (T == 1) {
            scn(int, i, x);
            val[i] = x;
            bs[bid[i]]->rebuild(val, L[bid[i]], R[bid[i]]);
        }
        else {
            scn(ll, x);
            ll curGcd = 0, curXor = 0;
            int ans = INF;
            for (auto b : bs) {
                for (auto &gcdPair : b->gcds) {
                    ll newGcd = gcd(gcdPair.first, curGcd);
                    if (x % newGcd == 0) {
                        ll toFind = (x / newGcd) ^ curXor;
                        // dblb("query"); db(T); db(x); db(newGcd); db(curXor); db(toFind); dbln;
                        if (gcdPair.second.find(toFind) != gcdPair.second.end())
                            mina(ans, gcdPair.second[toFind]);
                    }
                }
                curGcd = gcd(curGcd, b->totGcd);
                curXor ^= b->totXor;
            }
            println(ans == INF ? -1 : ans);
        }
    }

    return 0;
}