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
template <typename T> string arrayStr(T *arr,int sz){string ret = "[";for(int i=0;i<sz;i++){ret+=arr[i]+", "; } return ret + "]";}
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
#define dblb(s) cout << "[" << s << "] "
#define dbbin(x, n) cout << (#x) << ": " << bitset<n>(x) << ", "
#define dbarr(x, n) cout << (#x) << ": " << arrayStr((x), (n)) << ", "
#define dbln cout << endl;
#pragma endregion

/*

assume going from j to i where j<i.  Assume current k
Let pfx[] be array of int (pfx sum of values)
Let dp[][] be array of int 

Assume that sequence up to J has been split.  This question actually pretends this in a sorta backwards way:
When we model the DP, we put the current split before all others, so this new split is actually splitting 1..I into 1..J-1 and J..I
dp[k][i] = dp[k - 1][j] + pfx[j] * (pfx[i] - pfx[j])

LINE STUFF
dp[k - 1][j] + pfx[j] * (pfx[i] - pfx[j])
= dp[k - 1][j] + pfx[j] * pfx[i] - pfx[j]^2

m = pfx[j]
x = pfx[i]
b = dp[k - 1][j] - pfx[j]^2
*/

// Note that rep(...), repi(...), repj(...), repk(...) are all for the range [a, b).  And reprev(..., a, b) is (b, a]
const int MN = 1e5 + 1, MK = 206;
int n, k,
    par[MK][MN];
ull v[MN], pfx[MN], dp[2][MN];
deque<int> dqs[2];

inline ll yInt(int k, int j) {
    return dp[k & 1][j] - pfx[j] * pfx[j];
}

inline ll slope(int k, int j) {
    return pfx[j];
}

// i < j
ld intersect(int k, int i, int j) {
    return -(yInt(k, j) - yInt(k, i)) / (ld)(slope(k, j) - slope(k, i));
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, k);

    repi(1, n + 1) {
        scan(v[i]);
        pfx[i] = pfx[i - 1] + v[i];
    }

    repi(0, k + 1) {
        int cur = i & 1, pre = cur ^ 1;
        dqs[cur].clear();
        repj(i + 1, n + 1) {
            if (i > 0) {
                auto &pdq = dqs[pre];
                // db(intersect(i - 1, pdq[0], pdq[1])); db(isnan(intersect(i - 1, pdq[0], pdq[1]))); dbln;

                ld inter = intersect(i - 1, pdq[0], pdq[1]);
                while (pdq.size() >= 2 && pdq[1] < j && (isnan(inter) || inter <= pfx[j])) {
                    pdq.pop_front();
                    if (pdq.size() >= 2)
                        inter = intersect(i - 1, pdq[0], pdq[1]);
                }
                
                int from = pdq[0];
                // db(i); db(j); db(from); dbln;
                dp[cur][j] = dp[pre][from] + pfx[from] * (pfx[j] - pfx[from]);
                par[i][j] = from;
            }

            auto &cdq = dqs[cur];
            while (cdq.size() >= 2 && intersect(i, cdq[cdq.size() - 2], j) <= intersect(i, cdq[cdq.size() - 2], cdq[cdq.size() - 1]))
                cdq.pop_back();
            cdq.pb(j);
        }
    }

    println(dp[k & 1][n]);
    
    // backtrack
    vi path;
    int curi = n, curk = k;
    while (curk >= 0) {
        path.pb(curi);
        curi = par[curk][curi];
        curk--;
    }
    reverse(path.begin(), path.end());
    path.pop_back();
    for (auto x : path)
        print(x, ' ');
    print('\n');

    return 0;
}
