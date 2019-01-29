//============================================================================
// Name        : CosimosDaringEscape.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 100001;
int n, q, ba, bb,
	levels1[MAX], levels2[MAX];
vector<int> matrix[MAX];
unordered_set<int> endpoints;

void bfs(int* levels, int start){
	deque<int> nextt;

	levels[start] = 0;
	nextt.push_back(start);

	while(!nextt.empty()){
		int curr = nextt.front(), level = levels[curr];
		nextt.pop_front();

		for(int adj : matrix[curr]){
			if(levels[adj] == -1){
				levels[adj] = level + 1;
				nextt.push_back(adj);
			}
		}
	}
}

inline int maxdis(int* levels){
	return *max_element(levels + 1, levels + n + 1);
}

inline int max_node(int* levels){
	int maxv = -1, maxi = -1;

	for (int i = 1; i <= n; ++i) {
		if(levels[i] > maxv){
			maxv = levels[i];
			maxi = i;
		}
	}

	return maxi;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> q;

	for (int i = 1; i < n; ++i) {
		cin >> ba >> bb;

		matrix[ba].push_back(bb);
		matrix[bb].push_back(ba);
	}

	// Find diameter and endpoints

	memset(levels1, -1, sizeof(levels1));
	memset(levels2, -1, sizeof(levels2));

	bfs(levels1, 1);
	int enda = max_node(levels1);

	memset(levels1, -1, sizeof(levels1));
	bfs(levels1, enda);
	int endb = max_node(levels1);

	bfs(levels2, endb);
	int dia = maxdis(levels2);

	for (int i = 1; i <= n; ++i) {
		if(levels1[i] == dia || levels2[i] == dia){
			endpoints.insert(i);
		}
	}

	// Queries

	for (int i = 0; i < q; ++i) {
		cin >> ba >> bb;

		if(endpoints.count(ba)){
			printf("%lld\n", (ll)dia * (ll)bb);
		}
		else{
			printf("%lld\n", (ll)dia * (ll)(bb - 1) + max(levels1[ba], levels2[ba]));
		}
	}
}
