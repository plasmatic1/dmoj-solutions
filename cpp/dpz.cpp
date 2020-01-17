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
Let dp[]: Array
Let h[]: Array
Let C: Int
Given a J and I, J<I
 
dp[i] = dp[j] + (h[i] - h[j])^2 + C
 
dp[j] + (h[i] - h[j])^2 + C
= (h[i] - h[j])^2 + C + dp[j]
= h[i]^2 + h[j]^2 - 2*h[i]*h[j] + C + dp[j]
= h[i]^2 + h[j]^2 - 2*h[i]*h[j] + C + dp[j]
= -2*h[j]*h[i] + (h[j]^2 + dp[j]) + (h[i]^2 + C)
 
y=mx+b
m=2*h[j]
b=h[j]^2 + dp[j]
x=h[i]
 
Extra (always the same no matter the line): h[i]^2 + C
 
mx+b=y
m'x+b'=y
(m-m')x+(b-b')=0
(m-m')x=-(b-b')
x=-(b-b')/(m-m') -> Intercept
 
convex hull trick bois
hugs <3
*/
 
const int MN = 2e5 + 1;
int n;
ll c,
    h[MN], dp[MN];
deque<int> dq;
 
inline ll Slope(ll j) { return -2 * h[j]; }
inline ll Yint(ll j) { return h[j] * h[j] + dp[j]; }
inline double Intersect(ll j0, ll j1) { return -(double)(Yint(j0) - Yint(j1)) / (double)(Slope(j0) - Slope(j1)); }
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    scan(n, c);
 
    Forinci(1, n)
        scan(h[i]);
    
    memset(dp, 0x3f, sizeof dp);
    dp[1] = 0LL;
    dq.pb(1);
    Forinci(2, n) {
        // Forincj(1, i - 1) {
        //     ll d = h[i] - h[j];
        //     mina(dp[i], dp[j] + d * d + c);
        // }
 
        while (dq.size() >= 2 && Intersect(dq[0], dq[1]) < h[i]) {
            // debug(i, Intersect(dq[0], dq[1]), h[i]);
            dq.pop_front();
        }
        
        // debug(i, dq[0]);
        ll d = h[i] - h[dq[0]];
        dp[i] = dp[dq[0]] + d * d + c;
 
        while (dq.size() >= 2 && Intersect(dq[dq.size() - 2], i) < Intersect(dq[dq.size() - 2], dq[dq.size() - 1]))
            dq.pop_back();
        dq.pb(i);
    }
 
    println(dp[n]);
 
    return 0;
}