//============================================================================
// Name        : wcipeg.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 101;
int n, tot = 0,
	arr[MAX], dp[MAX][MAX];

int rec(int l, int r){
	if(l == r) return arr[l];
	if(l > r) return 0;
	if(dp[l][r] != -1) return dp[l][r];

	return dp[l][r] = max(min(rec(l + 2, r), rec(l + 1, r - 1)) + arr[l], min(rec(l, r - 2), rec(l + 1, r - 1)) + arr[r]);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 0; i < n; ++i){
		cin >> arr[i];
		tot += arr[i];
	}

	memset(dp, -1, sizeof dp);

	int best1 = rec(0, n - 1), best2 = tot - best1;

//	printf("dp: [\n");
//	for(int i = 0; i < n; i++){
//		printf("%d : ", i);
//		for(int j = 0; j < n; j++){
//			printf("%d, ", dp[i][j]);
//		}
//		printf("\n");
//	}
//	printf("]\n");
	printf("%d %d\n", best1, best2);
}
