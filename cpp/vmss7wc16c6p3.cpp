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
template <int MAX, typename T>
struct ArticulationPoints {
	int curOrd = -1, ord[MAX], low[MAX]; bool vis[MAX]; T graph;
	vector<int> points;
	void tarjan(T &graph0) {
		graph = graph0;
		curOrd = -1;
		memset(vis, false, sizeof vis);

		for (int i = 1; i <= graph.n; i++)
			if (!vis[i])
				dfs(i, -1);
	}
	void dfs(int cur, int par) {
		vis[cur] = true;
		ord[cur] = low[cur] = ++curOrd;

				debug(cur, par, ord[cur]);

		int totBranches = 0;
		bool flag = false;
		for (int adj : graph.adjs(cur)) {
			if (!vis[adj]) {
				dfs(adj, cur);
				flag |= low[adj] >= ord[cur];
				low[cur] = min(low[cur], low[adj]);
				totBranches++;
			}
			else if (adj ^ par)
				low[cur] = min(low[cur], ord[adj]);
		}

		// is articulation point
		if (par == -1) {
			if (totBranches > 1)
				points.push_back(cur);
		}
		else if (flag)
			points.push_back(cur);
	}
};

#define MAX 100001
int n, m;
Graph<MAX> graph;
ArticulationPoints<MAX, Graph<MAX>> artic;

template <typename T>
ostream& operator<<(ostream& out, vector<T> v) {
	out << "[";
	for (auto x : v)
		out << x << ", ";
	out << "]";
	return out;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	scan(n, m);
	graph.init(n, m);
	graph.input(true);
	artic.tarjan(graph);

	vector<int> lows, ords;
	for (int i = 1; i <= n; i++)
		lows.push_back(artic.low[i]), ords.push_back(artic.ord[i]);
	debug(lows);
	debug(ords);

	sort(artic.points.begin(), artic.points.end());
	cout << artic.points.size() << "\n";
	for (auto x : artic.points)
		cout << x << "\n";

	return 0;
}