//============================================================================
// Name        : DistributionChannel.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

struct ed{
	int a, b, c;

	ed(int a0, int b0, int c0) : a(a0), b(b0), c(c0){}
	ed() : a(-1), b(-1), c(-1){}

	friend bool operator<(const ed &a, const ed &b){
		return a.c < b.c;
	}
};

struct edd{
	int v, w;

	edd(int a, int b) : v(a), w(b){}
	edd() : v(-1), w(-1){}
};

const int MAX = 100001, NM = 100001;
int n, m, ba, bb, bc, msttotal = 0, best = INT_MAX;
ed edges[MAX];

struct disjoint{
	int set[NM], size;

	disjoint(int sz){
		size = sz;
		for(int i = 0; i < size; i++){
			set[i] = i;
		}
	}

	int root(int val){
		if(set[val] == val){
			return val;
		}

		return set[val] = root(set[val]);
	}

	void unite(int v1, int v2){
		int rv1 = root(v1);
		int rv2 = root(v2);

		if(v1 == v2){
			return;
		}

		if(v1 < v2){
			set[rv2] = rv1;
			root(v2);
		}
		else{
			set[rv1] = rv2;
			root(v1);
		}
	}

	bool same(int v1, int v2){
		return root(v1) == root(v2);
	}
};

disjoint dset(NM);
bool inmst[NM];

// Sparse Table Setup

const int B_MAX = 18;
int dist[MAX];
ll distt[MAX];

int sptable[B_MAX][NM], costable[B_MAX][NM];
vector<edd> matrix[NM]; // Adjecency Matrix

int query(int a, int b){ // Querys nodes `a` and `b`
	if(dist[a] > dist[b]){
		swap(a, b);
	}

	int maxv = INT_MIN;

	// Equalizing levels
	int delta = dist[b] - dist[a];
	for (int i = B_MAX - 1; i >= 0; --i) {
		if(delta & (1 << i)){
			maxv = max(maxv, costable[i][b]);
			b = sptable[i][b];
		}
	}

	// Checking if they are the same again now that levels are equal
	if(a == b){
		return maxv;
	}

	// Moving up the chain
	for(int i = B_MAX - 1; i >= 0; --i){
		if(sptable[i][a] != sptable[i][b] && sptable[i][a] != -1 && sptable[i][b] != -1){
			maxv = max(maxv, max(costable[i][a], costable[i][b]));

			a = sptable[i][a];
			b = sptable[i][b];
		}
	}

	return max(maxv, max(costable[0][a], costable[0][b]));
}

// DFS
void dfs(int curr, int lvl, int lasted, int parent){
	dist[curr] = lvl;
	costable[0][curr] = lasted;
	sptable[0][curr] = parent;

	for(edd adj : matrix[curr]){
		if(adj.v != parent){
			dfs(adj.v, lvl + 1, adj.w, curr);
		}
	}
}

void build(){
	// DFS to build first parents and arrays
	dfs(1, 0, -1, -1);

	// Building sparse table
	for (int i = 1; i < B_MAX; ++i) {
		for (int j = 1; j <= n; ++j) {
			int directpar = sptable[i - 1][j];

			if(directpar != -1){
				sptable[i][j] = sptable[i - 1][directpar];
				costable[i][j] = max(costable[i - 1][j], costable[i - 1][directpar]);
			}
			else{
				sptable[i][j] = -1;
			}
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	for (int i = 0; i < m; ++i) {
		cin >> ba >> bb >> bc;
		edges[i] = ed(ba, bb, bc);
	}

	sort(edges, edges + m);

	// First run of kruskal

	int cnt = 0;
	for (int i = 0; i < m; ++i) {
		if(!dset.same(edges[i].a, edges[i].b)){
			cnt++;
			inmst[i] = true;
			dset.unite(edges[i].a, edges[i].b);
			matrix[edges[i].a].emplace_back(edges[i].b, edges[i].c);
			matrix[edges[i].b].emplace_back(edges[i].a, edges[i].c);
			msttotal += edges[i].c;
		}
	}

	if(cnt < n - 1){
		printf("-1\n");
		return 0;
	}

	// Initialize binary lift

	build();

	// Attempt to replace edge

	for (int i = 0; i < m; ++i) {
		if(!inmst[i]){
//			printf("attempt edge a=%d b=%d c=%d, adding=%d, removing=%d\n", edges[i].a, edges[i].b,
//					edges[i].c, edges[i].c, query(edges[i].a, edges[i].b));
			int rem = edges[i].c - query(edges[i].a, edges[i].b);

			best = min(best, rem > 0 ? rem : INT_MAX);
		}
	}

	// Output

	if(best == INT_MAX){
		printf("-1\n");
	}
	else{
		printf("%d\n", msttotal + best);
	}
}
