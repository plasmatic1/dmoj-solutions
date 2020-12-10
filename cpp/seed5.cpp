// ./genesis.yml
#include "bits/stdc++.h"
using namespace std;

// Defines
#define fs first
#define sn second
#define pb push_back
#define eb emplace_back
#define mpr make_pair
#define mtp make_tuple
#define all(x) (x).begin(), (x).end()
// Basic type definitions
using ll = long long; using ull = unsigned long long; using ld = long double;
using pii = pair<int, int>; using pll = pair<long long, long long>;
// PBDS order statistic tree
#include <ext/pb_ds/assoc_container.hpp> // Common file 
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds; 
template <typename T, class comp = less<T>> using os_tree = tree<T, null_type, comp, rb_tree_tag, tree_order_statistics_node_update>;
template <typename K, typename V, class comp = less<K>> using treemap = tree<K, V, comp, rb_tree_tag, tree_order_statistics_node_update>;
// HashSet
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
const ll RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash { ll operator()(ll x) const { return x ^ RANDOM; } };
template <typename T, class Hash> using hashset = gp_hash_table<T, null_type, Hash>;
template <typename K, typename V, class Hash> using hashmap = gp_hash_table<K, V, Hash>;
// More utilities
int SZ(string &v) { return v.length(); }
template <typename C> int SZ(C &v) { return v.size(); }
template <typename C> void UNIQUE(vector<C> &v) { sort(v.begin(), v.end()); v.resize(unique(v.begin(), v.end()) - v.begin()); }
template <typename T, typename U> void maxa(T &a, U b) { a = max(a, b); }
template <typename T, typename U> void mina(T &a, U b) { a = min(a, b); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

// A sample edge struct for maximum flow
// Flow of edge can be found with cap - resCap
// Template Arguments:
//   _FlowUnit: the type of the flow
// Constructor Arguments:
//   to: the vertex that this directed edge ends at
//   rev: the index in the adjacency list of vertex to of the reverse edge
//   cap: the initial capacity of this edge
// Fields:
//   FlowUnit: the type of the flow
//   to: the vertex that this directed edge ends at
//   rev: the index in the adjacency list of vertex to of the reverse edge
//   cap: the initial capacity of this edge
//   resCap: the residual capacity of this edge
// Tested:
//   https://open.kattis.com/problems/maxflow
//   https://open.kattis.com/problems/mincut
//   https://www.spoj.com/problems/FASTFLOW/
//   https://vn.spoj.com/problems/FFLOW/
//   https://loj.ac/p/127
template <class _FlowUnit> struct FlowEdge {
  using FlowUnit = _FlowUnit; int to, rev; FlowUnit cap, resCap;
  FlowEdge(int to, int rev, FlowUnit cap)
      : to(to), rev(rev), cap(cap), resCap(cap) {}
};

// Computes the maximum flow and minimum cut in a flow network using the
//   Push Relabel algorithm with the highest label selection rule and
//   gap relabelling heuristic
// Vertices are 0-indexed
// Template Arguments:
//   Edge: a generic edge class (such as FlowEdge)
//     Required Fields:
//       FlowUnit: the type of the flow
//       to: the vertex that this directed edge ends at
//       rev: the index in the adjacency list of vertex to of the reverse edge
//       resCap: the residual capacity of this edge
//     Required Functions:
//       constructor(to, rev, cap): initializes the edge to vertex to with
//         the reverse index rev and capacity cap
// Constructor Arguments:
//   V: the number of vertices in the flow network
//   FLOW_EPS: a value for the flow epsilon
// Fields:
//   V: the number of vertices in the flow network
//   FLOW_EPS: a value for the flow epsilon
//   G: an adjacency list of all edges and reverse edges in the flow network
//   cut: a vector of booleans indicating which side of a minimum s-t cut it
//     is on
// Functions:
//   addEdge(v, w, vwCap, wvCap): adds an edge from v to w with capacity
//     vwCap and a reverse capacity of wvCap
//   getFlow(s, t): returns the maximum flow from s to t as well as the minimum
//     s-t cut
// In practice, has a very small constant
// Time Complexity:
//   constructor: O(V)
//   addEdge: O(1)
//   getFlow: O(V^2 sqrt E)
// Memory Complexity: O(V + E)
// Tested:
//   https://open.kattis.com/problems/maxflow
//   https://open.kattis.com/problems/mincut
//   https://www.spoj.com/problems/FASTFLOW/
//   https://vn.spoj.com/problems/FFLOW/
//   https://loj.ac/p/127
template <class Edge> struct PushRelabelMaxFlow {
  using FlowUnit = typename Edge::FlowUnit;
  int V; FlowUnit FLOW_EPS; vector<vector<Edge>> G; vector<bool> cut;
  PushRelabelMaxFlow(int V, FlowUnit FLOW_EPS = FlowUnit(1e-9))
      : V(V), FLOW_EPS(FLOW_EPS), G(V) {}
  void addEdge(int v, int w, FlowUnit vwCap, FlowUnit wvCap = FlowUnit()) {
    if (v == w) return;
    G[v].emplace_back(w, int(G[w].size()), vwCap);
    G[w].emplace_back(v, int(G[v].size()) - 1, wvCap);
  }
  FlowUnit getFlow(int s, int t) {
    cut.assign(V, false); if (s == t) return FlowUnit();
    vector<FlowUnit> ex(V, FlowUnit()); vector<int> h(V, 0), cnt(V * 2, 0);
    vector<vector<int>> hs(V * 2);
    vector<typename vector<Edge>::iterator> cur(V);
    auto push = [&] (int v, Edge &e, FlowUnit df) {
      int w = e.to;
      if (abs(ex[w]) <= FLOW_EPS && df > FLOW_EPS) hs[h[w]].push_back(w);
      e.resCap -= df; G[w][e.rev].resCap += df; ex[v] -= df; ex[w] += df;
    };
    h[s] = V; ex[t] = FlowUnit(1); cnt[0] = V - 1;
    for (int v = 0; v < V; v++) cur[v] = G[v].begin();
    for (auto &&e : G[s]) push(s, e, e.resCap);
    if (!hs[0].empty()) for (int hi = 0; hi >= 0;) {
      int v = hs[hi].back(); hs[hi].pop_back(); while (ex[v] > FLOW_EPS) {
        if (cur[v] == G[v].end()) {
          h[v] = INT_MAX; for (auto e = G[v].begin(); e != G[v].end(); e++)
            if (e->resCap > FLOW_EPS && h[v] > h[e->to] + 1)
              h[v] = h[(cur[v] = e)->to] + 1;
          cnt[h[v]]++;
          if (--cnt[hi] == 0 && hi < V) for (int w = 0; w < V; w++)
            if (hi < h[w] && h[w] < V) { cnt[h[w]]--; h[w] = V + 1; }
          hi = h[v];
        } else if (cur[v]->resCap > FLOW_EPS && h[v] == h[cur[v]->to] + 1) {
          push(v, *cur[v], min(ex[v], cur[v]->resCap));
        } else cur[v]++;
      }
      while (hi >= 0 && hs[hi].empty()) hi--;
    }
    for (int v = 0; v < V; v++) cut[v] = h[v] >= V;
    return -ex[s];
  }
};

// 3*i=in, 3*i+1=mediator, 3*i+2=out
const int MN = 101;
int N, M,
    E[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N);
    for (auto i = 0; i < N-1; i++)
        cin >> (E[i]);

    PushRelabelMaxFlow<FlowEdge<int>> flow(3*N);
    cin >> (M);
    for (auto i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;

        flow.addEdge(3*a+2, 3*b, INF);
    }
    for (auto i = 0; i < N; i++) {
        flow.addEdge(3*i, 3*i+1, E[i]);
        flow.addEdge(3*i+1, 3*i+2, E[i]);
    }

    cout << (flow.getFlow(0, 3*(N-1))) << '\n';

    return 0;
}