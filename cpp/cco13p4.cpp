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

const int MX = 6101, D = 3010, MX2 = 2101;
int L, Q;
bool exist[MX2][MX2 >> 1];

void transform(int &x, int &y) {
    x = x + y;
    y = x - 2 * y;
}

// bit
int bit[MX][MX];
void add(int x, int y, int v) {
    x += D; y += D;
    for (; x < MX; x += x & -x)
        for (int cy = y; cy < MX; cy += cy & -cy)
            bit[x][cy] += v;
}
int sum(int x, int y) {
    int sum = 0;
    x += D; y += D;
    for (; x; x -= x & -x)
        for (int cy = y; cy; cy -= cy & -cy)
            sum += bit[x][cy];
    return sum;
}

int qrange(int x10, int y10, int x20, int y20) {
    int x1 = min(x10, x20), y1 = min(y10, y20), x2 = max(x10, x20), y2 = max(y10, y20);
    return sum(x2, y2) - sum(x1 - 1, y2) - sum(x2, y1 - 1) + sum(x1 - 1, y1 - 1);
}

int qpoint(int x, int y) {
    int x1 = x, y1 = y, x2 = -x + 2, y2 = y;
    transform(x1, y1);
    transform(x2, y2);
    return qrange(x1, y1, x2, y2);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(L, Q);
    while (Q--) {
        char T;
        int a, b;
        scan(T, a, b);

        if (T == 'S') {
            if (exist[a][b] || exist[a][b + 1])
                println("No");
            else {
                int ans = qpoint(a, b) + qpoint(a, b + 1);
                println(ans);
            }
        }
        else if (T == 'E') {
            if (a > L + 1010) continue;
            exist[a][b] = true;
            transform(a, b);
            add(a, b, 1);
        }
        else if (T == 'L') {
            if (a > L + 1010) continue;
            exist[a][b] = false;
            transform(a, b);
            add(a, b, -1);
        }
    }

    // find far point
    int fst = INF, snd = INF;
    repi(1, 1011) {
        repj(1, 1001) {
            if (exist[L + i][j]) continue;
            int ans = qpoint(L + i, j);
            // db(i), db(j), db(ans), dbln;
            if (ans <= fst) {
                snd = fst;
                fst = ans;
            }
            else if (ans <= snd)
                snd = ans;
        }
    }
    println(fst + snd);
    // db(fst); db(snd); dbln;

    return 0;
}