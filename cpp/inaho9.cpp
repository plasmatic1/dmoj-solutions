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

using Vec = vec<ll>;
using Mat = vec<Vec>;
const ll MOD = 1e9 + 7;

Mat make(int N) { return Mat(N, Vec(N)); }
Mat identity(int N) {
    Mat ret = make(N);
    for (int i = 0; i < N; i++)
        ret[i][i] = 1;
    return ret;
}
Mat mul(const Mat &a, const Mat &b) {
    int N = a.size();
    Mat ret = make(N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
                ret[i][j] = (ret[i][j] + a[i][k] * b[k][j]) % MOD;
    return ret;
}
Vec mul(const Mat &a, const Vec &v) {
    int N = a.size();
    Vec ret(N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            ret[i] = (ret[i] + a[i][j] * v[j]) % MOD;
    return ret;
}
Mat exp(Mat a, ll pow) {
    int N = a.size();
    Mat ret = identity(N);
    for (ll cpow = 0; pow >> cpow; cpow++) {
        if ((pow >> cpow) & 1)
            ret = mul(ret, a);
        a = mul(a, a);
    }
    return ret;
}

const int MN = 11;
string s;
int n,
    co[MN];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, s);
    repi(0, n) 
        scan(co[i]);
    
    if (s.length() < 4 && stoi(s) <= n) {
        println(1);
        return 0;
    }

    // subtract 1
    for (int i = s.length() - 1, needSub = true; i >= 0 && needSub; i--) {
        if (s[i] == '0') 
            s[i] = '9';
        else {
            s[i]--;
            needSub = false;
        }
    }
    // db(s); dbln;

    // build initial matrix
    Mat cpow = make(n);
    repi(1, n)
        cpow[i][i - 1] = 1; 
    repi(0, n)
        cpow[0][i] = co[i];

    // fast pow base 10
    Mat funMatrix = identity(n);
    for (int i = s.length() - 1; i >= 0; i--) {
        // multiply
        int dig = s[i] - '0';
        for (int j = 0; j < dig; j++)
            funMatrix = mul(funMatrix, cpow);
        
        // increase to next power of 10
        Mat tmp = cpow;
        for (int j = 0; j < 9; j++)
            tmp = mul(tmp, cpow);
        cpow = tmp;
    }

    // multiply for ans
    Vec ans = Vec(n, 1); 
    ans = mul(funMatrix, ans);
    // db(funMatrix); db(ans); dbln;
    println(ans[n - 1]);

    return 0;
}