//============================================================================
// Name        : nccc7s3.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> p;

const int MAX = 3001;
int n;
ll combs = 0,
	x[MAX], y[MAX];

ll gcd(ll a, ll b){
	return b ? gcd(b, a % b) : a;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 0; i < n; ++i)
		cin >> x[i] >> y[i];

	for (int i = 0; i < n; ++i) {
		map<p, int> slopes;

		for (int j = i + 1; j < n; ++j) {
			ll dx = x[j] - x[i], dy = y[j] - y[i], gcdv = gcd(dx, dy);
			dx /= gcdv;
			dy /= gcdv;

			slopes[make_pair(dx, dy)]++;
		}

		ll tot = 0;
		for(pair<p, int> pa : slopes){
//			printf("i=%d got pa (%lld,%lld) -> %d\n", i, pa.first.first, pa.first.second, pa.second);
			combs += pa.second * tot;
			tot += pa.second;
		}
	}

	printf("%lld\n", combs);
}
