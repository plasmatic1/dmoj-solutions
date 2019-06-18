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
    void addEdge(int a, ed<T> b) { matrix[a].push_back(b); }
    auto& adjs(int x) { return matrix[x]; }
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
template <int MAX, typename DIS_TYPE>
struct Dijkstra {
    DIS_TYPE dis[MAX]; priority_queue<ed<DIS_TYPE>> nxt;
    void dijkstra(int start, WeightedGraph<MAX, DIS_TYPE>& graph) {
        vector<int> starts = {start};
        multisource_dijkstra(starts, graph);
    }
    void multisource_dijkstra(vector<int> &starts, WeightedGraph<MAX, DIS_TYPE>& graph) {
        memset(dis, 0x3f, sizeof dis);
        for (int start : starts) {
            dis[start] = 0;
            nxt.push({start, 0});
        }

        while (!nxt.empty()) {
            auto cur = nxt.top(); nxt.pop();

            if (cur.w > dis[cur.v])
                continue;

            for (auto adj : graph.adjs(cur)) {
                DIS_TYPE alt = cur.w + adj.w;
                if (alt < dis[adj.v]) {
                    dis[adj.v] = alt;
                    nxt.push({adj, alt});
                }
            }
        }
    }
};

#define MAX 1001
int n, m;
WeightedGraph<MAX, int> graph;
Dijkstra<MAX, int> dijk;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, m);
    graph.init(n, m);
    graph.input(true);
    dijk.dijkstra(1, graph);

    for (int i = 1; i <= n; i++) {
        cout << (dijk.dis[i] == INF ? -1 : dijk.dis[i]) << "\n";
    }

    return 0;
}