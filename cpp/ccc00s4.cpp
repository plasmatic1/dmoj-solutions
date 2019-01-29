//============================================================================
// Name        : Golf.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int ML = 5281;
int d, n, buf,
	dp[ML];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> d >> n;

	memset(dp, 0x3f, sizeof(dp));
	dp[0] = 0;

	for (int i = 0; i < n; ++i) {
		cin >> buf;

		for (int j = buf; j <= d; ++j) {
			dp[j] = min(dp[j], dp[j - buf] + 1);
		}
	}

	// Output

	if(dp[d] == 0x3f3f3f3f){
		printf("Roberta acknowledges defeat.\n");
	}
	else{
		printf("Roberta wins in %d strokes.\n", dp[d]);
	}
}
