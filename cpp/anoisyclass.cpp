#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Defines
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f

// Scan and Debug
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
    auto transpose() { // Transposes the graph into its reversed form
        Graph<MAX> ret; ret.init(n, m);
        for (int i = 1; i <= n; i++)
            for (auto adj : adjs(i))
                ret.addEdge(adj, i);
        return ret;
    }
};
template <int MAX, typename T>
struct SCC {
    int curOrd = -1, ord[MAX], low[MAX]; stack<int> stk; bool inStk[MAX], vis[MAX]; T graph;
    vector<vector<int>> comps;
    void tarjan(T &graph0) {
        comps.clear();
        graph = graph0;
        curOrd = -1;
        memset(inStk, false, sizeof inStk);
        memset(vis, false, sizeof vis);

        for (int i = 1; i <= graph.n; i++)
            if (!vis[i])
                dfs(i);
    }
    void dfs(int cur) {
        stk.push(cur);
        vis[cur] = inStk[cur] = true;
        ord[cur] = low[cur] = ++curOrd;

        for (int adj : graph.adjs(cur)) {
            if (!vis[adj]) {
                dfs(adj);
                low[cur] = min(low[cur], low[adj]);
            }
            else if (inStk[adj])
                low[cur] = min(low[cur], ord[adj]);
        }

        // If root of SCC
        if (low[cur] == ord[cur]) {
            int st = -1, v = -1;
            vector<int> comp;
            do {
                v = stk.top(); stk.pop(); inStk[v] = false;
                comp.push_back(v);
            }
            while (v != cur);
            comps.push_back(comp);
        }
    }
};

const int MAX = 10001;
int n, m;
Graph<MAX> g;
SCC<MAX, Graph<MAX>> scc;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, m);
    g.init(n, m);
    g.input(false);
    scc.tarjan(g);

    cout << (scc.comps.size() == n ? "Y\n" : "N\n");

    return 0;
}