//============================================================================
// Name        : InahoXI.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const ll MOD = 1000000007;
const int MAXD = 10;
int n, m, buf,
	mins[MAXD], maxs[MAXD], lens[MAXD];
ll tot = 0;

inline int fact(int n){
	int ans = 1;
	while(n > 0){
		ans *= n--;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	fill(mins, mins + n, INT_MAX);
	fill(maxs, maxs + n, INT_MIN);

	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> buf;

			mins[j] = min(mins[j], buf);
			maxs[j] = max(maxs[j], buf);
		}
	}

	for (int i = 0; i < n; ++i) {
		lens[i] = maxs[i] - mins[i];
	}

	for (int i = 0; i < n; ++i) { // Cut out one of each element
		ll sz = 1;

		for (int j = 0; j < n; ++j) {
			if(i == j) continue;
			sz *= lens[j];
			sz %= MOD;
		}

		tot += sz;
		tot %= MOD;
	}

	printf("%lld\n", (tot * 2) % MOD);
}
