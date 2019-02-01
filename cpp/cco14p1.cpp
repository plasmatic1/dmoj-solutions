//============================================================================
// Name        : Troyangles.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 2001;
int n, tot = 0,
	check[MAX][MAX], dp[MAX][MAX];
char grid[MAX][MAX];
string bs;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n;

	for(int i = 1; i <= n; i++){
		cin >> bs;
		for(int j = 1; j <= n; j++) grid[i][j] = bs[j - 1];
	}

	for(int i = 1; i <= n; i++){
		int last = -1;
		for(int j = 1; j <= n; j++){
			if(grid[i][j] == '#' && last == -1) last = j;
			else if(grid[i][j] == '.' && last != -1){
				for(int k = last; k < j; k++)
					check[i][k] = min(k - last + 1, j - k);
				last = -1;
			}
		}

		if(last != -1){
			for(int j = last; j <= n; j++)
				check[i][j] = min(j - last, n - j) + 1;
		}
	}

	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			if(grid[i][j] == '#')
				dp[i][j] = min(check[i][j], dp[i - 1][j] + 1);
		}
	}

	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			tot += dp[i][j];

	printf("%d\n", tot);

	return 0;
}