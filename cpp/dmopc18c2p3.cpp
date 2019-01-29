//============================================================================
// Name        : ThanksgivingFeast.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
//#define DEBUG

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 100001;
int n, m, k, a, b, ba, bb,
	levelsa[MAX], levelsb[MAX], dest[MAX];

vector<int> matrix[MAX];

void bfs(int start, int n, int *levels){
	deque<int> next;
	next.push_back(start);

	fill(levels, levels + n + 1, -1);
	levels[start] = 0;

	while(!next.empty()){
		int curr = next.front();
		next.pop_front();
		int level = levels[curr];

		for(int adj : matrix[curr]){
			if(levels[adj] != -1){
				continue;
			}

			levels[adj] = level + 1;
			next.push_back(adj);
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m >> k >> a >> b;

	for (int i = 0; i < k; ++i) {
		cin >> dest[i];
	}

	for (int i = 0; i < m; ++i) {
		cin >> ba >> bb;

		matrix[ba].push_back(bb);
		matrix[bb].push_back(ba);
	}

	bfs(a, n, levelsa);
	bfs(b, n, levelsb);

#ifdef DEBUG
	printf("levelsa: ");
	for (int i = 0; i < n + 1; ++i) {
		printf("%d, ", levelsa[i]);
	}
	printf("\n");
	printf("levelsb: ");
	for (int i = 0; i < n + 1; ++i) {
		printf("%d, ", levelsb[i]);
	}
	printf("\n");
#endif

	int mindist = INT_MAX;
	for (int i = 0; i < k; ++i) {
		mindist = min(mindist, levelsa[dest[i]] + levelsb[dest[i]]);
	}

	printf("%d\n", mindist);
}
