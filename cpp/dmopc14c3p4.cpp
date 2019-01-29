//============================================================================
// Name        : NotEnoughTesting.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 100001, MAXK = 201;
int t, a, b, k,
	pfx[MAXK][MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	for(int i = 1; i < MAX; i++){
		int facts = 1, sqi = sqrt(i), cur = i;

		for(int j = 2; j <= sqi; j++){
			int cnt = 1;

			while(cur % j == 0){
				cur /= j;
				cnt++;
			}

			facts *= cnt;
		}

		if(cur > 1){
			facts <<= 1;
		}

		pfx[facts][i] = 1;
	}

	for (int i = 0; i < MAXK; ++i) {
		for (int j = 1; j < MAX; ++j) {
			pfx[i][j] += pfx[i][j - 1];
		}
	}

	cin >> t;

	while(t--){
		cin >> k >> a >> b;

		if(k >= MAXK) printf("0\n");
		else printf("%d\n", pfx[k][b] - pfx[k][a - 1]);
	}
}
