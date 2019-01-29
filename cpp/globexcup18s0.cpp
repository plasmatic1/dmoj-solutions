//============================================================================
// Name        : ChairStacking.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 100001;
int n,
	lhs[MAX], rhs[MAX];

ll run(int* chairs){
	ll total = 0;
	int best = 0;

	for (int i = 1; i < n; ++i) {
		total += chairs[i] - chairs[best];

		ll delta = chairs[best + 1] - chairs[best],
				shiftedtotal = total + (best + 1) * delta - (i - best) * delta;

		if(shiftedtotal <= total){
			total = shiftedtotal;
			best++;
		}
	}

	return total;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> lhs[i] >> rhs[i];
	}

	sort(lhs, lhs + n);
	sort(rhs, rhs + n);

	printf("%lld\n", run(lhs) + run(rhs));
}
