//============================================================================
// Name        : SchoolTraversal.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
#define DEBUG

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

int n, q, ba, bb, bw;

struct ed{
	int v, w;

	ed(int v0, int w0) : v(v0), w(w0){}
	ed() : v(-1), w(-1){}
};

const int MAX = 6001, B_MAX = 18;
int firstinstances[MAX], dist[MAX];
ll distt[MAX];

int sptable[B_MAX][MAX * 2 + 1], path_size = 1; // The base 2 log of 100000 (Max size) is ~16.609, I used 18 to be safe
#define PUSH_EDGE(x) sptable[0][path_size++] = x // Push edge

vector<ed> matrix[MAX]; // Adjecency Matrix

inline int dist_min(int a, int b){ // Gets min distance of nodes `a` and `b`
	return dist[a] < dist[b] ? a : b;
}

int query(int a, int b){ // Querys the range from `a` to `b`
	// Change to RMQ Indxes
	a = firstinstances[a];
	b = firstinstances[b];

	if(a >= b){
		swap(a, b);
	}

	// Find max bit
	int delta = b - a, maxbit = 1, // Max bit begins at 1 to account for `b - maxbit + 1` when `a == b`
			maxbitind = 0; // Row of the sparse table to use

	for (int i = B_MAX; i >= 0; --i) {
		int v = 1 << i;

		if(delta & v){
			maxbit = v;
			maxbitind = i;
			break;
		}
	}

	// Return Range
	return dist_min(sptable[maxbitind][a],
			sptable[maxbitind][b - maxbit + 1]);
}

// DFS
void dfs(int curr, int lvl, ll dis, int parent){
	PUSH_EDGE(curr);
	dist[curr] = lvl;
	distt[curr] = dis;

	for(ed adj : matrix[curr]){
		if(adj.v != parent){
			dfs(adj.v, lvl + 1, dis + adj.w, curr);
			PUSH_EDGE(curr);
		}
	}
}

void build(){
	// DFS to build tour
	dfs(1, 0, 0, -1);

	// Get first indexes of nodes
	for (int i = 1; i <= path_size; ++i) {
		if(!firstinstances[sptable[0][i]]){
			firstinstances[sptable[0][i]] = i;
		}
	}

	// Building sparse table
	for (int i = 1; i < B_MAX; ++i) {
		int gap = 1 << (i - 1), maxv = path_size - (1 << i) + 1;

		for (int j = 1; j <= maxv; ++j) {
			sptable[i][j] = dist_min(sptable[i - 1][j],
					sptable[i - 1][j + gap]);
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 1; i < n; ++i) {
		cin >> ba >> bb >> bw;

		matrix[ba].emplace_back(bb, bw);
		matrix[bb].emplace_back(ba, bw);
	}

	build();

	cin >> q;

	for (int i = 0; i < q; ++i) {
		cin >> ba >> bb;

		int par = query(ba, bb);

		printf("%lld\n", distt[ba] + distt[bb] - 2 * distt[par]);
	}
}
