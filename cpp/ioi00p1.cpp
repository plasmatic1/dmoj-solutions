//============================================================================
// Name        : Palindrome.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 5001;
int n, cur = 0, nxt,
	dp[2][MAX];
string s, t;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> s;
	t = s;
	reverse(t.begin(), t.end());

	for(int i = 1; i <= n; i++){
		nxt = !cur;

		for(int j = 1; j <= n; j++){
			if(s[i - 1] == t[j - 1]) dp[nxt][j] = dp[cur][j - 1] + 1;
			else dp[nxt][j] = max(dp[cur][j], dp[nxt][j - 1]);
		}

		cur = nxt;
	}

	printf("%d\n", n - dp[cur][n]);
}
