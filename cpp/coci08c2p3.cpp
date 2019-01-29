//============================================================================
// Name        : Perket.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct ing{
	int s, b;
};

const int MAX = 11;
int n, sb, bb, minv = INT_MAX;
ing ings[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> sb >> bb;

		ings[i] = {sb, bb};
	}

	int maxsub = 1 << n;
	for (int i = 1; i < maxsub; ++i) {
		int prod = 1, sum = 0;
//		printf(" -- i=%d\n", i);

		for (int j = n - 1; j >= 0; j -= 1) {
			if(i & (1 << j)){
//				printf("including ing=%d\n", j);
				prod *= ings[j].s;
				sum += ings[j].b;
			}
		}

		minv = min(minv, abs(prod - sum));
	}

	printf("%d\n", minv);
}
