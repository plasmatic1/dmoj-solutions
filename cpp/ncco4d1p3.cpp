//============================================================================
// Name        : HungryGames.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
using namespace std;

struct e{
	int v, w;
	e(int v0, int w0) : v(v0), w(w0){
		//
	}

	friend bool operator<(const e &a, const e &b){
		return a.w < b.w;
	}
};

int n, m, dist[20000], dist2[20000];
vector<e> matrix[20000];

int main() {
	scanf("%d %d\n", &n, &m);

	for(int i = 0; i < m; i++){
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		a--;
		b--;
		matrix[a].emplace_back(b, c);
		matrix[b].emplace_back(a, c);
	}

//	assert(false);

	priority_queue<e> next;
	memset(dist, 0x3f, sizeof(dist));
	memset(dist2, 0x3f, sizeof(dist2));

	next.push(e(0, 0));
	dist[0] = 0;

	while(!next.empty()){
		e curr = next.top();
		next.pop();

		if(curr.w > dist2[curr.v]){
			continue;
		}

		for(e adj : matrix[curr.v]){
			int alt = dist[curr.v] + adj.w, alt2 = dist2[curr.v] + adj.w;

			if(alt < dist[adj.v]){
				dist2[adj.v] = dist[adj.v];
				dist[adj.v] = alt;
				next.emplace(adj.v, alt);
			}
			else if(alt < dist2[adj.v] && alt != dist[adj.v]){
				dist2[adj.v] = alt;
				next.emplace(adj.v, alt);
			}
			else if(alt2 < dist2[adj.v] && alt2 != dist[adj.v]){
				dist2[adj.v] = alt2;
				next.emplace(adj.v, alt2);
			}
		}
	}

//	assert(false);

	if(dist2[n - 1] == INT_MAX){
		printf("-1\n");
	}
	else{
		printf("%d\n", dist2[n - 1]);
	}

	return 0;
}