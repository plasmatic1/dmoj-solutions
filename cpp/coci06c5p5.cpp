//============================================================================
// Name        : Ivana.cpp
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
int n, tot = 0, oddcnt, half,
	arr[MAX], tmp[MAX],
	dp[MAX][MAX];

int rec(int l, int r){
	if(l > r) return 0;
	if(l == r) return tmp[l];
	if(dp[l][r] != -1) return dp[l][r];

	return dp[l][r] = max(min(rec(l + 2, r), rec(l + 1, r - 1)) + tmp[l],
			min(rec(l, r - 2), rec(l + 1, r - 1)) + tmp[r]);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 1; i <= n; ++i){
		cin >> arr[i];
		oddcnt += arr[i] % 2;
	}
	half = oddcnt / 2;

	for (int i = 1; i <= n; ++i) {
		memset(tmp, 0, sizeof tmp);
		copy(arr + i + 1, arr + n + 1, tmp + 1);
		copy(arr + 1, arr + i, tmp + n - i + 1);

		for(int j = 1; j < n; j++)
			tmp[j] %= 2;

		memset(dp, -1, sizeof dp);
		tot += (oddcnt - rec(1, n - 1)) > half;
	}

	printf("%d\n", tot);
}
