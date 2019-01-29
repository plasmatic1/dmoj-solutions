//============================================================================
// Name        : BigChess.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 1000000;
int n, m;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> m;

	for (int i = 0; i < m; ++i) {
		bool dig = i % 2;

		for (int j = 0; j < n; ++j) {
			printf("%d", dig);
			dig = !dig;
		}
		printf("\n");
	}
}
