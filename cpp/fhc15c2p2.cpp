//============================================================================
// Name        : AllCritical.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 25, N = 20;
int t;
double p,
	dp[MAX];
ll tria[MAX][MAX];

inline void maketria(int n){
	tria[1][1] = 1;
	for(int i = 1; i < n; i++){
		for(int j = 1; j <= i; j++){
			tria[i + 1][j] += tria[i][j];
			tria[i + 1][j + 1] += tria[i][j];
		}
	}
}

#define choose(n, k) (tria[(n) + 1][(k) + 1])

/*
Given n coins, the probability of getting k of them to be heads,
with the probability of getting one heads being p, can be computed
with the following formula:

(n choose k) * p^k * (1 - p)^(n - k)
 */

double rec(int cur){
	if(cur == N) return 0;
	if(dp[cur] != 0) return dp[cur];

	double tot = 0;
	int left = N - cur;
	for(int i = 1; i <= left; i++){
		tot += choose(left, i) * pow(p, i) * pow(1 - p, left - i) * rec(cur + i);
	}

	return dp[cur] = (1 + tot) / (1 - pow(1 - p, left));
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> t;

	maketria(N + 1);

	for(int i = 1; i <= t; i++){
		cin >> p;

		printf("Case #%d: %.12f\n", i, rec(0));

//		for(int i = 0; i <= N; i++){
//			printf("%f, ", dp[i]);
//		}
//		printf("\n");

		memset(dp, 0., sizeof dp);
	}
}
