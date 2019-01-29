//============================================================================
// Name        : PrefixSumArray(TLE).cpp
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
const ll MOD = 1000000007;
int n, k;
ll farr[MAX], coeffs[MAX], arr[MAX];

ll fastpow(ll x, ll y){
	ll curr = 1, curr_pow = x, curr_mask = 1;

	while(curr_mask <= y){
		if(y & curr_mask){
			curr = (curr * curr_pow) % MOD;
		}

		curr_pow = (curr_pow * curr_pow) % MOD;
		curr_mask <<= 1;
	}

	return curr;
}

#define INVERSE(x) (fastpow((x), (MOD - 2)))

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 1; i <= n; ++i) {
		cin >> arr[i];
	}

	cin >> k;

	ll cn = 1, offset = k - 1;
	for (int i = 1; i <= n; ++i) {
		coeffs[i] = cn;

		cn = (cn * (i + offset)) % MOD;
		cn = (cn * INVERSE(i)) % MOD;
//		cn %= MOD;
	}

//	printf("coeffs: ");
//	for (int i = 0; i < n + 1; ++i) {
//		printf("%lld, ", coeffs[i]);
//	}
//	printf("\n");

	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < i; ++j) {
			farr[i] += (arr[i - j] * coeffs[j + 1]) % MOD;
		}
	}

	// Output

	for (int i = 1; i <= n; ++i) {
		printf("%lld ", farr[i] % MOD);
	}
	printf("\n");
}
