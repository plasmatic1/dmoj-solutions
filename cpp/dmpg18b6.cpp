//============================================================================
// Name        : HouseOfCards.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 2001;
int n, k,
	size[MAX], dp[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> k;

	for (int i = 0; i < n; ++i) {
		cin >> size[i];
	}

	sort(size, size + n, greater<int>());

	dp[0] = 1;
	for (int i = 1; i < n; ++i) {
		for(int j = 0; j < i; ++j){
			if(size[i] + k <= size[j]){
				dp[i] = max(dp[i], dp[j] + 1);
			}
			else{
				dp[i] = max(dp[i], dp[j]);
			}
		}
	}

	printf("%d\n", dp[n - 1]);
}
