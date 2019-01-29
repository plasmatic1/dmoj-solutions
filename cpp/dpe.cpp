//============================================================================
// Name        : AtcoderDpE.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 100001;
int n, w, bw, bv;
ll dp[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> w;

	memset(dp, 0x3f, sizeof(dp));
	dp[0] = 0;

	for (int i = 0; i < n; ++i) {
		cin >> bw >> bv;

		for(int j = MAX - 1; j >= bv; j--){
			dp[j] = min(dp[j], dp[j - bv] + bw);
		}
	}

	int best = -1;
	for (int i = 0; i < MAX; ++i){
		if(dp[i] <= w){
			best = i;
		}
	}

	printf("%d\n", best);
}
