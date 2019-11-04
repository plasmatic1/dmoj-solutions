#include <bits/stdc++.h>

using namespace std;

// Common DS shorteners
using ll = long long; using ull = unsigned long long;
using pii = pair<int, int>; using pll = pair<ll, ll>;
template <typename T> using vec = vector<T>;
template <typename K, typename V> using mp = unordered_map<K, V>;
template <typename K> using us = unordered_set<K>;
using vi = vec<int>; using vl = vec<ll>; using vpi = vec<pii>; using vpl = vec<pll>;
// Shorthand Macros
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
#define mpr make_pair
#define pb push_back
// Shorthand Functions
template<typename T> inline void maxa(T& st, T v) { st = max(st, v); }
template<typename T> inline void mina(T& st, T v) { st = min(st, v); }
// Out operators and printing for arrays and vectors
template <typename T> ostream& operator<<(ostream& out,vector<T> iter){out<<"[";for(auto t:iter){out<<t<<", ";}out<<"]";return out;}
template <typename T> void printDebug(T *arr,int sz){cout<<"[";for(int i=0;i<sz;i++){cout<<arr[i]<<", "; } cout<<"]\n";}
template <typename T> void printArray(T *arr,int sz){for(int i=0;i<sz;i++){cout<<arr[i]<<" "; } cout<<"\n";}
#define OUT_OPERATOR(type, propa, propb) ostream& operator<<(ostream& out,type obj){out<<"("<<#propa<<"="<<obj. propa<<", "<<#propb<<"="<<obj. propb<<")";return out;}
// I/O Operations
inline void scan(){}
template<typename F, typename... R> inline void scan(F &f,R&... r){cin>>f;scan(r...);}
inline void println(){cout<<"\n";}
template<typename F, typename... R> inline void println(F f,R... r){cout<<f<<" ";println(r...);}
inline void print(){}
template<typename F, typename... R> inline void print(F f,R... r){cout<<f;print(r...);}
// Debugging
int di_; string dnms_, co_ = ",";
void debug_(){cout<<endl;}
template<typename F, typename... R>
void debug_(F f,R... r){int bc=0;while (bc != 0 || dnms_[di_] != ','){if (dnms_[di_] == '(') {bc++;}else if (dnms_[di_] == ')') {bc--;}cout << dnms_[di_++];}di_++;cout << ": " << f << ",";debug_(r...);}
#define debug(...) do{dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__);}while(0)

// #define debug(...) 

const int MN = 1e5 + 1, LG = 17;
int n, q, 
    pars[MN];
ll sz[MN], tdis[MN];
vi g[MN];

ll gsz(int cur, int par) {
    pars[cur] = par;
    sz[cur] = 1;
    for (int adj : g[cur])
        if (adj ^ par)
            sz[cur] += gsz(adj, cur);
    return sz[cur];
}

ll gdis(int cur, int par) {
    for (int adj : g[cur])
        if (adj ^ par)
            tdis[cur] += gdis(adj, cur);
    return tdis[cur] += sz[cur] - 1;
}

// Set Tdis going towards node I
// tdisTo[i] -> Sum of distance of all nodes going to node I
ll tdisTo[MN];

ll gdis2(int cur) {
    if (tdisTo[cur] != -1) return tdisTo[cur];
    tdisTo[cur] = tdis[cur];
    if (pars[cur] != -1)
        tdisTo[cur] = gdis2(pars[cur]) - sz[cur] + (sz[1] - sz[cur]);
    return tdisTo[cur];
}

// LCA
int lv[MN], lca[LG][MN];

void dfslca(int cur, int par, int clv) {
    lv[cur] = clv;
    lca[0][cur] = par;
    for (int adj : g[cur])
        if (adj ^ par)
            dfslca(adj, cur, clv + 1);
}

void makelca() {
    for (int i = 1; i < LG; i++) {
        for (int j = 1; j <= n; j++) {
            int par = lca[i - 1][j];
            lca[i][j] = par != -1 ? lca[i - 1][par] : -1;
        }
    }
}

int queryLca(int a, int b) {
    if (lv[a] > lv[b]) swap(a, b);
    int delta = lv[b] - lv[a];
    for (int i = 0; i < LG; i++)
        if ((delta >> i) & 1)
            b = lca[i][b];
    if (a == b) return a;
    for (int i = LG - 1; i >= 0; i--) {
        if (lca[i][a] != lca[i][b]) {
            a = lca[i][a];
            b = lca[i][b];
        }
    }
    return lca[0][a];
}

int queryDis(int a, int b) {
    return lv[a] + lv[b] - (lv[queryLca(a, b)] << 1);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, q);

    for (int i = 1; i < n; i++) {
        int a, b;
        scan(a, b);
        g[a].pb(b);
        g[b].pb(a);
    }

    // Dfs sums
    gsz(1, -1);
    gdis(1, -1);
    
    memset(tdisTo, -1, sizeof tdisTo);
    for (int i = 1; i <= n; i++)
        gdis2(i);
    // printArray(tdisTo + 1, n); cout << '\n';

    // Lca
    dfslca(1, -1, 0);
    makelca();

    for (int i = 0; i < q; i++) {
        int a, b;
        scan(a, b);

        ll dif = 0;

        // Take out I
        dif -= (tdis[a] + sz[a]) * (sz[1] - sz[a]);
        dif -= sz[a] * (tdisTo[a] - tdis[a]);

        // Take out J
        dif -= (tdis[b] + sz[b]) * (sz[1] - sz[a] - sz[b]);
        dif -= sz[b] * (tdisTo[b] - tdis[b] - (tdis[a] + queryDis(a, b) * sz[a]));

        // Add in I
        dif += (tdis[a] + sz[a]) * (sz[1] - sz[a] - sz[b]);
        dif += sz[a] * (tdisTo[b] - tdis[b] - (tdis[a] + queryDis(a, b) * sz[a]));

        // Add in J
        dif += (tdis[b] + sz[b]) * (sz[1] - sz[b]);
        dif += sz[b] * (tdisTo[a] - tdis[a] - (tdis[b] + queryDis(a, b) * sz[b]) + (tdis[a] + queryDis(a, b) * sz[a]));

        // debug(i, a, b, pars[a], pars[b], dif);
        // Output
        if (!dif)
            println(0);
        else
            println(dif / abs(dif));
    }   

    return 0;
}
 