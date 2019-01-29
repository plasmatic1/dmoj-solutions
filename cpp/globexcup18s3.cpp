//============================================================================
// Name        : PlayingWithBits.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ll;
typedef pair<int, int> p;

ll k, v, m, n, rbcount;

ll fastpow(ll x, ll y){
    x%=m;
	ll curr = 1, curr_pow = x, curr_mask = 1;

	while(curr_mask <= y){
		if(y & curr_mask){
			curr = (curr * curr_pow) % m;
		}

		curr_pow = (curr_pow * curr_pow) % m;
		curr_mask <<= 1;
	}

	return curr;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m >> k >> v;

	// XOR

	// V itself is irrelavent
	printf("%lld\n", fastpow(2, (n - 1) * k) % m);

	// OR

	rbcount = __builtin_popcountll(v);
	printf("%lld\n", fastpow(fastpow(2, n) - 1, rbcount) % m);

	// AND

	rbcount = k - __builtin_popcountll(v);
	printf("%lld\n", fastpow(fastpow(2, n) - 1, rbcount) % m);
}
