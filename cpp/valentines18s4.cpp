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
    void addEdge(int a, int b) { matrix[a].push_back(b); }
    auto& adjs(int x) { return matrix[x]; }
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

const int MAX = 200001;
const ll MOD = 1000000007;
int n, buf;
ll facts[MAX];
Graph<MAX> graph;

ll dfs(int cur) {
    ll tot = 1;
    for (int adj : graph.adjs(cur))
        tot = (tot * dfs(adj)) % MOD;
    return (tot * facts[graph.adjs(cur).size() + 1]) % MOD;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n);
    graph.init(n, n - 1);

    facts[0] = 1;
    for (int i = 1; i <= n; i++)
        facts[i] = (facts[i - 1] * i) % MOD;
    
    for (int i = 1; i < n; i++) {
        scan(buf);
        graph.addEdge(buf, i);
    }

    cout << dfs(0) << "\n";

    return 0;
}