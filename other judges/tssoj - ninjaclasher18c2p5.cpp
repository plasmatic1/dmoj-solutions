//============================================================================
// Name        : nc2p5.cpp
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
	int v, w;

	ed(int v0, int w0) : v(v0), w(w0){}
	ed() : v(-1), w(-1){}

	friend bool operator<(const ed &a, const ed &b){
		return a.w > b.w;
	}

	friend bool operator>(const ed &a, const ed &b){
			return a.w < b.w;
	}
};

const int MAX = 100001;
int n, m, a, b, ba, bb, bc,
	dist[MAX], counts[MAX];
vector<ed> matrix[MAX];
priority_queue<ed> nextt;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m >> a >> b;

	for (int i = 0; i < m; ++i) {
		cin >> ba >> bb >> bc;

		matrix[ba].emplace_back(bb, bc);
		matrix[bb].emplace_back(ba, bc);
	}

	for (int i = 1; i <= n; ++i) {
		sort(matrix[i].begin(), matrix[i].end(), greater<ed>());
	}

	// First do dijkstra for min dist;

	memset(dist, 0x3f, sizeof(dist));
	dist[a] = 0;
	counts[a] = 1;
	nextt.emplace(a, 0);

	while(!nextt.empty()){
		ed curr = nextt.top();
		nextt.pop();

		if(curr.w > dist[curr.v]){
			continue;
		}

		for(ed adj : matrix[curr.v]){
			int alt = curr.w + adj.w;

			if(alt < dist[adj.v]){
				counts[adj.v] = counts[curr.v];

				dist[adj.v] = alt;
				nextt.emplace(adj.v, alt);
			}
			else if(alt == dist[adj.v]){
				counts[adj.v] += counts[curr.v];
			}
		}
	}

	printf("%d\n%d\n", dist[b], counts[b]);
}
