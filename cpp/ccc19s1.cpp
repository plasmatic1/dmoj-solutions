//============================================================================
// Name        : ccc19s1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n,
	grid[2][2] = {{1, 2}, {3, 4}};
string s;
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> s;
	n = s.length();

	for (int i = 0; i < n; ++i) {
		if(s[i] == 'V'){
				int a = grid[0][1], b = grid[1][1];
				grid[0][1] = grid[0][0];
				grid[1][1] = grid[1][0];
				grid[0][0] = a;
				grid[1][0] = b;
		}
		else{
				int a = grid[1][0], b = grid[1][1];
				grid[1][0] = grid[0][0];
				grid[1][1] = grid[0][1];
				grid[0][0] = a;
				grid[0][1] = b;
		}
	}

	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 2; j++){
			printf("%d ", grid[i][j]);
		}
		printf("\n");
	}
}