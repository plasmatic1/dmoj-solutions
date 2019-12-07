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

const int MN = 1e4 + 1, MK = 501;
int n, k, w,
    wt[MN], pfx[MN], dp[MK][MN], dpPfxMax[MN];

void solve() {
    // Make pfx sum
    Forinci(1, n)
        pfx[i] = wt[i] + pfx[i - 1];
    
    // dp
    Forinci(0, k)
        fill(dp[i], dp[i] + n + 1, -INF);
    dp[0][0] = 0;
    Forinci(1, k) {
        Forincj(1, n) {
            // Current throw partially obscured by previous
            for (int l = max(0, j - w); l <= j; l++) {
                // debug(i, j, l, dp[i][j], dp[i - 1][l], pfx[j] - pfx[l]);
                maxa(dp[i][j], dp[i - 1][l] + (pfx[j] - pfx[l]));
            }

            // Not obscured
            if (j >= w)
                maxa(dp[i][j], dpPfxMax[j - w] + pfx[j] - pfx[j - w]);
            
            // Throw past the end
            if (j == n) {
                for (int l = max(0, j - w); l <= j; l++)
                    maxa(dp[i][j], dpPfxMax[l] + (pfx[j] - pfx[l]));
            }
            
            // debug(i, j, dp[i][j]);
        }

        // Make pfx max
        fill(dpPfxMax, dpPfxMax + n + 1, -INF);
        Forincj(1, n)
            dpPfxMax[j] = max(dpPfxMax[j - 1], dp[i][j]);
    }

    // debug(dp[1][1]);
    // debug(dp[2][1]);
    // debug(dp[3][1]);

    int ans = -INF;
    Forinci(1, n)
        maxa(ans, dp[k][i]);
    println(ans);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T; scan(T);
    while (T--) {
        // Input
        scan(n, k, w);

        Forinci(1, n)
            scan(wt[i]);

        // Init stuff
        fill(pfx, pfx + n + 1, 0);
        fill(dpPfxMax, dpPfxMax + n + 1, 0);

        solve();
    }

    return 0;
}
