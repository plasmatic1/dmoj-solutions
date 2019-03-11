//============================================================================
// Name        : dpk.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 101, MK = 100001;
int n, k,
	arr[MAX], dp[MK];

int rec(int c){
	if(c == 0) return 0;
	if(dp[c] != -1) return dp[c];

	int maxv = 0;
	for(int i = 0; i < n; i++)
		if(c >= arr[i])
			maxv = max(maxv, (int)!rec(c - arr[i]));

	return dp[c] = maxv;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> k;

	for(int i = 0; i < n; i++)
		cin >> arr[i];

	memset(dp, -1, sizeof dp);
	if(rec(k)) printf("First\n");
	else printf("Second\n");
}
