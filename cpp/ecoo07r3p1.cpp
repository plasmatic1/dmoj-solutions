//============================================================================
// Name        : SumOfPrimes.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MV = 10000001;
int n;
bool isprime[MV];
vector<int> primes;

inline void run(int &a, int &b, int target){
	int ind = upper_bound(primes.begin(), primes.end(), target / 2) - primes.begin() - 1;

	for(int i = ind; i >= 0; i--){
		int alt = target - primes[i];
		if(isprime[alt]){
			a = primes[i];
			b = alt;
			break;
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	// Prime Sieve

	memset(isprime, true, sizeof(isprime));
	isprime[0] = false;
	isprime[1] = false;
	for (int i = 2; i < MV; ++i) {
		if(isprime[i]){
			primes.push_back(i);

			for (int j = i << 1; j < MV; j += i) {
				isprime[j] = false;
			}
		}
	}

	// Cases

	for (int abcabcabcabc = 0; abcabcabcabc < 5; ++abcabcabcabc) {
		cin >> n;

		if(n % 2){
			if(isprime[n]){
				printf("%d = %d\n", n, n);
			}
			else{
				int ci = upper_bound(primes.begin(), primes.end(), n / 3) - primes.begin() - 1, aux = 0, c = 1, a = 0, b = 0;

				while(c > a){
					c = primes[ci];
					aux = n - c;
					run(a, b, aux);
					ci--;
				}

				printf("%d = %d + %d + %d\n", n, c, a, b);
			}
		}
		else{
			int a, b;
			run(a, b, n);
			printf("%d = %d + %d\n", n, a, b);
		}
	}
}
