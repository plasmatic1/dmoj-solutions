//============================================================================
// Name        : AtcoderDpF.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 3001;
int n, m,
	dp[MAX][MAX], parx[MAX][MAX], pary[MAX][MAX];
string s, t;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> s >> t;
	n = s.length();
	m = t.length();

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if(s[i - 1] == t[j - 1]){
				parx[i][j] = i - 1;
				pary[i][j] = j - 1;
				dp[i][j] = dp[i - 1][j - 1] + 1;
			}
			else{
				int best = -1;

				if(dp[i - 1][j] > best){
					best = dp[i - 1][j];
				}
				if(dp[i][j - 1] > best){
					best = dp[i][j - 1];
				}

				dp[i][j] = best;
			}
		}
	}

	string lcs = "";

	int x = n, y = m;
	while(x != 0 && y != 0){
		int left = dp[x - 1][y], up = dp[x][y - 1], curr = dp[x][y];

		if(curr == left) x--;
		else if(curr == up) y--;
		else{
			lcs.push_back(s[x - 1]);
			x--;
			y--;
		}
	}

	reverse(lcs.begin(), lcs.end());

	printf("%s\n", lcs.c_str());
}
