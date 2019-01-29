//============================================================================
// Name        : SharingCrayons.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int b, c; ll n[100001];
ll sum = 0;
map<ll, ll> mapp;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> b >> c;
	mapp[0]=1;
	for(int i = 1; i <= b; i++){
		cin >> n[i];
		n[i] = (n[i] + n[i - 1]) % c;
		sum += mapp[n[i]];
		mapp[n[i]]++;
	}

	printf("%lld\n", sum);

	return 0;
}
