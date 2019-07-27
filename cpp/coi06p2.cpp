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

struct edi {
    int i, v;
    operator int() const { return v; } // Returns the adjacent node
};
template <int MAX>
struct EdgeIdGraph {
    int n, m, __ba, __bb; vector<edi> matrix[MAX];
    void init(int n0, int m0) { n = n0; m = m0; }
    inline void addEdge(int a, int b, int i) { matrix[a].push_back({i, b}); }
    inline auto& adjs(int x) { return matrix[x]; }
    EdgeIdGraph& operator=(const EdgeIdGraph o) { n = o.n; m = o.m; copy(o.matrix, o.matrix + n + 1, matrix); return *this; }
    void input(bool undirected) { // Reads a graph's edges from stdin
        for (int i = 0; i < m; i++) {
            cin >> __ba >> __bb;
            addEdge(__ba, __bb, i);
            if (undirected) addEdge(__bb, __ba, i);
        }
    }
};

template <int MAX, int LOG, typename T>
struct BinaryLiftLCA {
    int pars[LOG][MAX], levels[MAX]; T &graph;
    BinaryLiftLCA(T& graph0) : graph(graph0) {}
    void dfs(int cur, int par, int level) {
        levels[cur] = level;
        pars[0][cur] = par;
        for (auto adj : graph.adjs(cur))
            if (adj ^ par)
                dfs(adj, cur, level + 1);
    }
    void init() {
        // Setting sparse table
        dfs(1, -1, 0);
        for (int i = 1; i < LOG; i++) {
            for (int j = 0; j <= graph.n; ++j)
                pars[i][j] = pars[i - 1][j] == -1 ? -1 : pars[i - 1][pars[i - 1][j]];
        }
    }
    int lca(int a, int b) {
        if (levels[a] > levels[b]) swap(a, b);
        int delta = levels[b] - levels[a];
        for (int i = LOG - 1; i >= 0; i--)
            if ((delta >> i) & 1)
                b = pars[i][b];
        if (a == b) return a;
        for (int i = LOG - 1; i >= 0; i--) {
            if (pars[i][a] != pars[i][b]) {
                a = pars[i][a];
                b = pars[i][b];
            }
        }
        return pars[0][a];
    }
    int dis(int a, int b) { return levels[a] + levels[b] - (levels[lca(a, b)] << 1); }
};

const int MN = 1e5 + 1, MM = 5e5 + 1;
int n, m, q, bt, ba, bb, bc, bd;
EdgeIdGraph<MN> g, compG, dfsTree;
BinaryLiftLCA<MN, 17, EdgeIdGraph<MN>> lca(compG), lcaDT(dfsTree);

template <int MAX, int MM, typename T>
struct Bridges {
    int curOrd = -1, ord[MAX], low[MAX]; bool vis[MAX], isBridge[MM]; T &graph;
    int adjLow[MAX];
    vector<int> bridges;
    Bridges(T &graph0) : graph(graph0) {}
    void tarjan() {
        curOrd = -1;
        memset(vis, false, sizeof vis);
        memset(adjLow, 0x3f, sizeof adjLow);

        for (int i = 1; i <= graph.n; i++)
            if (!vis[i])
                dfs(i, -1);
    }
    void dfs(int cur, int par) {
        vis[cur] = true;
        ord[cur] = low[cur] = ++curOrd;

        for (auto adj : graph.adjs(cur)) {
            if (adj.v ^ par) {
                if (!vis[adj.v]) {
                    dfsTree.addEdge(cur, adj.v, adj.i);
                    dfsTree.addEdge(adj.v, cur, adj.i);

                    dfs(adj.v, cur);
                    low[cur] = min(low[cur], low[adj.v]);
                }
                else
                    low[cur] = min(low[cur], ord[adj.v]);
                if (low[adj.v] > ord[cur])
                    isBridge[adj.i] = true;
                
                adjLow[cur] = min(adjLow[cur], low[adj.v]);
            }
        }
    }
};

Bridges<MN, MM, EdgeIdGraph<MN>> br(g);

