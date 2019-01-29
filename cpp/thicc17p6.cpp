//============================================================================
// Name        : THICCest CS CONTEST EVER
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <algorithm>
#include <cstdio>
#include <queue>
#include <utility>
#include <vector>
#include <assert.h>

using namespace std;

typedef pair<int, int> e;

void bfs(int start, int levels[], vector<e> matrix[], int n){
	fill(levels, levels + n, -1);
	queue<e> next;
	next.push(e(start, 0));
	while(!next.empty()){
		e curr = next.front();
		next.pop();

		for(e adj : matrix[curr.first]){
			if(levels[adj.first] != -1){
				continue;
			}

			levels[adj.first] = levels[curr.first] + adj.second;
			next.push(adj);
		}
	}
}

int maxNode(int levels[], int n){
	int maxd = -1, maxn = -1;
	for(int i = 0; i < n; i++){
		if(levels[i] > maxd){
			maxd = levels[i];
			maxn = i;
		}
	}
	return maxn;
}

int main() {
	int n, t, edges = 0;
	scanf("%d %d", &n, &t);

	vector<e> matrix[n];
	int n0 = n - 1, to[n];

	fill(to, to + n, 0);

	for(int i = 0; i < n0; i++){
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		a--;
		b--;
		matrix[a].push_back(e(b, c));
		matrix[b].push_back(e(a, c));
		to[a]++;
		to[b]++;
		edges += c;
	}

//	assert(0);

	int levels[n], levels0[n], levels1[n];
	bfs(0, levels, matrix, n);
	int maxn = maxNode(levels, n);
	bfs(maxn, levels0, matrix, n);
	int maxn2 = maxNode(levels0, n);
	bfs(maxn2, levels1, matrix, n);

	for(int i = 0; i < n; i++){
		if(to[i] == t){
			printf("%d %d\n", i + 1, 2 * edges - max(levels0[i], levels1[i]) - 1);
		}
	}

	return 0;
}
