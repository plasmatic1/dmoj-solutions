//============================================================================
// Name        : WorldTradeFoundation.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 10;
int n, cnt = 0;
ll k, coins[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> k;

	for (int i = 0; i < n; ++i) {
		cin >> coins[i];
	}

	sort(coins, coins + n, greater<int>());

	for (int i = 0; i < n; ++i) {
		while(k >= coins[i]){
			k -= coins[i];
			cnt++;
		}
	}

	if(k > 0){
		printf("-1\n");
	}
	else{
		printf("%d\n", cnt);
	}
}
