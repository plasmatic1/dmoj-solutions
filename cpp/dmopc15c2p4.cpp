//============================================================================
// Name        : dmopc15c2p4.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct p{
	ll l, r, h;

	bool operator<(const p &o) const {
		return r < o.r;
	}
};

const int MAX = 100001;

ll ba, bb, bc,
	dp[MAX];
int n;
p anime[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> ba >> bb >> bc;
		anime[i] = {ba, ba + bb - 1, bc};
	}

	sort(anime, anime + n);

	dp[0] = anime[0].h;
	for(int i = 1; i < n; i++){
		p tmp = {-1, anime[i].l, -1};
		int idx = lower_bound(anime, anime + n, tmp) - anime - 1;

		dp[i] = dp[i - 1];
		if(idx < 0)
			dp[i] = max(dp[i], anime[i].h);
		else if(idx < i)
			dp[i] = max(dp[i], dp[idx] + anime[i].h);
	}

	printf("%lld\n", dp[n - 1]);
}