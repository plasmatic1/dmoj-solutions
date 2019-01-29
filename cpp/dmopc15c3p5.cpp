//============================================================================
// Name        : TotalAnnihilation.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 40, PART_SUBSZ = 1 << 19;
int n, m, buf, mat[MAX], half;

ll sub1[PART_SUBSZ], sub2[PART_SUBSZ];

int solve(ll* subs, int* arr, int l, int r){
	int sz = r - l, msub = 1 << sz;

//	printf("from l=%d to r=%d subcount =%d\n", l, r, msub);

	for (int i = 1; i < msub; ++i) {
		ll sum = 0;

		for (int j = sz - 1; j >= 0; --j) {
			if(i & (1 << j)){
				sum += arr[l + j];
			}
		}

		subs[i] = sum;
	}

	return msub;
}

ll ways = 0;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	for (int i = 0; i < n; ++i) {
		cin >> mat[i];
	}

	int ttl = n + m;
	for (int i = n; i < ttl; ++i) {
		cin >> buf;
		mat[i] = -buf;
	}

	half = ttl / 2;

	int sz1 = solve(sub1, mat, 0, half), sz2 = solve(sub2, mat, half, ttl);

	sort(sub2, sub2 + sz2);

	for (int i = 0; i < sz1; ++i) {
		ll lookfor = -sub1[i];
//		printf("i=%d, lf=%d\n", i, lookfor);

		auto lptr = lower_bound(sub2, sub2 + sz2, lookfor), rptr = upper_bound(sub2, sub2 + sz2, lookfor);

		if(lptr != rptr){
//			printf("got sz of %d for i=%d\n", rptr - lptr + 1, i);
			ways += rptr - lptr;

			if(i == 0){
				ways--;
			}
		}
	}

	printf("%lld\n", ways);
}
