//============================================================================
// Name        : SummingASequence.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 1000002;
int n;
ll arr[MAX], dp[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 1; i <= n; ++i) {
		cin >> arr[i + 1];
	}

	int m = n + 1;
	for (int i = 2; i <= m; ++i) {
		dp[i] = max(dp[i - 1], dp[i - 2] + arr[i]);
	}

	printf("%lld\n", dp[m]);
}
