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
    int n, m, A[MAX], B[MAX]; vector<int> matrix[MAX];
    void init(int n0, int m0) { n = n0; m = m0; }
    inline void addEdge(int a, int b) { matrix[a].push_back(b); }
    inline auto& adjs(int x) { return matrix[x]; }
    Graph& operator=(const Graph o) { n = o.n; m = o.m; copy(o.matrix, o.matrix + n + 1, matrix); return *this; }
    void input(bool undirected) { // Reads a graph's edges from stdin
        for (int i = 0; i < m; i++) {
            cin >> A[i] >> B[i];
            addEdge(A[i], B[i]);
            if (undirected) addEdge(B[i], A[i]);
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
    int curOrd = -1, ord[MAX], low[MAX], to[MAX]; stack<int> stk; bool inStk[MAX], vis[MAX];
    // vector<vector<int>> comps;
    void tarjan(T &graph) {
        // comps.clear();
        // graph = graph0;
        curOrd = -1;
        memset(inStk, false, sizeof inStk);
        memset(vis, false, sizeof vis);

        for (int i = 1; i <= graph.n; i++)
            if (!vis[i])
                dfs(i, graph);
    }
    void dfs(int cur, T& graph) {
        stk.push(cur);
        vis[cur] = inStk[cur] = true;
        ord[cur] = low[cur] = ++curOrd;

        for (int adj : graph.adjs(cur)) {
            if (!vis[adj]) {
                dfs(adj, graph);
                low[cur] = min(low[cur], low[adj]);
            }
            else if (inStk[adj])
                low[cur] = min(low[cur], ord[adj]);
        }

        // If root of SCC
        if (low[cur] == ord[cur]) {
            int st = -1, v = -1;
            // vector<int> comp;
            do {
                v = stk.top(); stk.pop(); inStk[v] = false;
                // comp.push_back(v);
                if (st == -1) st = v;
                to[v] = st;
            }
            while (v != cur);
            // comps.push_back(comp);
        }
    }
};

const int MAX = 5e5 + 1;
int n, m, s, p, 
    toVal[MAX], tot[MAX], inDeg[MAX];
short val[MAX];
bitset<MAX> vis;
Graph<MAX> g;
SCC<MAX, Graph<MAX>> scc;
vector<int> pubs;

void dfsInDeg(int cur) {
    inDeg[cur]++;
    if (vis[cur])
        return;
    vis[cur] = true;
    for (int adj : g.adjs(cur))
        dfsInDeg(adj);
}

void dfs(int cur, int ctot) {
    inDeg[cur]--;
    tot[cur] = max(tot[cur], ctot);
    
    // only visit adjecent once parent is done
    if (!inDeg[cur]) {
        for (int adj : g.adjs(cur))
            dfs(adj, tot[cur] + toVal[adj]);
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, m);
    g.init(n, m);
    g.input(false);

    for (int i = 1; i <= n; i++)
        scan(val[i]);
    
    scan(s, p);

    pubs.resize(p);
    for (int i = 0; i < p; i++)
        scan(pubs[i]);
    
    scc.tarjan(g);

    for (int i = 1; i <= n; i++) {
        g.matrix[i].resize(0);
        toVal[scc.to[i]] += val[i];
    }

    for (int i = 0; i < m; i++) {
        int a = scc.to[g.A[i]], b = scc.to[g.B[i]];
        if (a != b)
            g.addEdge(a, b);
    }

    int ts = scc.to[s];
    dfsInDeg(ts);
    dfs(ts, toVal[ts]);

    int best = 0;
    for (int pub : pubs)
        best = max(best, tot[scc.to[pub]]);
    cout << best << "\n";

    return 0;
}