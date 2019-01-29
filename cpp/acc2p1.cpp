//============================================================================
// Name        : ACC2P1Poutine.cpp
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
};

const int MAX = 201, INF_BYTE = 0x3f;
ll INF = 0x3F3F3F3F3F3F3F3F;
int n, q, buf, bs, bt, bd;
ll dp[MAX][MAX][MAX];
// In d days from s to t

vector<ed> matrix[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> buf;

			if(buf != 0){
				matrix[i].emplace_back(j, buf);
			}
		}
	}

	// Run DP

	memset(dp, INF_BYTE, sizeof(dp));

	for (int i = 1; i <= n; ++i) {
		dp[1][i][i] = 0;

		for(ed adj : matrix[i]){
			dp[1][i][adj.v] = adj.w;
		}
	}

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			for (int k = 1; k <= n; ++k) {
				dp[1][j][k] = min(dp[1][j][k], dp[1][j][i] + dp[1][i][k]);
			}
		}
	}

//	printf("dp[1]: [\n");
//	for(int i = 1; i < n + 1; i++){
//		printf("%d : ", i);
//		for(int j = 1; j < n + 1; j++){
//			printf("%d, ", dp[1][i][j]);
//		}
//		printf("\n");
//	}
//	printf("]\n");

	for (int d = 2; d <= n; ++d) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				for (int k = 1; k <= n; ++k) {
					dp[d][j][k] = min(dp[d][j][k], max(dp[d - 1][j][i], dp[1][i][k]));
				}
			}
		}
	}

	// Answering Queries

	cin >> q;

	for (int i = 0; i < q; ++i) {
		cin >> bs >> bt >> bd;

		ll val = dp[bd][bs][bt];

		if(val == INF){
			printf("0\n");
		}
		else{
			printf("%lld\n", val);
		}
	}
}
