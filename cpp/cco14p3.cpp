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

const ll MOD = 1e9 + 7;
const int MN = 201;
int N, M, W,
    indeg[MN];
ll dp[MN][MN][2];
vec<pair<int, bool>> g[MN];

ll madd(ll a, ll b) { return (a + b) % MOD; }
ll mmul(ll a, ll b) { return (a * b) % MOD; }

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(N, W, M);
    repi(0, M) {
        char t; int a, b;
        scan(t, a, b);
        g[a].emplace_back(b, t == 'D'); // (adjacent player, assuming current player is a werewolf, what is the type of the adjacent player (werewolf or civillian))
        indeg[b]++;
    }

    // init
    repi(1, N + 1) {
        if (g[i].empty()) {
            dp[i][0][0] = 1; // first isn't werewolf
            dp[i][1][1] = 1; // first is werewolf
        }
    }

    // dp
    reprev(i, N, 0) {
        if (!g[i].empty()) {
            repj(0, 2) {
                vec<ll> freq(W + 1, 0), aux(W + 1, 0);
                freq[0] = 1LL;
                for (auto to_ : g[i]) {
                    int to = to_.first; bool t = to_.second;

                    // merge frequency arrays
                    repk(0, W + 1) {
                        rep(l, 0, W + 1) {
                            int target = k + l;
                            if (target > W) continue;

                            // werewolf can only defend werewolf and accuse civillian
                            ll adjAdd = madd(dp[to][l][t], j ? 0LL : dp[to][l][!t]);
                            // db(to); db(t); db(i); db(j); db(k); db(l); db(dp[to][l][0]); db(dp[to][l][1]); db(freq[k]); db(target); db(aux[target]); dbln;
                            aux[target] = madd(aux[target], mmul(freq[k], adjAdd));
                        }
                    }

                    // reset req array stuff for next child
                    swap(aux, freq);
                    fill(all(aux), 0);
                }

                // set dp array to frequency table value
                repk(j, W + 1)
                    dp[i][k][j] = freq[k - j];
                
                // dblb("final dp"); db(i); db(j); dbln;
                // repk(0, W + 1)
                //     db(k), db(dp[i][k][j]), dbln;
            }
        }
    }

    // get total
    vec<ll> freq(W + 1, 0), aux(W + 1, 0);
    freq[0] = 1LL;
    repi(1, N + 1) {
        if (indeg[i] == 0) {
            // merge frequency arrays
            repj(0, W + 1) {
                repk(0, W + 1) {
                    int target = j + k;
                    if (target > W) continue;

                    ll dpAdd = madd(dp[i][k][0], dp[i][k][1]);
                    aux[target] = madd(aux[target], mmul(freq[j], dpAdd));
                }
            }

            // reset req array stuff for next node 
            swap(aux, freq);
            fill(all(aux), 0);
        }
    }
    println(freq[W]);

    return 0;
}