//============================================================================
// Name        : DamageOutput.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 500000;
int n;
ll m,
	arr[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	for (int i = 0; i < n; ++i) {
		cin >> arr[i];
	}

	for (int i = 1; i < n; ++i) {
		arr[i] += arr[i - 1];
	}

	int l = 0, r = 0, minl = INT_MAX;
	for (; r < n; ) {
		ll s = l > 0 ? arr[r] - arr[l - 1] : arr[r];
//		printf("l=%d, r=%d, sum=%lld\n", l, r, s);

		if(s >= m){
			minl = min(minl, r - l + 1);
			l++;
		}
		else{
			r++;
		}
	}

	printf("%d\n", minl == INT_MAX ? -1 : minl);
}
