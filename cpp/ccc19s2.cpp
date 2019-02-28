//============================================================================
// Name        : ccc19s2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 2000001;
int t, n, buf;
vector<int> primes;
bool isprime[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	memset(isprime, true, sizeof isprime);
	isprime[0] = isprime[1] = false;

	for (int i = 2; i < MAX; ++i) {
		if(isprime[i]){
			for(int j = i << 1; j < MAX; j += i)
				isprime[j] = false;
			primes.push_back(i);
		}
	}

	cin >> t;

	while(t--){
		cin >> n;
		n <<= 1;

		int a, b;

		for(int pr : primes){
			if(isprime[n - pr]){
				a = pr;
				b = n - pr;
				break;
			}
		}

		printf("%d %d\n", a, b);
	}
}