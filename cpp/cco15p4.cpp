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

/*
If we have a row like:

EEESEEE...
-------
1234567...

The edges should be the following:

1->2
2->3
3->4
3->5
5->6
6->7

Each node should only depend on nodes to the right (or whichever direction it faces) until it hits the next node that is in the same direction
*/

struct p {
    int x, y;
};

const int MN = 2e3 + 1, MN2 = MN * MN;
int n, m;
p pos[MN2];
char grid[MN][MN];
vi g[MN2];

inline int getNum(int i, int j) {
    return i * m + j;
}

inline int getF(int x) {
    return x / m;
}

inline int getS(int x) {
    return x % m;
}

bool vis[MN2];
void dfs(int cur) {
    if (vis[cur]) return;
    vis[cur] = true;
    for (int adj : g[cur])
        dfs(adj);
    
    int i = getF(cur), j = getS(cur);
    if (grid[i][j] != '.') {
        print('(', i, ',', j, ")\n");
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, m);

    for (int i = 0; i < n; i++) {
        scan(grid[i]);
    }

    // N/S
    for (int j = 0; j < m; j++) {
        // North
        vi last;
        for (int i = 0; i < n; i++) {
            if (grid[i][j] == 'N') {
                int node = getNum(i, j);
                for (auto x : last)
                    g[node].pb(x);
                last.clear();
            }
            if (grid[i][j] != '.') {
                last.pb(getNum(i, j));
            }
        }

        // South
        last.clear();
        for (int i = n - 1; i >= 0; i--) {
            if (grid[i][j] == 'S') {
                int node = getNum(i, j);
                for (auto x : last)
                    g[node].pb(x);
                last.clear();
            }
            if (grid[i][j] != '.') {
                last.pb(getNum(i, j));
            }
        }
    }

    // E/W
    for (int i = 0; i < n; i++) {
        // West
        vi last;
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'W') {
                int node = getNum(i, j);
                for (auto x : last)
                    g[node].pb(x);
                last.clear();
            }
            if (grid[i][j] != '.') {
                last.pb(getNum(i, j));
            }
        }

        // East
        last.clear();
        for (int j = m - 1; j >= 0; j--) {
            if (grid[i][j] == 'E') {
                int node = getNum(i, j);
                for (auto x : last)
                    g[node].pb(x);
                last.clear();
            }
            if (grid[i][j] != '.') {
                last.pb(getNum(i, j));
            }
        }
    }

    // Do the topo sort thing
    int end = getNum(n - 1, m - 1);
    for (int i = 0; i <= end; i++) {
        dfs(i);
    }

    return 0;
}
