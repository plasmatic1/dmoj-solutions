//============================================================================
// Name        : PhonomenalReviews.cpp
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
int n, m, ba, bb, bc,
	levels[MAX];
bool good[MAX];
vector<int> matrix[MAX];

bool dfs(int cur, int par){
	bool &flag = good[cur];

	for(int adj : matrix[cur])
		if(adj ^ par)
			flag |= dfs(adj, cur);

	return flag;
}

void dfs2(int cur, int lvl){
	levels[cur] = lvl;

	for(int adj : matrix[cur])
		if(levels[adj] == -1 && good[adj])
			dfs2(adj, lvl + 1);
}

int edgecnt(int cur, int par){
	int cnt = 0;

	for(int adj : matrix[cur])
		if(good[adj] && (adj ^ par))
			cnt += edgecnt(adj, cur) + 1;

	return cnt;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	for (int i = 0; i < m; ++i) {
		cin >> bc;
		good[bc] = true;
	}

	for (int i = 1; i < n; ++i) {
		cin >> ba >> bb;

		matrix[ba].push_back(bb);
		matrix[bb].push_back(ba);
	}

	dfs(bc, -1);

	memset(levels, -1, sizeof levels);
	dfs2(bc, 0);

	int besti = -1, bestv = -10;
	for(int i = 0; i < n; i++){
		if(levels[i] > bestv){
			bestv = levels[i];
			besti = i;
		}
	}

	memset(levels, -1, sizeof levels);
	dfs2(besti, 0);

	int dia = *max_element(levels, levels + n);

	printf("%d\n", 2 * edgecnt(bc, -1) - dia);
}
