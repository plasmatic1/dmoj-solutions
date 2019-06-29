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

const int MAX = 5e3 + 1;
int n, s;
Graph<MAX> g;

bool done[MAX];
vector<int> nodes;
int ctr = -1, maxDis = -1;
int getNodes(int cur, int par) {
    int maxD = done[cur] ? -INF : 0;
    for (int adj : g.adjs(cur))
        if (adj ^ par)
            maxD = max(maxD, getNodes(adj, cur) + 1);
    if (maxD == maxDis)
        nodes.push_back(cur);
    return maxD;
}

void markDone(int cur, int par, int rad) {
    if (rad < 0) return;

    done[cur] = true;
    for (int adj : g.adjs(cur))
        if (adj ^ par)
            markDone(adj, cur, rad - 1);
}

bool sim(int i) {
    memset(done, false, sizeof done);
    maxDis = i;
    ctr = 0;
        
    do {
        nodes.clear();
        getNodes(1, -1);

        for (int node : nodes) {
            markDone(node, -1, i);
            ctr++;
        }
    } while (nodes.size());

    for (int j = 1; j <= n; j++) {
        if (!done[j]) {
            ctr++;
            break;
        }
    }

    return ctr <= s;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, s);
    g.init(n, n - 1);
    g.input(true);

    int l = -1, r = n;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        if (sim(mid))
            r = mid;
        else
            l = mid;
    }

    // debug(l, r);
    cout << r << "\n";

    return 0;
}