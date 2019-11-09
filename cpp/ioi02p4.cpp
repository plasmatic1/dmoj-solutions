#pragma region
#include <bits/stdc++.h>
using namespace std;
// Common DS shorteners
using ll = long long; using ull = unsigned long long;
using pii = pair<int, int>; using pll = pair<ll, ll>;
template <typename T> using vec = vector<T>;
template <typename K, typename V> using um = unordered_map<K, V>; template<typename K, typename V> using om = map<K, V>;
template <typename K> using us = unordered_set<K>; template <typename K> using os = set<K>;
using vi = vec<int>; using vl = vec<ll>; using vpi = vec<pii>; using vpl = vec<pll>;
// Shorthand Macros
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
#define mpr make_pair
#define pb push_back
// Shorthand Function Macros
#define Fori(a, b) for (int i = a; i < b; i++)
#define Forj(a, b) for (int j = a; j < b; j++)
#define Fork(a, b) for (int k = a; k < b; k++)
#define Forinci(a, b) for (int i = a; i <= b; i++)
#define Forincj(a, b) for (int j = a; j <= b; j++)
#define Forinck(a, b) for (int k = a; k <= b; k++)
#define Cmplt(type) bool operator<(const type &o) const
#define Cmpgt(type) bool operator>(const type &o) const
#define Cmpfn(type) bool operator()(const type &a, const type &b)
// Shorthand Function Macros Part 2
#define Pow2(x) (1LL << (x))
// Shorthand Functions
template<typename T> inline void maxa(T& st, T v) { st = max(st, v); }
template<typename T> inline void mina(T& st, T v) { st = min(st, v); }
inline void setprec(ostream& out, int prec) { out << setprecision(prec) << fixed; }
// Out operators and printing for arrays and vectors
template <typename T> ostream& operator<<(ostream& out,vector<T> iter){out<<"[";for(auto t:iter){out<<t<<", ";}out<<"]";return out;}
template <typename T> void debugArray(T *arr,int sz){cout<<"[";for(int i=0;i<sz;i++){cout<<arr[i]<<", "; } cout<<"]\n";}
template <typename T> void printArray(T *arr,int sz){for(int i=0;i<sz;i++){cout<<arr[i]<<" "; } cout<<"\n";}
#define OUT_OPERATOR(type, propa, propb) ostream& operator<<(ostream& out,type obj){out<<"("<<#propa<<"="<<obj. propa<<", "<<#propb<<"="<<obj. propb<<")";return out;}
// I/O Operations
inline void scan(){}
template<typename F, typename... R> inline void scan(F &f,R&... r){cin>>f;scan(r...);}
template <typename F> inline void println(F t){cout<<t<<'\n';}
template<typename F, typename... R> inline void println(F f,R... r){cout<<f<<" ";println(r...);}
inline void print(){}
template<typename F, typename... R> inline void print(F f,R... r){cout<<f;print(r...);}
// Debugging
int di_; string dnms_, casttostr_ = ",";
void debug_(){cout<<endl;}
template<typename T> string debug_tostring_(T val) { ostringstream os; os << val; return os.str(); }
string debug_name_(string s, string str_val) {
    string ret = ""; if (s[0] == ' ') { ret += ' '; s = s.substr(1); } if (s[0] == '"' && s[s.length() - 1] == '"') { ret += string("[") + str_val + "]"; }
    else if (s.length() == (size_t)3 && s[0] == '\'' && s[2] == '\'') { ret += '(' + str_val + ')'; } else { ret += s + ": " + str_val; } return ret;
} template<typename F, typename... R> void debug_(F f, R... r) {
    int bc = 0; string pr = "";
    while (bc != 0 || dnms_[di_] != ',') { if (dnms_[di_] == '(') { bc++; } else if (dnms_[di_] == ')') { bc--; } pr += dnms_[di_++]; }
    di_++; cout << debug_name_(pr, debug_tostring_(f)) << ","; debug_(r...);
}
#define debug(...) do{dnms_=#__VA_ARGS__+casttostr_,di_=0,debug_(__VA_ARGS__);}while(0)
#pragma endregion

/*
sum(a, x, y) -> a[x]+a[x+1]+...+a[y-1]+a[y]
F[] -> array
T[] -> array
SFXF[] -> Sfx of F[]
SFXT[] -> Sfx of T[]
S -> int
dp[j] -> dp[i] | j > i

dp[i] = sum(F, i, n) * (S + sum(T, i, j - 1)) + dp[j]
dp[i] = SFXF[i] * (S + SFXT[i] - SFXT[j]) + dp[j]

DP STATE: dp[i] -> Best answer if we started from job i 

SFXF[i] * (S + SFXT[i] - SFXT[j]) + dp[j]
SFXF[i] * (S - SFXT[j]) + SFXF[i] * SFXT[i] + dp[j]

m = S - SFXT[j]
x = SFXF[i] // SFXF is non-increasing (non-decreasing because going backwards)
b = dp[j]
EXTRA: SFXF[i] * SFXT[i] (Irrelavent)

mx+b=y
m'x+b'=y
(m-m')x+(b-b')=0
(m-m')x=-(b-b')
x=-(b-b')/(m-m')
*/

const int MN = 10010;
int n, s,
    dp[MN], sfxF[MN], sfxT[MN];
deque<int> dq;

inline int Slope(int j) { return s - sfxT[j]; }
inline int Const(int j) { return dp[j]; }
inline double Intersection(int j0, int j1) { return -(double)(Const(j0) - Const(j1)) / (Slope(j0) - Slope(j1)); }

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, s);

    Fori(0, n) {
        scan(sfxT[i], sfxF[i]);
    }

    for (int i = n - 1; i >= 0; i--) {
        sfxF[i] += sfxF[i + 1];
        sfxT[i] += sfxT[i + 1];
    }

    fill(dp, dp + n, INT_MAX);
    dp[n] = 0;
    dq.pb(n);
    for (int i = n - 1; i >= 0; i--) {
        while (dq.size() >= 2 && Intersection(dq[0], dq[1]) < sfxF[i])
            dq.pop_front();

        dp[i] = sfxF[i] * (s + sfxT[i] - sfxT[dq[0]]) + dp[dq[0]];
        while (dq.size() >= 2 && Intersection(dq[dq.size() - 2], i) < Intersection(dq[dq.size() - 2], dq[dq.size() - 1]))
            dq.pop_back();
        dq.pb(i);        
    }
    
    // debugArray(dp, n);
    println(dp[0]);

    return 0;
}
