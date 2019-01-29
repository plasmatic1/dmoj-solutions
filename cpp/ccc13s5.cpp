//============================================================================
// Name        : FactorSolitaireRecode.cpp
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

int small_factor(int x){
	int nsq = sqrt(x) + 1, lf = INT_MAX;

	if(x % 2 == 0){
		lf = 2;
		x /= x & -x;
	}

	for(int i = 3; i <= nsq && x > 1; i += 2){
		while(x % i == 0){
			x /= i;
			lf = min(lf, i);
		}
	}

	return lf == INT_MAX ? x : lf;
}

int runseq(int x){
	int total = 0;

	while(x > 1){
		int fact = x / small_factor(x);
		x -= fact;
		total += x / fact;
	}

	return total;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	printf("%d\n", runseq(n));
}
