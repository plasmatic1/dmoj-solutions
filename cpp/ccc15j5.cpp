//============================================================================
// Name        : PiDay.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 251;
int m, l;
unordered_map<int, int> sols[MAX][MAX];

int solve(int prev, int n, int k){
	if(sols[n][k][prev]){
		return sols[n][k][prev];
	}

	if(n == k || k == 1){
		return sols[n][k][prev] = 1;
	}

	int mv = min(n - k + 1, prev), total = 0;

	for(int i = (n + (n % k)) / k; i <= mv; i++){
		total += solve(i, n - i, k - 1);
	}

	return sols[n][k][prev] = total;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> m >> l;

	printf("%d\n", solve(INT_MAX, m, l));
}
