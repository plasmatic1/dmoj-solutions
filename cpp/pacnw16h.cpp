//============================================================================
// Name        : Paint.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

struct sa{
	ll l, r;

	friend bool operator<(const sa &f, const sa &s){
		return f.r < s.r;
	}
};

const int MAX = 200001;

ll n, ba, bb,
	dp[MAX];
int k;
sa sections[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> k;

	for (int i = 1; i <= k; ++i) {
		cin >> ba >> bb;

		sections[i] = {ba, bb};
	}

	sort(sections, sections + k + 1);

	// DP

	for (int i = 1; i <= k; ++i) {
		sa sfor = {-1, sections[i].l};
		auto ptr = upper_bound(sections, sections + k + 1, sfor);

//		printf("i=%d, l=%lld, r=%lld\n", i, sections[i].l, sections[i].r);
//		printf("found index=%d\n", ptr - sections - 1);

		dp[i] = max(dp[i - 1], dp[ptr - sections - 1] + sections[i].r - sections[i].l + 1);
	}

	// Output

	printf("%lld\n", n - dp[k]);
}
