//============================================================================ //Literally just firehoses
// Name        : LargestMinimumDistance.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 100001, MAXD = 1000000000;
int n, m, dists[MAX];

int test(int length){
	int cnt = 1, curr = dists[0];

	for (int i = 0; i < n; ++i) {
		if(dists[i] >= curr + length){
			curr = dists[i];
			cnt++;
		}
	}

	return cnt;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	for (int i = 0; i < n; ++i) {
		cin >> dists[i];
	}

	sort(dists, dists + n);

	int l = 0, r = MAXD;

//	int dc = 20;

	while(l + 1 < r){
		int mid = (l + r) / 2;

//		printf("l=%d, r=%d, foudn val=%d\n", l, r, test(mid));

		if(test(mid) < m){
			r = mid;
		}
		else{
			l = mid;
		}

//		assert(dc--);
	}

	printf("%d\n", l);
}
