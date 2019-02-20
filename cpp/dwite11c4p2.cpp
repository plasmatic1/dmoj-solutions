//============================================================================
// Name        : dwite11c4p2.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

int n, buf;

void pfactor(int n, int factors[]){
	int sqn = sqrt(n);
	for(int i = 2; i <= sqn; i++){
		while(n % i == 0){
			n /= i;
			factors[i]++;
		}
	}

	if(n > 1)
		factors[n]++;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	for (int ashdfiuashi = 0; ashdfiuashi < 5; ++ashdfiuashi) {
		cin >> n;

		vector<p> pfacts;
		int factors[n + 1];
		memset(factors, 0, sizeof factors);

		for(int i = 2; i <= n; i++)
			pfactor(i, factors);

		for(int i = 2; i <= n; i++)
			if(factors[i])
				pfacts.push_back(make_pair(i, factors[i]));

		int last = pfacts.size() - 1;
		for(int i = 0; i < last; i++)
			printf("%d^%d * ", pfacts[i].first, pfacts[i].second);
		printf("%d^%d\n", pfacts[last].first, pfacts[last].second);
	}
}
