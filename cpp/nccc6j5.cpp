//============================================================================
// Name        : dmojmockccc19j5.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<string, int> p;

const ll MOD = 998244353;
const int MAX = 1001, INF = 0x3f3f3f3f;
int n, k, buf, sz,
	cnt[MAX], dp[MAX][MAX];
vector<int> available;

ll rec(int curri, int currk){
	if(dp[curri][currk] != -1) return dp[curri][currk];
	if(currk == k) return dp[curri][currk] = 1;
	if(curri == sz) return 0;

	// choose sushi i or not choose sushi i
	return dp[curri][currk] = (((rec(curri + 1, currk + 1) * cnt[available[curri]]) % MOD) + rec(curri + 1, currk)) % MOD;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> k;

	memset(dp, -1, sizeof dp);

	for (int i = 0; i < n; ++i) {
		cin >> buf;
		cnt[buf]++;
	}

	for (int i = 1; i <= n; ++i) {
		if(cnt[i]) available.push_back(i);
	}
	sz = available.size();

	if(sz < k){
		printf("0\n");
	}
	else{
//		dp[0][0] = 1;
		printf("%lld\n", rec(0, 0) % MOD);
	}
}
