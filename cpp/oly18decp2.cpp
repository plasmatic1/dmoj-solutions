//============================================================================
// Name        : RotateMatrix.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 21;
int n, m,
	matrix[MAX][MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cin >> matrix[i][j];
		}
	}

	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			printf("%d ", matrix[j][m - i - 1]);
		}
		printf("\n");
	}
}
