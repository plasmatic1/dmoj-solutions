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

struct ed {
    int i, v;
};

const ll MOD = 1e9 + 7;
const int MN = 2e4 + 1, LG = 15, MM = 1e5 + 1;
int n, m,
    A[MM], B[MM];
vec<ed> g[MN];

// Tarjan 1
int curOrd = 0,
    ord[MN], low[MN];
bool hasNonSimpleCycles = false;
int where[MN];

void tarjan(int cur, int par) {
    ord[cur] = low[cur] = ++curOrd;
    where[ord[cur]] = cur;

    int backc = 0, branchC = 0;
    for (auto adj : g[cur]) {
        if (adj.v ^ par) {
            if (!ord[adj.v]) {
                tarjan(adj.v, cur);
                mina(low[cur], low[adj.v]);
                branchC++;
            }
            else {
                mina(low[cur], ord[adj.v]);
            }

            backc += low[adj.v] < ord[cur];
        }
    }

    // Non-simple cycles
    hasNonSimpleCycles |= backc >= 2;
}

// MST + DSU
int dsu[MN];
int rt(int x) { return dsu[x] == x ? x : dsu[x] = rt(dsu[x]); }
void initDSU() { Forinci(1, n) dsu[i] = i; }
void merge(int x, int y) { dsu[rt(x)] = rt(y); }
bool inMST[MM]; // In MST

// LCA
int lv[MN], par[LG][MN];

void dfs(int cur, int cpar, int clv) {
    par[0][cur] = cpar;
    lv[cur] = clv;
    for (auto adj : g[cur]) 
        if (inMST[adj.i] && (adj.v ^ cpar))
            dfs(adj.v, cur, clv + 1);
}

void initLCA() {
    Fori(1, LG) {
        Forincj(1, n) {
            int cpar = par[i - 1][j];
            par[i][j] = cpar != -1 ? par[i - 1][cpar] : -1;
        }
    }
}

int lca(int a, int b) {
    if (a == b) return a;
    if (lv[a] > lv[b]) swap(a, b);
    int delta = lv[b] - lv[a];
    Fori(0, LG)
        if ((delta >> i) & 1)
            b = par[i][b];
    if (a == b) return a;
    for (int i = LG - 1; i >= 0; i--) {
        if (par[i][a] != par[i][b]) {
            a = par[i][a];
            b = par[i][b];
        }
    }
    return par[0][a];
}

int dis(int a, int b) {
    return lv[a] + lv[b] - (lv[lca(a, b)] << 1);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, m);

    initDSU();

    Fori(0, m) {
        int a, b; scan(a, b);

        g[a].pb({i, b});
        g[b].pb({i, a});
        A[i] = a;
        B[i] = b;

        if (rt(a) ^ rt(b)) {
            merge(a, b);
            inMST[i] = true;
        }
    }

    tarjan(1, -1);

    // Multiple components
    Forinci(1, n) {
        if (!ord[i]) {
            println("safe");
            return 0;
        }
    }

    // cycle stuff
    if (hasNonSimpleCycles) {
        println("safe");
        return 0;
    }

    // LCA
    dfs(1, -1, 0);
    initLCA();

    ll tot = 1;

    Fori(0, m) {
        if (!inMST[i]) {
            int mul = dis(A[i], B[i]) + 1;
            tot = (tot * mul) % MOD;
        }
    }

    println(tot);

    return 0;
}
