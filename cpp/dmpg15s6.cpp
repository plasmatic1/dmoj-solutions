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

struct ed2 {
    int v, w; double wt;
};

struct ed {
    int v; double w;
};

const int ITS = 5;
const int MN = 501;
const double PREC = 0.01;
int n, m;
double bc, 
    dis[MN];
string ba, bb;
vec<ed2> edges;
vec<ed> back[MN];

int rankOf(string s) {
    static unordered_map<string, int> rank;
    static int ctr = 0;

    auto ptr = rank.find(s);
    if (ptr == rank.end())
        return rank[s] = ++ctr;
    return ptr->second;
}

// Note that the NEG cycle must be on an edge that connects to APPLES
// DFS Utils
int id;
bool found = false, vis[MN];
void dfs(int cur) {
    if (vis[cur]) return;
    vis[cur] = true;

    // Edge is from adj.v -> cur
    for (ed adj : back[cur]) {
        // debug(adj.v, cur, dis[adj.v], adj.w, dis[adj.v] * adj.w, dis[cur]);
        found |= dis[adj.v] * adj.w > dis[cur] + PREC;
        dfs(adj.v);
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, m);

    for (int i = 0; i < n; i++) {
        scan(ba);
        rankOf(ba);
    }

    id = rankOf("APPLES");
    for (int i = 1; i <= n; i++)
        dis[i] = 1;
    
    for (int i = 0; i < m; i++) {
        scan(ba, bb, bc);
        int baId = rankOf(ba), bbId = rankOf(bb);
        back[bbId].pb({baId, bc});
        edges.pb({baId, bbId, bc});
    }

    // BELLMAN-FORD
    for (int i = 0; i < n; i++) {
        for (auto ed : edges) {
            maxa(dis[ed.w], dis[ed.v] * ed.wt);
        }
    }
    
    // for (int i = 1; i <= n; i++) {
    //     cout << "i: " << i << ", ";
    //     printDebug(dp[i] + 1, n);
    // }
    
    // Check for Inf Cycle
    dfs(id);
    if (found)
        println("YA");
    else
        println("NAW");

    return 0;
}
