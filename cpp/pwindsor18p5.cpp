//============================================================================
// Name        : MathDepression.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

int n;
ll ans = 1;
const ll MOD = 1000000007;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	int v = (int)sqrt(n), amt = n / v;

	for (int i = 0; i < amt; ++i) {
		ans = (ans * v) % MOD;
	}

	int extra = n - (v * amt);
	if(extra == 1){
		ans /= v;
		ans *= (v + extra);
	}
	else if(extra > 1){
		ans *= extra;
	}

	printf("%lld\n", ans % MOD);
}
