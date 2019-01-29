//============================================================================
// Name        : Kratki.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

ll n, k, buf;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n >> k;

	if(k * k < n){
		printf("-1\n");
		return 0;
	}

	for(ll i = n - k + 1; i > 0; i -= k){
		for (ll j = 0; j < k; ++j) {
			printf("%lld ", i + j);
		}
	}

	ll leftv = n % k;
	for (ll i = 1; i <= leftv; ++i) {
		printf("%lld ", i);
	}

	printf("\n");
	return 0;
}
