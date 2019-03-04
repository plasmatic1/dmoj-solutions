//============================================================================
// Name        : coci15c4p3.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 1000000;
int n, buf;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n;

	for (int i = 0; i < n; ++i) {
		int cur = 0;
		for (int j = 0; j < n; ++j) {
			cin >> buf;
			cur |= buf;
		}
		printf("%d ", cur);
	}
	printf("\n");
}