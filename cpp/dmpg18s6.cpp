#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Defines and one-liners
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
template <typename T> inline T& back(vector<T> &vec) { return *(vec.end() - 1); }
template <typename T> inline void pop(vector<T> &vec) { return vec.erase(vec.end() - 1); }

// Scan, Debug, and other nonsense
template <typename T> ostream& operator<<(ostream& out,vector<T> iter){out<<"[";for(auto t:iter){out<<t<<", ";}out<<"]";return out;}
template <typename T> void printArray(ostream& out,T* arr,int sz){out<<"[";for(int i=0;i<sz;i++){out<<arr[i]<<", "; } out<<"]";}
#define OUT_OPERATOR(type, propa, propb) ostream& operator<<(ostream& out,type obj){out<<"("<<#propa<<"="<<obj. propa<<", "<<#propb<<"="<<obj. propb<<")";return out;}

void scan(){}
template<typename F, typename... R> void scan(F &f,R&... r){cin>>f;scan(r...);}
int di_; string dnms_, co_ = ",";
void debug_(){cout<<endl;}
template<typename F, typename... R> void debug_(F f,R... r){while(dnms_[di_] != ',')cout<<dnms_[di_++];di_++;cout<<": "<<f<<",";debug_(r...);}
#define debug(...) dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__)

template <int MAX>
struct Graph {
    int n, m, __ba, __bb; vector<int> matrix[MAX];
    void init(int n0, int m0) { n = n0; m = m0; }
    inline void addEdge(int a, int b) { matrix[a].push_back(b); }
    inline auto& adjs(int x) { return matrix[x]; }
    Graph& operator=(const Graph o) { n = o.n; m = o.m; copy(o.matrix, o.matrix + n + 1, matrix); return *this; }
    void input(bool undirected) { // Reads a graph's edges from stdin
        for (int i = 0; i < m; i++) {
            cin >> __ba >> __bb;
            addEdge(__ba, __bb);
            if (undirected) addEdge(__bb, __ba);
        }
    }
};

const int MN = 1e5 + 1;
int n, m, cord = 0, best = INF, bestI = -1,
    sz[MN], ord[MN], low[MN];
Graph<MN> g;
bool vis[MN];

void dfs(int cur, int par) {
    ord[cur] = low[cur] = ++cord;
    vis[cur] = true;

    vector<int> szs;
    int maxLow = -1, comps = 0, backSzs = 0;
    for (int adj : g.adjs(cur)) {
        if (adj ^ par) {
            if (!vis[adj]) {
                dfs(adj, cur);
                low[cur] = min(low[cur], low[adj]);
                comps++;

                if (low[adj] >= ord[cur])
                    szs.push_back(sz[adj]);
                else
                    backSzs += sz[adj];
            }
            else // If it's already been visited, it's part of another component
                low[cur] = min(low[cur], ord[adj]);
            maxLow = max(maxLow, low[adj]);
        }
    }

    // debug(cur, par, ord[cur], low[cur], sz[cur], sz[par], maxLow, comps);

    // Articulation Point
    if ((par == -1 && comps >= 2) || (par != -1 && maxLow >= ord[cur])) {
        szs.push_back(backSzs + sz[1] - sz[cur]);
        // debug(szs);
        int cbest = *max_element(szs.begin(), szs.end());
        if (cbest < best) {
            best = cbest;
            bestI = cur;
        }
        else if (cbest == best && cur > bestI)
            bestI = cur;
    }
}

int calcSz(int cur) {
    sz[cur] = 1;
    vis[cur] = true;
    for (int adj : g.adjs(cur)) {
        if (!vis[adj])
            sz[cur] += calcSz(adj);
    }
    return sz[cur];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, m);
    g.init(n, m);
    g.input(true);

    calcSz(1);
    memset(vis, false, sizeof vis);
    dfs(1, -1);

    cout << bestI << " " << (best == INF ? -1 : best) << "\n"; 

    return 0;
}
