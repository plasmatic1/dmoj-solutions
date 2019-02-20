//============================================================================
// Name        : valentines19s3.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 100001, MM = 9;
int n, m, ming = INT_MAX,
	groups[MM];
ll pages[MAX];

inline ll ceildiv(ll a, ll b){
	if(a % b) return a / b + 1;
	return a / b;
}

bool simPermutation(ll k){
	ll passed = 0;

	for (int i = 0; i < m; ++i) {
		ll limit = passed + groups[i] * k;
		int idx = upper_bound(pages, pages + n, limit) - pages;

		if(idx >= n) return true;

		passed = pages[idx - 1];
	}

	return false;
}

bool sim(ll k){
	sort(groups, groups + m);
	do{
		if(simPermutation(k))
			return true;
	}
	while(next_permutation(groups, groups + m));

	return false;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> m;

	for(int i = 0; i < n; i++)
		cin >> pages[i];

	for(int i = 1; i < n; i++)
		pages[i] += pages[i - 1];

	for(int i = 0; i < m; i++){
		cin >> groups[i];
		ming = min(ming, groups[i]);
	}

	ll l = 0, r = ceildiv(pages[n - 1], ming);
	while(l + 1 < r){
		ll mid = (l + r) >> 1;

		if(sim(mid))
			r = mid;
		else
			l = mid;
	}

	printf("%lld\n", r);
}
