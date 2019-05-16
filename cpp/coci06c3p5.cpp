//============================================================================
// Name        : coci06c3p5.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Scan and Debug
void scan(){}
template<typename F, typename... R> void scan(F &f,R&... r){cin>>f;scan(r...);}
int di_; string dnms_, co_ = ",";
void debug_(){cout<<endl;}
template<typename F, typename... R> void debug_(F f, R... r){while(dnms_[di_] != ',')cout<<dnms_[di_++];di_++;cout<<": "<<f<<",";debug_(r...);}
#define debug(...) dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__)

const int MAX = 10001;
const ll MOD = 1000000000;
int n, m, ba, bb;
ll dp[MAX];
vector<int> topo,
	amatrix[MAX], matrix[MAX];
bool over = false,
	vis[MAX], vis1[MAX], vis2[MAX], before[MAX];

void toposort(int cur) {
	if(vis[cur]) return;

	vis[cur] = true;
	for (int adj : amatrix[cur])
		toposort(adj);
	topo.push_back(cur);
}

void dfs(int cur, vector<int> matrix[], bool vis[]) {
	if (vis[cur]) return;

	vis[cur] = true;
	for (int adj : matrix[cur])
		dfs(adj, matrix, vis);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	scan(n, m);

	for (int i = 0; i < m; ++i) {
		scan(ba, bb);
		matrix[ba].push_back(bb);
		amatrix[bb].push_back(ba);
	}

	// prep
	dfs(1, matrix, vis1);
	dfs(2, amatrix, vis2);
	toposort(2);

	// cycle
	for (int i : topo) {
		if (vis1[i] && vis2[i]) {
			bool flag = false;
			for (int adj : matrix[i])
				flag |= before[adj];

			if (flag) {
				printf("inf\n");
				return 0;
			}
		}

		before[i] = true;
	}

	// dp
	dp[1] = 1;
	for (int i : topo) {
		if (dp[i] >= MOD) {
			dp[i] %= MOD;
			over = true;
		}

		for (int adj : matrix[i])
			dp[adj] += dp[i];
	}

	if (over)
		printf("%09lld\n", dp[2]);
	else
		printf("%lld\n", dp[2]);

	return 0;
}