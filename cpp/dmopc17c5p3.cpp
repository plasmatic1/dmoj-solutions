//============================================================================
// Name        : MimiAndPrimes.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 100000;
int n;
ll cgcd = 0, buf, nums[MAX];

ll gcd(ll a, ll b){
	if(b == 0){
		return a;
	}
	return gcd(b, a % b);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> buf;
		cgcd = gcd(cgcd, buf);
	}

	if(cgcd == 1){
		printf("DNE\n");
		return 0;
	}

	ll mv = (long long int)(sqrt((double)cgcd)) + 1, mprime = INT_MIN, old_cgcd = cgcd;

//	printf("cgcd=%lld, mv=%lld\n", cgcd, mv);

	bool pass = false;
	for (ll i = 2; i <= mv && i <= cgcd; ++i) {
		while(cgcd % i == 0){
			pass = true;
			cgcd /= i;
		}

		if(pass){
			mprime = i;
		}
	}

	if(mprime == INT_MIN){
		printf("%lld\n", old_cgcd);
		return 0;
	}

	printf("%lld\n", mprime);
}
