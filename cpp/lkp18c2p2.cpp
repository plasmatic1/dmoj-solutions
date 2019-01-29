//============================================================================
// Name        : SecretSignal.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 200001;
int n, k, buf,
	freq[MAX];
ll tot = 0,
	arr[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> k;

	for (int i = 1; i <= n; ++i) {
		cin >> arr[i];
		arr[i] += arr[i - 1];
	}

	for (int i = 1; i <= n; i++){
		arr[i] %= (ll)k;
	}

	for (int i = 0; i <= n; ++i) {
		freq[arr[i]]++;
	}

	for (int i = 0; i < n; ++i) {
		freq[arr[i]]--;
		ll lookfor = arr[i];
		tot += freq[lookfor];
	}

	printf("%lld\n", tot);
}
