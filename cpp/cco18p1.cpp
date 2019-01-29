//============================================================================
// Name        : GeeseVsHawks.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 1001;
int n, buf,
	geesepts[MAX], hawkpts[MAX], dp[MAX][MAX];
char geesewl[MAX], hawkwl[MAX];

inline int pts(int i, int j){
	int gp = geesepts[i], hp = hawkpts[j]; //Hey look its helen haha
	if(gp < hp){
		if(geesewl[i] == 'L' && hawkwl[j] == 'W'){
			return gp + hp;
		}
		return 0;
	}
	else if(gp > hp){
		if(geesewl[i] == 'W' && hawkwl[j] == 'L'){
			return gp + hp;
		}
		return 0;
	}
	return 0;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	//Input

	cin >> n;

	cin >> geesewl;
	copy(geesewl, geesewl + n, geesewl + 1);

	for (int i = 1; i <= n; ++i) {
		cin >> geesepts[i];
	}

	cin >> hawkwl;
	copy(hawkwl, hawkwl + n, hawkwl + 1);

	for (int i = 1; i <= n; ++i) {
		cin >> hawkpts[i];
	}

	//Dp

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			dp[i][j] = max(dp[i - 1][j], max(dp[i][j - 1], dp[i - 1][j - 1] + pts(i, j)));
		}
	}

	printf("%d\n", dp[n][n]);
}
