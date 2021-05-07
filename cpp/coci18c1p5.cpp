// ./coci-18-contest-1-5-teoretičar.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

int mxdeg;

using pii = pair<int, int>;

const int MN = 2e5 + 10, MM = 5e5 + 1;
int L, R, N, M;

// keeping track of ans
int clrCtr = 1, ans[MM];

// graphs
map<pii, int> _edgeIdx;
vector<pii> g[MN];
int deg[MN];
// graph utils
int clr(int k) { return k >= L; } // colour of node
int edgeIdx(int a, int b) { if (a > b) swap(a, b); auto ptr = _edgeIdx.find({a, b}); return ptr == _edgeIdx.end() ? -1 : ptr->second; }

// DFS to find ans
bool sel[MM+MN], vis[MN], selNode[MN]; // sel[i] = whether edge i is selected in eulerian tour, vis[i] = vis array, selNode[i] = whether a node was selected already in nodes set
void dfs(int c, vector<int> &cyc) { 
    vis[c] = true;
    while (!g[c].empty()) {
        while (!g[c].empty() && sel[g[c].back().second])
            g[c].pop_back();
        if (g[c].empty()) break;

        auto [to, toi] = g[c].back();
        g[c].pop_back();
        sel[toi] = true;

        dfs(to, cyc);
    }

    cyc.push_back(c);
}

void solve(vector<pii> es) {
    vector<int> nodes;
    int ectr = 0;

    // clear graph helper
    auto clearGraph = [&] () {
        for (auto n : nodes) {
            g[n].clear();
            deg[n] = 0;
            vis[n] = false;
            selNode[n] = false;
        }
        for (auto i = 0; i < ectr; i++)
            sel[i] = false;
        ectr = 0;
    };
    // add edge helper
    auto addEdge = [&] (int a, int b) {
        g[a].emplace_back(b, ectr);
        g[b].emplace_back(a, ectr++);
        deg[a]++;
        deg[b]++;
        if (!selNode[a]) { selNode[a] = true; nodes.push_back(a); }
        if (!selNode[b]) { selNode[b] = true; nodes.push_back(b); }
    };

    // get eulerian circuit and split graph
    for (auto [a, b] : es) addEdge(a, b);

    vector<int> oddNodes;
    int maxDeg = 0;
    for (auto k : nodes) {
        if (deg[k] & 1)
            oddNodes.push_back(k);
        maxDeg = max(maxDeg, deg[k]);
    }

    // special case, maxDeg = 1, done d&c
    if (maxDeg == 1) {
        for (auto [a, b] : es)
            ans[edgeIdx(a, b)] = clrCtr;
        clrCtr++;

        clearGraph();
        return;
    }

    int sz = oddNodes.size(); assert(sz % 2 == 0);
    if (sz) {
        for (auto k : oddNodes)
            addEdge(k, N+clr(k));
        if (g[N].size() % 2 || g[N+1].size() % 2)
            addEdge(N, N+1);
    }

    // get Euler cycle
    vector<pii> childs[2];
    for (auto n : nodes) {
        if (!vis[n]) {
            vector<int> cyc;
            dfs(n, cyc);
            int sz = cyc.size(), curEdgeClr = 0;
            for (auto i = 0; i < sz-1; i++) {
                // split edges
                if (cyc[i] < N && cyc[i+1] < N)
                    childs[curEdgeClr].emplace_back(cyc[i], cyc[i+1]);
                curEdgeClr ^= 1;
            }
        }
    }

    // clear graph
    clearGraph();

    // recurse to children
    solve(childs[0]);
    solve(childs[1]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> L >> R >> M;
    N = L+R;

    vector<pii> es;
    vector<int> deg(N);
    for (auto i = 0; i < M; i++) {
        int a, b; cin >> a >> b; a--; b--;
        b += L;
        deg[a]++; deg[b]++;

        es.emplace_back(a, b);
        _edgeIdx[{a, b}] = i; // always a<b
    }

    mxdeg = *max_element(deg.begin(), deg.end());
    solve(es);
    cout << clrCtr-1 << '\n';
    for (auto i = 0; i < M; i++) cout << ans[i] << '\n';

#ifdef LOCAL
    cout.flush(); fflush(stdout); // so asserts dont "hide" output
    int k = mxdeg;
    cout << "VERIFY: K=" << k << ", C=" << clrCtr-1 << endl;
    int p = 2; while (p < k) p *= 2;
    assert(clrCtr-1 <= p);

    vector<vector<int>> clrs(N);
    vector<set<int>> uclrs(N);
    for (auto [a, b] : es) {
        int clr = ans[edgeIdx(a, b)];
        clrs[a].push_back(clr);
        clrs[b].push_back(clr);
        uclrs[a].insert(clr);
        uclrs[b].insert(clr);
    }
    for (auto i = 0; i < N; i++)
        assert(clrs[i].size() == uclrs[i].size());
#endif

    return 0;
}