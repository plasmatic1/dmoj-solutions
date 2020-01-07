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

const int MN = 1e5 + 1, MV = 1e3 + 1;
int n, Q,
    vals[2][MN];

// prime checking
const int MP = 170; // 1000/ln(1000) ~= 144
bool isPrime[MV], multipleOf[MP][MV];
vi primes;

// preprocess
int workPfx[2][MP][MN];
bool work[2][MP][MN];

__attribute__((optimize("-O3"))) int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // sieve
    memset(isPrime, true, sizeof isPrime);
    isPrime[0] = isPrime[1] = false;
    int ptr = 0;
    repi(2, MV) {
        if (isPrime[i]) {
            primes.pb(i);
            multipleOf[ptr][i] = true;
            for (int j = i * 2; j < MV; j += i) {
                isPrime[j] = false;
                multipleOf[ptr][j] = true;
            }
            ptr++;
        }
    }

    // input
    scan(n, Q);
    repi(1, n + 1)
        scan(vals[0][i]);
    repi(1, n + 1)
        scan(vals[1][i]);

    // preprocess
    int primesSz = primes.size();
    // db(primesSz); dbln;
    repi(0, 2) {
        repj(0, primesSz) {
            repk(1, n + 1) {
                work[i][j][k] = multipleOf[j][vals[i][k]];
                workPfx[i][j][k] = work[i][j][k] + workPfx[i][j][k - 1];
            }
        }
    }

    // stupid constant optimization or some shit idk
    int maxv = max(*max_element(vals[0] + 1, vals[0] + n + 1), *max_element(vals[1] + 1, vals[1] + n + 1)), 
        st = -1;
    repi(0, primesSz) 
        if (primes[i] <= maxv)
            st = i;

    // queries
    while (Q--) {
        scn(int, x1, y1, x2, y2);

        bool foundAnswer = false;
        reprev(i, st, -1) {
            bool curAnsWork = false;

            // 0 -> rows, 1 -> columns
            repj(0, 2) {
                int row = j, col = j ^ 1;
                bool workRowStart = work[row][i][x1];

                if (!workRowStart) {
                    swap(x1, y1);
                    swap(x2, y2);
                    continue;
                }

                // adjacent rows
                curAnsWork |= (x1 + 1 == x2 && workRowStart && work[row][i][x2]) ||
                // row is same
                (x1 == x2 && workRowStart) ||
                // all rows in between work
                (workPfx[row][i][x2] - workPfx[row][i][x1 - 1] == x2 - x1 + 1) ||
                // first row then final col
                (workRowStart && work[col][i][y2]) ||
                // first and final rows and any intermediate col
                (workRowStart && work[row][i][x2] && (workPfx[col][i][y2] - workPfx[col][i][y1 - 1] > 0));

                // swap from row to col
                swap(x1, y1);
                swap(x2, y2);
            }

            if (curAnsWork) {
                println(primes[i]);
                foundAnswer = true;
                break;
            }
        }

        if (!foundAnswer)
            println(-1);
    }

    return 0;
}
