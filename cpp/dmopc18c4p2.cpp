//============================================================================
// Name        : DrHenriAndResponsibility.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 701, MV = MAX * MAX + 1;
int n, buf, tot = 0, best = INT_MAX,
	tasks[MAX];
bool dp[MV];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 1; i <= n; ++i) {
		cin >> tasks[i];
		tot += tasks[i];
	}

	dp[0] = true;


	for (int i = 0; i < n; ++i) {
		for (int j = tot; j >= tasks[i]; --j) {
			if(dp[j - tasks[i]]){
				dp[j] = true;
			}
		}
	}

	for (int i = 0; i <= tot; ++i) {
		if(dp[i]){
			best = min(best, abs(i - (tot - i)));
		}
	}

	printf("%d\n", best);
}
