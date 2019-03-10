//============================================================================
// Name        : tle17c3p3.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 300001;
int n, m, ba, bb, bc,
	req[MAX];
vector<int> matrix[MAX];
bool vis[MAX];

int dfs(int cur){
	if(vis[cur]) return 0;
	if(!matrix[cur].size()) return req[cur];

	vis[cur] = true;

	int best = INT_MAX;
	for(int adj : matrix[cur])
		best = min(best, dfs(adj));

	return req[cur] += best;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	for (int i = 0; i < m; ++i) {
		cin >> ba >> bb;
		for (int j = 0; j < bb; ++j) {
			cin >> bc;
			matrix[ba].push_back(bc);
		}
	}

	for (int i = 1; i <= n; ++i)
		cin >> req[i];

	dfs(1);

	printf("%d\n", req[1]);
}