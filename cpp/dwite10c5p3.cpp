//============================================================================
// Name        : BalancingAct.cpp
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

int solve(int* subs, int* arr, int l, int r){
	int sz = r - l, msub = 1 << sz;

//	printf("from l=%d to r=%d subcount =%d\n", l, r, msub);

	for (int i = 0; i < msub; ++i) {
		int sum = 0, sumnot = 0;

		for (int j = sz - 1; j >= 0; --j) {
			if(i & (1 << j)){
				sum += arr[l + j];
			}
			else{
				sumnot += arr[l + j];
			}
		}

		subs[i] = sum - sumnot;;
	}

	return msub;
}

const int PM = 32900;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	for (int aisufjadsiufhsif = 0; aisufjadsiufhsif < 5; ++aisufjadsiufhsif) {
		cin >> n;
		int weight[n];

		for (int i = 0; i < n; ++i) {
			cin >> weight[i];
		}

		int half = n / 2;
		int sub1[PM], sub2[PM];

		int sz1 = solve(sub1, weight, 0, half), sz2 = solve(sub2, weight, half, n), mindiff = INT_MAX;
		sort(sub2, sub2 + sz2);

		for (int i = 0; i < sz1; ++i) {
			int lookfor = -sub1[i], cv = sub1[i];

			auto lptr = lower_bound(sub2, sub2 + sz2, lookfor), rptr = upper_bound(sub2, sub2 + sz2, lookfor);
//			printf("i=%d for val=%d lf=%d rf=%d\n", i, cv, *lptr, *rptr);

			mindiff = min(mindiff, abs(min(cv + *lptr, cv + *rptr)));
		}

		printf("%d\n", mindiff);
	}
}
