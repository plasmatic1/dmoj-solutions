//============================================================================
// Name        : ncp4.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 100001;
int n, m, pfx[MAX], bp, bt;
string tmp;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	for (int i = 1; i <= n; ++i) {
		cin >> pfx[i];
		pfx[i] += pfx[i - 1];
	}

	for (int i = 0; i < m; ++i) {
		cin >> tmp >> bp >> bt;

		printf("%d\n", pfx[bp + bt - 1] - pfx[bp - 1]);
	}
}
