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
    auto transpose() { // Transposes the graph into its reversed form
        Graph<MAX> ret; ret.init(n, m);
        for (int i = 1; i <= n; i++)
            for (auto adj : adjs(i))
                ret.addEdge(adj, i);
        return ret;
    }
};
template <int MAX, int LOG, typename T>
struct BinaryLiftLCA {
    int pars[LOG][MAX], levels[MAX]; T graph;
    BinaryLiftLCA() {}
    void dfs(int cur, int par, int level) {
        levels[cur] = level;
        pars[0][cur] = par;
        for (auto adj : graph.adjs(cur))
            if (adj ^ par)
                dfs(adj, cur, level + 1);
    }
    void init(T &graph0) {
        graph = graph0;

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
};

struct p {
    int i, l, r, v;
    bool operator<(const p &o) const {
        if (l == o.l)
            return r > o.r;
        return l < o.l;
    }
};

const int MAX = 1e5 + 1;
int n, q, bl, br, 
    to[MAX], bestIds[MAX];
p segs[MAX];
Graph<MAX> g;
BinaryLiftLCA<MAX, 17, Graph<MAX>> lca;

void dfs(int cur, int par, int bestVal, int bestId) {
    bestIds[cur] = bestId;
    // debug(cur, par, bestVal, bestId);

    for (int adj : g.adjs(cur)) {
        if (adj ^ par) {
            if (segs[adj - 2].v <= bestVal)
                dfs(adj, cur, segs[adj - 2].v, adj);
            else
                dfs(adj, cur, bestVal, bestId);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n);

    for (int i = 0; i < n; i++) {
        scan(segs[i].l, segs[i].r, segs[i].v);
        segs[i].i = i + 1;
    }
    sort(segs, segs + n);
    for (int i = 0; i < n; i++)
        to[segs[i].i] = i + 2;

    stack<int> pars, parsR; 
    pars.push(1); parsR.push(INF);
    for (int i = 0; i < n; i++) {
        while (segs[i].l > parsR.top()) {
            parsR.pop();
            pars.pop();
        }

        g.addEdge(pars.top(), i + 2);
        g.addEdge(i + 2, pars.top());

        pars.push(i + 2);
        parsR.push(segs[i].r);
    }

    g.init(n + 1, n);
    lca.init(g);
    dfs(1, -1, INF, -1);

    scan(q);

    for (int i = 0; i < q; i++) {
        scan(bl, br); bl = to[bl]; br = to[br];

        int lcav = lca.lca(bl, br), ansId = lcav;
        if (lcav == bl)
            ansId = lca.pars[0][bl];
        else if (lcav == br)
            ansId = lca.pars[0][br];
        
        // debug(i, bl, br, lcav, ansId);

        cout << (ansId == -1 || bestIds[ansId] == -1 ? -1 : segs[bestIds[ansId] - 2].i) << "\n";
    }

    return 0;
}