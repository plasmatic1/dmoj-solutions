//============================================================================
// Name        : Legends.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct p {
	int i, v;
};

constexpr int SM_MAX = 1001, MAX = 100001, LOG = log2(MAX) + 1;
int s, t, n, m, ba, bb,
	edgeA[MAX], edgeB[MAX];
vector<p> matrix[MAX];

// Myth of the Flask, Myth of the Sun, Myth of the Fox
int curOrd = 0,
		ord[MAX], low[MAX][2];
vector<int> cVis;
int vis[MAX];

// Myth of the Sun
int pars[LOG][MAX], levels[MAX], disj[MAX];
bool used[MAX];

// Myth of the Fox
int curBlocked = -1;
bool foundDouble = false, foundBlocked = false,
		cycle[SM_MAX], cycleNode[SM_MAX], isAdjecentToBlocked[SM_MAX], vis2[SM_MAX], articulationPoint[SM_MAX];

// ======================================================================================================
//                                            Functions
// ======================================================================================================

// Myth of the Flask, Myth of the Sun, Myth of the Fox
// Tarjan's Bridge Finding Algorithm
void getCycles(int cur, int par, bool type5) {
	if (vis[cur])
		return;

	vis[cur] = true;
	low[cur][0] = ord[cur] = ++curOrd; low[cur][1] = 0x3f3f3f3f;
	vector<int> rets; rets.push_back(ord[cur]); rets.push_back(0x3f3f3f3f);

	if (type5 && cur == curBlocked)
		return;

	for (p adj : matrix[cur]) {
		if (type5 && adj.v == curBlocked)
			continue;

		if (adj.v ^ par) {
			getCycles(adj.v, cur, type5);

			if (low[adj.v][1] <= ord[cur]) // If the second one is lower, then both are lower (sorted)
				foundDouble = true;
			if (type5 && low[adj.v][0] <= ord[cur])
				cycle[adj.i] = true;

			rets.push_back(low[adj.v][0]);
			rets.push_back(low[adj.v][1]);
		}
	}

	sort(rets.begin(), rets.end());
	copy(rets.begin(), rets.begin() + 2, low[cur]);
}

bool hasDoubleCycleEdges() {
	foundDouble = false;

	for (int i = 1; i <= n; i++) {
		if (vis[i])
			continue;

		curOrd = 0;
		getCycles(i, -1, false);
	}

	return foundDouble;
}

// Myth of the Sun
void dfs3(int cur, int par, int lv) {
	levels[cur] = lv;
	pars[0][cur] = par;
	vis[cur] = true;

	for (p adj : matrix[cur]) {
		if (!vis[adj.v]) {
			dfs3(adj.v, cur, lv + 1);
			used[adj.i] = true;
		}
	}
}

int lca(int a, int b) {
	if (levels[a] > levels[b])
		swap(a, b);

	int delta = levels[b] - levels[a];
	for (int i = 0; i < LOG; i++)
		if ((delta >> i) & 1)
			b = pars[i][b];

	if (a == b)
		return a;

	for (int i = LOG - 1; i >= 0; i--) {
		if (pars[i][a] != pars[i][b]) {
			a = pars[i][a];
			b = pars[i][b];
		}
	}

	return pars[0][a];
}

int dis(int a, int b) { return levels[a] + levels[b] - (levels[lca(a, b)] << 1); }

// Myth of the fox
int cycleOnlyDfs(int cur, int par) {
	if (vis[cur] || cur == curBlocked)
		return 0;

	int tot = 0;
	bool pass = false;
	vis[cur] = true;
	for (p adj : matrix[cur]) {
		if (adj.v == curBlocked) {
			foundBlocked = true;
			continue;
		}

		if (adj.v ^ par) {
			if (cycle[adj.i])
				tot += cycleOnlyDfs(adj.v, cur);
			if (!isAdjecentToBlocked[cur])
				pass |= !cycle[adj.i] || articulationPoint[cur];
		}
	}

	return tot + pass;
}

bool hasDoubleCycleEdgesTask5() {
	foundDouble = false;

	for (int i = 1; i <= n; i++) {
		if (vis[i] || i == curBlocked)
			continue;

		curOrd = 0;
		getCycles(i, -1, true);
	}

	return foundDouble;
}

