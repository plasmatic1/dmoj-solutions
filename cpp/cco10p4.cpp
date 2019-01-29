//============================================================================
// Name        : ComputerPurchaseReturn.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct p{
	int c, v;
};

const int MAX = 1001, MB = 3001, MT = 6;
int n, t, b, bc, bv, bt,
	dp[MB], tdp[MB], ttdp[MB]; // tdp -> temp dp for each part
vector<p> parts[MT];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> t >> n;

	for (int i = 0; i < n; ++i) {
		cin >> bc >> bv >> bt;

		parts[--bt].push_back({bc, bv});
	}

	cin >> b;

	dp[0] = 0;
	for (int i = 0; i < t; ++i) {
		memset(tdp, -1, sizeof tdp);

		int sz = parts[i].size();
		for (int j = 0; j < sz; ++j) {
			memset(ttdp, -1, sizeof ttdp);

			for(int k = parts[i][j].c; k <= b; k++){
				if(dp[k - parts[i][j].c] != -1) ttdp[k] = max(ttdp[k], dp[k - parts[i][j].c] + parts[i][j].v);
			}

			for (int k = 0; k <= b; ++k) {
				tdp[k] = max(tdp[k], ttdp[k]);
			}
		}

		for (int j = 0; j <= b; ++j) {
			dp[j] = tdp[j];
		}
	}

	printf("%d\n", dp[b]);
}
