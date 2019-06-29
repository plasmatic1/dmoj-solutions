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

template <typename T>
struct ed {
    int v; T w;
    operator int() const { return v; } // Returns the adjacent node
    bool operator<(const ed &o) const { return w > o.w; } // Reversed for dijkstra
    ostream& operator<<(ostream& out) const { out << "(v=" << v << ", w=" << w << ")"; return out; }
};
template <typename T> istream& operator>>(istream& in, ed<T> &o) { in >> o.v >> o.w; return in; }
template <int MAX, typename T = int>
struct WeightedGraph {
    int n, m, __ba; ed<T> __bb; vector<ed<T>> matrix[MAX];
    void init(int n0, int m0) { n = n0; m = m0; }
    inline void addEdge(int a, ed<T> b) { matrix[a].push_back(b); }
    inline auto& adjs(int x) { return matrix[x]; }
    WeightedGraph& operator=(const WeightedGraph o) { n = o.n; m = o.m; copy(o.matrix, o.matrix + n + 1, matrix); return *this; }
    void input(bool undirected) {
        for (int i = 0; i < m; i++) {
            cin >> __ba >> __bb;
            addEdge(__ba, __bb);
            if (undirected) addEdge(__bb.v, {__ba, __bb.w});
        }
    }
    auto transpose() { // Transposes the graph into its reversed form
        WeightedGraph<MAX, T> ret; ret.init(n, m);
        for (int i = 1; i <= n; i++)
            for (auto adj : adjs(i))
                ret.addEdge(adj.v, {i, adj.w});
        return ret;
    }
};
template <int MAX, typename T, typename dis_t>
struct WeightedBFS {
    dis_t levels[MAX]; queue<int> nxt;
    void reset() { memset(levels, 0x3f, sizeof levels); }
    void bfs(int start, T& graph) {
        vector<int> starts = {start};
        multisource_bfs(starts, graph);
    }
    void multisource_bfs(vector<int> &starts, T& graph) {
        for (int start : starts) {
            levels[start] = 0;
            nxt.push(start);
        }

        while (!nxt.empty()) {
            int cur = nxt.front(); dis_t level = levels[cur]; nxt.pop();

            for (auto adj : graph.adjs(cur)) {
                if (levels[adj.v] > level + 1) {
                    levels[adj.v] = level + adj.w;
                    nxt.push(adj);
                }
            }
        }
    }
};

#define SINGLE(...) __VA_ARGS__
OUT_OPERATOR(SINGLE(pair<int, int>), first, second)

const int MAX = 1e5 + 1;
int N, M, L;
WeightedGraph<MAX, int> g;
WeightedBFS<MAX, WeightedGraph<MAX, int>, int> bfs;

namespace center {
    int dis1[MAX], dis2[MAX], dis3[MAX];
    vector<int> vis;
    void init() { 
        memset(dis1, 0x3f, sizeof dis1);
        memset(dis2, 0x3f, sizeof dis2);
        memset(dis3, 0x3f, sizeof dis3);
    }
    void reset() { vis.clear(); }
    void dfs(int cur, int par, int cdis, int dis[MAX], bool addVis) {
        dis[cur] = cdis;
        if (addVis)
            vis.push_back(cur);
        for (auto adj : g.adjs(cur))
            if (adj.v ^ par)
                dfs(adj, cur, cdis + adj.w, dis, addVis);
    }
    int maxNode(int dis[MAX]) {
        int best = -1, bestI = -1;
        for (int node : vis) {
            if (dis[node] > best) {
                best = dis[node];
                bestI = node;
            }
        }
        return bestI;
    }
}

bool pieceCmp(const pair<int, int> &a, const pair<int, int> &b) {
    return a.second > b.second;
}

int travelTime(int N0, int M0, int L0, int A[], int B[], int T[]) {
    N = N0; M = M0; L = L0;

    g.init(N, M);
    for (int i = 0; i < M; i++) {
        g.addEdge(A[i], {B[i], T[i]});
        g.addEdge(B[i], {A[i], T[i]});
    }

    vector<pair<int, int>> pieces; // Centre, Radius
    center::init();
    for (int i = 0; i < N; i++) {
        if (center::dis1[i] == INF) {
            center::reset();

            center::dfs(i, -1, 0, center::dis1, true);
            int dia1 = center::maxNode(center::dis1);
            center::dfs(dia1, -1, 0, center::dis2, false);
            int dia2 = center::maxNode(center::dis2);
            center::dfs(dia2, -1, 0, center::dis3, false);

            // debug(i, center::vis, dia1, dia2);

            int best = INF, bestI = -1;
            for (int node : center::vis) {
                int curAns = max(center::dis2[node], center::dis3[node]);
                if (curAns < best) {
                    best = curAns;
                    bestI = node;
                }
            }
            pieces.push_back(make_pair(bestI, best));
        }
    }
    sort(pieces.begin(), pieces.end(), pieceCmp);

    // debug(pieces);

    int start = pieces[0].first; // Adding extra edges
    for (int i = 1, sz = pieces.size(); i < sz; i++) {
        g.addEdge(start, {pieces[i].first, L});
        g.addEdge(pieces[i].first, {start, L});
    }

    // Diameter Finding
    bfs.reset();
    bfs.bfs(0, g);
    int maxDis = -1, maxNode = -1;
    for (int i = 0; i < N; i++) {
        if (bfs.levels[i] > maxDis) {
            maxDis = bfs.levels[i];
            maxNode = i;
        }
    }
    bfs.reset();
    bfs.bfs(maxNode, g);

    return *max_element(bfs.levels, bfs.levels + N);
}

#ifdef LOCAL

int A[8] = {0, 8, 2, 5, 5, 1, 1, 10},
            B[8] = {8, 2, 7, 11, 1, 3, 9, 6},
            T[8] = {4, 2, 4, 3, 7, 1, 5, 3};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "Case #1: " << travelTime(12, 8, 2, A, B, T) << "\n";

    return 0;
}
#endif