namespace lca2 {
    const int LOG = 17;
    int parLow[LOG][MN];
    void dfs(int cur, int par) {
        parLow[0][cur] = br.low[cur];
        for (edi &adj : dfsTree.adjs(cur))
            if (adj.v ^ par)
                dfs(adj.v, cur);
    }
    void init() {
        memset(parLow, -1, sizeof parLow);
        dfs(1, -1);

        for (int i = 1; i < LOG; i++) {
            for (int j = 1; j <= n; j++) {
                int par = lcaDT.pars[i - 1][j];
                parLow[i][j] = par == -1 ? -1 : min(parLow[i - 1][j], parLow[i - 1][par]);
            }
        }
    }
    bool isParentOf(int from, int to) {
        int delta = lcaDT.levels[from] - lcaDT.levels[to];
        // assert(delta >= 0);
        for (int i = 0; i < LOG; i++)
            if ((delta >> i) & 1)
                from = lcaDT.pars[i][from];
        return from == to;
    }
    int minParentOrd(int from, int to) {
        int delta = lcaDT.levels[from] - lcaDT.levels[to], best = INF;
        for (int i = 0; i < LOG; i++) {
            if ((delta >> i) & 1) {
                best = min(best, parLow[i][from]);
                from = lcaDT.pars[i][from];
            }
        }
        return best;
    }
}

namespace cyc {
    int to[MN];
    bool vis[MN];
    void dfs(int cur, int begin) {
        if (vis[cur]) return;
        vis[cur] = true;
        to[cur] = begin;
        for (auto adj : g.adjs(cur))
            if (!br.isBridge[adj.i])
                dfs(adj.v, begin);
    }
    void compressGraph() {
        for (int i = 1; i <= n; i++)
            if (!vis[i])
                dfs(i, i);
        for (int i = 1; i <= n; i++) {
            unordered_set<int> added;
            for (auto adj : g.adjs(i)) {
                if (!br.isBridge[adj.i])
                    continue;
                
                int a = to[i], b = to[adj.v];
                if (a != b && added.find(b) == added.end()) { // not self-loop and not already added
                    compG.addEdge(a, b, adj.i); // Edges exist for both directions already
                    added.insert(b);

                    // debug("Add", adj.i, i, adj.v, a, b);
                }
            }
        }
    }
    int* getTo() { return to; }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, m);
    g.init(n, m); compG.init(n, m);
    g.input(true);

    dfsTree.init(n, m);

    br.tarjan();
    cyc::compressGraph();
    lca.init();

    lcaDT.init(); // LCA Array for dfstree
    lca2::init(); // LCA for min adj order

    // assert(0);

    // printArray(cout, br.ord, n + 1); cout << "\n";
    // printArray(cout, br.low, n + 1); cout << "\n";

    // cout << "TO: "; printArray(cout, cyc::getTo(), n + 1); cout << "\n";

    scan(q);

    for (int i = 0; i < q; i++) {
        scan(bt, ba, bb, bc);

        if (bt == 1) {
            scan(bd);
            ba = cyc::to[ba]; bb = cyc::to[bb]; bc = cyc::to[bc]; bd = cyc::to[bd];

            if (bc == bd) // Part of same cycle
                cout << "yes\n";
            else {
                // If C-D divides A and B, then A would be closer to C and B would be closer to D (or vice versa).  If they are both closer to the same node, then it does not divide them
                if ((lca.dis(ba, bc) < lca.dis(ba, bd)) == (lca.dis(bb, bc) < lca.dis(bb, bd)))
                    cout << "yes\n";
                else
                    cout << "no\n";
            }
        }
        else { // bt == 2
            // First check if C is in the middle of A and B
            if (lcaDT.dis(ba, bc) + lcaDT.dis(bc, bb) == lcaDT.dis(ba, bb)) {
                // assert(br.ord[ba] > br.ord[bc] || br.ord[bb] > br.ord[bc]);
                
                // Check if A needs to go backwards and if B needs to go backwards past C
                bool flag = true;
                if (br.ord[ba] > br.ord[bc] && lca2::isParentOf(ba, bc))
                    flag &= lca2::minParentOrd(ba, bc) < br.ord[bc];
                if (flag && br.ord[bb] > br.ord[bc] && lca2::isParentOf(bb, bc))
                    flag &= lca2::minParentOrd(bb, bc) < br.ord[bc];

                cout << (flag ? "yes\n" : "no\n");
            }
            else
                cout << "yes\n";
        }
    }

    return 0;
}