bool isAdjecentToCycle(int node) {
	for (int i = 1; i <= n; i++)
		for (p adj : matrix[i])
			cycleNode[i] |= cycle[adj.i];

	bool flag = false;
	for (p adj : matrix[node])
		flag |= cycleNode[adj.v];

	return flag;
}

bool dfsArticulationPoints(int cur, int par) {
	if (vis[cur])
		return false;

	vis[cur] = true;
	low[cur][0] = ord[cur] = ++curOrd;
	int totBranch = 0;
	bool flag = false;
	for (p adj : matrix[cur]) {
		if (adj.v ^ par) {
			totBranch += dfsArticulationPoints(adj.v, cur);
			if (low[adj.v][0] >= ord[cur])
				flag = true;
			low[cur][0] = min(low[cur][0], low[adj.v][0]);
		}
	}

	if (par == -1)
		articulationPoint[cur] = totBranch > 1;
	else
		articulationPoint[cur] = flag;

	return true;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> s >> t;

	for (int tcn_ = 0; tcn_ < t; ++tcn_) {
		cin >> n >> m;
		deque<int> nxt;
		vector<pair<int, int>> eds;

		memset(vis, 0, sizeof(vis));

		for (int i = 0; i < m; ++i) {
			cin >> ba >> bb;

			matrix[ba].push_back({i, bb});
			matrix[bb].push_back({i, ba});
			edgeA[i] = ba;
			edgeB[i] = bb;
		}

		if(s == 1){
			memset(vis, false, sizeof vis);
			printf(hasDoubleCycleEdges() ? "YES\n" : "NO\n");
		}
		else if(s == 2) // Chek for Cycle
			printf(m >= n ? "YES\n" : "NO\n");
		else if(s == 3){
			memset(vis, false, sizeof vis);
			memset(used, false, sizeof used);

			for (int j = 1; j <= n; j++)
				if (!vis[j])
					dfs3(j, -1, 0);

			for (int j = 1; j < LOG; j++)
				for (int k = 1; k <= n; k++)
					pars[j][k] = pars[j - 1][k] != -1 ? pars[j - 1][pars[j - 1][k]] : -1;

			int maxSize = -1;
			for (int j = 0; j < m; ++j)
				if (!used[j])
					maxSize = max(maxSize, dis(edgeA[j], edgeB[j]));

			memset(vis, false, sizeof vis);
			printf((maxSize >= 3) || hasDoubleCycleEdges() ? "YES\n" : "NO\n");
		}
		else if(s == 4){ // Anything has at least 3 children
			bool pass = false;

			for (int j = 1; j <= n; ++j) {
				if(matrix[j].size() >= 3){
					printf("YES\n");
					pass = true;
					break;
				}
			}

			if(!pass)
				printf("NO\n");
		}
		else{ // s == 5
			memset(articulationPoint, false, sizeof articulationPoint);
			memset(vis, false, sizeof vis);

			for (int j = 1; j <= n; ++j) {
				if (!vis[j]) {
					curOrd = 0;
					dfsArticulationPoints(j, -1);
				}
			}

			bool flag = false;

			for (int j = 1; j <= n; ++j) {
				// Memset sets the whole array instead of just the portion we need for subtask 5
				for (int k = 1; k <= n; k++)
					vis[k] = vis2[k] = isAdjecentToBlocked[k] = false;
				for (int k = 0; k < m; k++)
					cycle[k] = false;
				curBlocked = j;

				for (p adj : matrix[curBlocked])
					isAdjecentToBlocked[adj.v] = true;

				foundDouble = false;
				bool doubleCycleComp = hasDoubleCycleEdgesTask5();

				memset(cycleNode, false, sizeof cycleNode);
				if (!isAdjecentToCycle(j))
					continue;

				if (!doubleCycleComp) {
					for (int k = 1; k <= n; k++)
						vis[k] = false;

					for (int k = 1; k <= n; k++) {
						if (!vis[k] && k != curBlocked) {
							// Check if this is a dead node
							bool isAlive = false;
							for (p adj : matrix[k])
								isAlive |= cycle[adj.i];
							if (!isAlive)
								continue;

							foundBlocked = false;
							bool ret = cycleOnlyDfs(k, -1) >= 1;
							if (foundBlocked)
								flag |= ret;
						}
					}
				}

				flag |= doubleCycleComp;
			}

			printf(flag ? "YES\n" : "NO\n");
		}

		for (int j = 1; j <= n; j++)
			matrix[j].clear();
	}
}