//============================================================================
// Name        : dmopc18c5p1.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

int n, m, k, blue = 0, purple = 0;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m >> k;

	for (int i = 0; i < k; ++i) {
		bool isn = (n >> i) & 1, ism = (m >> i) & 1;

		if(isn && ism)
			purple++;
		else if(isn || ism)
			blue++;
		else
			purple++;
	}

	printf("%d %d\n", blue, purple);
}
