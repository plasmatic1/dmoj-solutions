//============================================================================
// Name        : nccc2s5.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct ed{
	int i, v, w;
};

const int MAX = 1001, ME = 5001;
int n, m, q, ba, bb, bc, bt;
vector<ed> matrix[MAX];
bool vis[MAX];

bool dfs(int cur){
	if(cur == bb) return true;
	vis[cur] = true;

	for(ed adj : matrix[cur]){
		if(adj.w >= bc && !vis[adj.v])
			if(dfs(adj.v)) return true;
	}

	return false;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	for (int i = 1; i <= m; ++i) {
		cin >> ba >> bb >> bc;

		matrix[ba].push_back({i, bb, bc});
		matrix[bb].push_back({i, ba, bc});
	}

	cin >> q;

	for (int i = 0; i < q; ++i) {
		cin >> bt >> ba >> bb;

		if(bt == 1){
			for (int i = 1; i <= n; ++i) {
				int sz = matrix[i].size();
				for (int j = 0; j < sz; ++j) {
					if(matrix[i][j].i == ba)
						matrix[i][j].w = bb;
				}
			}
		}
		else{
			cin >> bc;

			printf("%d\n", dfs(ba));
			memset(vis, false, sizeof vis);
		}
	}
}