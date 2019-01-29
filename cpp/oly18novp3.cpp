//============================================================================
// Name        : SplttingASequence.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 100001;
int n, m,
	arr[MAX];

int sim(ll maxsum){
	ll currsum = 0;
	int cnt = 1;

//	printf("maxsum=%lld\n", maxsum);

	for (int i = 0; i < n; ++i) {
		if(currsum + arr[i] > maxsum){
//			printf("i=%d goes over sum, currsum=%d\n", i, arr[i]);
			currsum = arr[i];
			cnt++;
		}
		else{
//			printf("i=%d not over, cs now=%lld\n", i, currsum);
			currsum += arr[i];
		}
	}

	return cnt;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	ll maxe = -1;
	for (int i = 0; i < n; ++i) {
		cin >> arr[i];
		maxe = max(maxe, (ll)arr[i]);
	}

	// Solving

	ll l = 0, r = 100000000000000; // r is max possible sum

	while(l + 1 < r){
		int mid = (l + r) / 2;

//		printf("l=%lld r=%lld\n", l, r);

		if(sim(mid) <= m){
			r = mid;
		}
		else{
			l = mid;
		}
	}

	printf("%lld\n", max(r, maxe));
}
