//============================================================================
// Name        : ACC2P2Poutine.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 501;
vector<int> matrix[MAX];
int n, tot = 0;
bool vis[MAX][MAX];
string buf;

void dfs(int start, int cur){
	if(vis[start][cur]) return;
	vis[start][cur] = true;
	for(int adj : matrix[cur])
		dfs(start, adj);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> buf;
		for (int j = 0; j < n; ++j)
			if(buf[j] == '1')
				matrix[i].push_back(j);
	}

	for (int i = 0; i < n; ++i)
		dfs(i, i);

	for (int i = 0; i < n; ++i)
		for (int j = i + 1; j < n; ++j)
			tot += !(vis[i][j] || vis[j][i]);

	printf("%d\n", tot);
}