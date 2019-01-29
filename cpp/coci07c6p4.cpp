//============================================================================
// Name        : George.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

struct e{
	int v, w;

	e(int v0, int w0) : v(v0), w(w0){}
	e() : v(-1), w(-1){}

	friend bool operator<(const e &a, const e &b){
		return a.w > b.w;
	}
};

const int MAX = 1001;
int n, m, a, b, k, g, ba, bb, bc,
	dists[MAX], george[MAX],
	blockeds[MAX][MAX], blockede[MAX][MAX], weights[MAX][MAX];

vector<e> matrix[MAX];
priority_queue<e> nextt;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m >> a >> b >> k >> g;

	for (int i = 0; i < g; ++i) {
		cin >> george[i];
	}

	for (int i = 0; i < m; ++i) {
		cin >> ba >> bb >> bc;

		matrix[ba].emplace_back(bb, bc);
		matrix[bb].emplace_back(ba, bc);

		weights[ba][bb] = bc;
		weights[bb][ba] = bc;
	}

	memset(dists, 0x3f, sizeof(dists));
	memset(blockeds, -1, sizeof(blockeds));
	memset(blockede, -1, sizeof(blockede));

	// Setting up blocked

	int g0 = g - 1, ctime = -k;
	for (int i = 0; i < g0; ++i) {
		int ca = george[i], cb = george[i + 1], wt = weights[ca][cb];

		blockeds[ca][cb] = ctime;
		blockeds[cb][ca] = ctime;

		blockede[ca][cb] = ctime + wt;
		blockede[cb][ca] = ctime + wt;

		ctime += wt;
	}

	// Dijkstra's algo

	dists[a] = 0;
	nextt.emplace(a, 0);

	while(!nextt.empty()){
		e curr = nextt.top();
		nextt.pop();

		if(curr.v == b){
			break;
		}

		if(curr.w > dists[curr.v]){
			continue;
		}

		for(e adj : matrix[curr.v]){
			int alt = adj.w;

			if(curr.w >= blockeds[curr.v][adj.v] && curr.w <= blockede[curr.v][adj.v]){
				alt += blockede[curr.v][adj.v];
			}
			else{
				alt += curr.w;
			}

			if(alt < dists[adj.v]){
				dists[adj.v] = alt;
				nextt.emplace(adj.v, alt);
			}
		}
	}

	// Output

	printf("%d\n", dists[b]);
}
