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

const int MN = 1e5 + 1;
int n,
    lv[MN];
bool good[MN];
vi g[MN];

ll f(ll x) {
    return x * x + x;
}

ll f2(ll x) {
    return x * x - x;
}

vi ccomp;
bool allow[MN], vis[MN];
void dfsComp(int c, int p) {
    if (!good[c]) return;
    ccomp.pb(c);
    vis[c] = true;
    for (int a : g[c])
        if (a ^ p)
            dfsComp(a, c);
}

void dfs(int c, int p, int l, int lv[MN]) {
    if (!allow[c]) return;
    lv[c] = l;
    for (int a : g[c])
        if (a ^ p)
            dfs(a, c, l + 1, lv);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n);

    Forinci(1, n) {
        ll x;
        scan(x);

        // int it=100;
        ll l = 0, r = 1e8;
        while (l < r) {
            ll mid = (l + r) >> 1;
            // assert(it--);
            // debug(l, r, mid, f(mid), x);
            ll fm = f(mid);
            if (fm > x)
                r = mid - 1;
            else if (fm < x)
                l = mid + 1;
            else
                l = r = mid;
        }
 
        ll l2 = 0, r2 = 2e8;
        while (l2 < r2) {
            ll mid = (l2 + r2) >> 1;

            ll fm = f2(mid);
            if (fm > x)
                r2 = mid - 1;
            else if (fm < x)
                l2 = mid + 1;
            else
                l2 = r2 = mid;
        }

        // debug(l2, r2, f2(l2), f2(r2), x);
        // debug(l, r, f(l), f(r), x);
        // l is ans
        good[i] = f(l) == x || f2(l2) == x;
    }

    Fori(1, n) {
        int a, b;
        scan(a, b);
        g[a].pb(b);
        g[b].pb(a);
    }

    // printArray(good + 1, n);

    memset(lv, -1, sizeof lv);
    
    int dia = -1;
    Forinci(1, n) {
        if (!vis[i]) {
            dfsComp(i, -1);
            if (ccomp.size() == (size_t)0)
                continue;

            for (int x : ccomp) allow[x] = true;

            dfs(i, -1, 0, lv);
            int st = ccomp[0];
            for (int x : ccomp) {
                if (lv[x] > lv[st])
                    st = x;
            }
            dfs(st, -1, 0, lv);
            for (int x : ccomp)
                maxa(dia, lv[x]);

            for (int x : ccomp) allow[x] = false;
            ccomp.clear();
        }
    }
    // debug(a, dia);
    println(dia + 1);

    return 0;
}
