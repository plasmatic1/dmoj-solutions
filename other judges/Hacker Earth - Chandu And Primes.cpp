//============================================================================
// Name        : ChanduAndPrimes.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 1000001;
int q, bl, br,
	flag[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	// Sieve

	fill(flag + 2, flag + MAX, 1);

	for (int i = 2; i < MAX; ++i) {
		if(!flag[i]){
			continue;
		}

		for (int j = i << 1; j < MAX; j += i) {
			flag[j] = 0;
		}
	}

	// Setup alpha prime stuff

	for (int i = 12; i < MAX; ++i) {
		if(!flag[i]){
			int mag = 10;

			while(mag < i){
				if(flag[i % mag]){
					flag[i] = 1;
					break;
				}

				mag *= 10;
			}
		}
	}

	// Prefix

	for (int i = 1; i <= MAX; ++i) {
		flag[i] += flag[i - 1];
	}

	cin >> q;

	for (int i = 0; i < q; ++i) {
		cin >> bl >> br;

		printf("%d\n", flag[br] - flag[bl - 1]);
	}
}
