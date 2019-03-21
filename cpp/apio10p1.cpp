//============================================================================
// Name        : apio10p1.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct p{
	int i, dpi;
};

const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MAX = 1000001;
int n, a, b, c,
	bestDP[MAX];
ll dp[MAX], pfx[MAX];
deque<p> bestDPDeq;

// Let x be the old value from i + 1 to j
// f(i, j) = dp[i] + ax^2 + bx + c
inline ll dpFrom(int from, int to){
	ll sum = pfx[to] - pfx[from];
	return dp[from] + a * sum * sum + b * sum + c;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> a >> b >> c;

	for (int i = 1; i <= n; i++)
		cin >> pfx[i], pfx[i] += pfx[i - 1];

	int currBest = 0;
	bestDPDeq.push_back({0, 0});

	for (int i = 1; i <= n; i++){
		if(bestDP[i])
			currBest = bestDP[i];
		dp[i] = dpFrom(currBest, i);

		p top = bestDPDeq.back();
		while(top.i > i && dpFrom(i, top.i) > dpFrom(top.dpi, top.i)){
			bestDP[top.i] = 0;
			bestDPDeq.pop_back();
			top = bestDPDeq.back();
		}

		int l = i, r = n;
		while(l + 1 < r){
			int mid = (l + r) >> 1;

			if(dpFrom(i, mid) >= dpFrom(top.dpi, mid))
				r = mid;
			else
				l = mid;
		}

		if(dpFrom(i, r) >= dpFrom(top.dpi, r)){
			bestDP[r] = i;
			bestDPDeq.push_back({r, i});
		}
	}

	printf("%lld\n", dp[n]);
}
