//============================================================================
// Name        : Tattarrattat.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

#ifdef ONLINE_JUDGE
const int T = 5;
#else
const int T = 1;
#endif

const int MAX = 256;
int n, h;
string s;
int dp[MAX][MAX];

inline bool ispalindrome(string &s){
	string tmp = s;
	reverse(tmp.begin(), tmp.end());

	return s == tmp;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	for (int idddddd = 0; idddddd < T; ++idddddd) {
		cin >> s;
		n = s.length();

		memset(dp, 0, sizeof(dp));

		for (int i = 0; i < n; ++i) {
			dp[i][i] = 1;
		}

		for (int i = 2; i <= n; ++i) {
			for (int j = 0; j < n - i + 1; ++j) {
				int r = j + i - 1;

				if(s[j] == s[r]){
					dp[j][r] = dp[j + 1][r - 1] + 2;
				}
				else{
					dp[j][r] = max(dp[j + 1][r], dp[j][r - 1]);
				}
			}
		}

//		printf("dp: [\n");
//		for(int i = 0; i < n; i++){
//			printf("%d : ", i);
//			for(int j = 0; j < n; j++){
//				printf("%d, ", dp[i][j]);
//			}
//			printf("\n");
//		}
//		printf("]\n");

		printf("%d\n", dp[0][n - 1]);
	}
}
