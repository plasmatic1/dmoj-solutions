//============================================================================
// Name        : dpl.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 3001;
const ll INF = 0x3f3f3f3f3f3f3f3f;
int n,
	arr[MAX];
ll tot = 0,
	dp[MAX][MAX];

ll rec(int l, int r){
	if(l == r) return arr[l];
	if(dp[l][r] != INF) return dp[l][r];

	// take left, take right
	return dp[l][r] = max(arr[l] - rec(l + 1, r), arr[r] - rec(l, r - 1));
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for(int i = 0; i < n; i++)
		cin >> arr[i], tot += arr[i];

	memset(dp, 0x3f, sizeof dp);
	printf("%lld\n", rec(0, n - 1));
}
