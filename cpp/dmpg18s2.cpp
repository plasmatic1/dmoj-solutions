//============================================================================
// Name        : dmpg18s2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 200001;
int n;
ll pfx[MAX], arr[MAX];
vector<ll> sto;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n;

	for(int i = 1; i <= n; i++)
		cin >> arr[i], pfx[i] = arr[i] + pfx[i - 1];

	int half = (n >> 1) + (n % 2);
	ll cur = 0;

	for (int i = 0; i < half; ++i) {
		ll ans = (i + 1) * (pfx[n - i] - pfx[i]) + cur;

		printf("%lld\n", ans);
		sto.push_back(ans);
		cur += (i + 1) * (arr[i + 1] + arr[n - i]);
	}

	reverse(sto.begin(), sto.end());
	for(int i = n, j = n % 2; i > half; i--, j++)
		printf("%lld\n", sto[j]);
}
