//============================================================================
// Name        : PolynomialTimeBooleanSatisfiability.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 50, MSUB = 1 << 25;
int n, k,
	pfx[MAX], sub1[MSUB], sub2[MSUB];
ll ways = 0;

int solve(int subs[MSUB], int l, int r){
	int sz = r - l, msub = 1 << sz;
	for (int i = 0; i < msub; ++i) {
		int sum = 0;
		for (int j = sz - 1; j >= 0; --j) {
			if(i & (1 << j)){
				sum += pfx[l + j];
			}
		}
		subs[i] = sum;
	}

	return msub;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> k;

	for (int i = 0; i < n; ++i) {
		cin >> pfx[i];
	}

	int half = n / 2, sz1 = solve(sub1, 0, half), sz2 = solve(sub2, half, n), ptr2 = sz2 - 1;
	sort(sub1, sub1 + sz1); sort(sub2, sub2 + sz2);

	for (int i = 0; i < sz1; ++i) {
		while(ptr2 >= 0 && sub1[i] + sub2[ptr2] > k)
			ptr2--;
		ways += ptr2 + 1;
	}

	printf("%lld\n", ways);
}
