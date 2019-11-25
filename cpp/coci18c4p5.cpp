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
assume k=K
assume j->i, j<i

dp[i][k] = dp[j][k - 1] + (i - j)/(n - j)

(i - j)/(n - j) + dp[j][k - 1]
i/(n - j) - j/(n - j) + dp[j][k - 1]

M=1/(n - j)
C=-j/(n - j) + dp[j][k - 1]
C=dp[j][k - 1] - j/(n - j)
x = i

y=Mx+C
y=M'x+C'
(M-M')x+(C-C')=0
(M-M')x=-(C-C')
x=-(C-C')/(M-M')
*/

struct dpv {
    double v; int segs;
};

const double PREC = 1e-12;
const int MN = 1e5 + 1;
int n, k;
dpv dp[MN];
deque<int> dq;

inline double Const(int j) {
    return dp[j].v - j / (double)(n - j);
}

inline double Slope(int j) {
    return 1 / (double)(n - j);
}

inline double Intersect(int j0, int j1) { // Assume that j0 < j1
    // double cj0 = Const(j0), cj1 = Const(j1), sj0 = Slope(j0), sj1 = Slope(j1);
    return -(Const(j0) - Const(j1)) / (Slope(j0) - Slope(j1));
}

void run(double segSubConstant) {
    // Reset
    Forinci(0, n)
        dp[i] = {0, 0};
    dq.clear();

    // Run
    dq.pb(0);
    Forinci(1, n) {
        // debug(i, j);
        // Handle case 2
        while (dq.size() >= 2 && Intersect(dq[0], dq[1]) < i) {
            // debug(dq[0], dq[1], Intersect(dq[0], dq[1]));
            dq.pop_front();
        }
        
        dp[i] = {dp[dq[0]].v + (double)(i - dq[0]) / (n - dq[0]) - segSubConstant, dp[dq[0]].segs + 1};
        // debug(i, dq[0], dp[i]);
        
        // Handle case 1
        while (dq.size() >= 2 && Intersect(dq[dq.size() - 2], i) < Intersect(dq[dq.size() - 2], dq[dq.size() - 1]))
            dq.pop_back();
        dq.pb(i);
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, k);

    double l = 0., r = 1e5 + 1;
    while (l + PREC < r) {
        double mid = (l + r) / 2.;
        run(mid);
        // debug(l, r, dp[n].segs);

        if (dp[n].segs > k) // Make adding new segments more costly
            l = mid + PREC;
        else if (dp[n].segs == k)
            break;
        else
            r = mid;
    }

    // debug(l, r, dp[n].segs);
    setprec(cout, 10);
    println(dp[n].v + dp[n].segs * ((l + r) / 2.));

    return 0;
}
