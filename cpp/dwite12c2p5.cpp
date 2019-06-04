//============================================================================
// Name        : dwite12c2p5.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Scan and Debug
void scan(){}
template<typename F, typename... R> void scan(F &f,R&... r){cin>>f;scan(r...);}
int di_; string dnms_, co_ = ",";
void debug_(){cout<<endl;}
template<typename F, typename... R> void debug_(F f, R... r){while(dnms_[di_] != ',')cout<<dnms_[di_++];di_++;cout<<": "<<f<<",";debug_(r...);}
#define debug(...) dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__)

const int MAX = 1001;
int n, m,
	dp[MAX], high[MAX];

void solve() {
	for (int i = 0; i < n; ++i) {
		int cMax = high[i + 1];
		queue<int> maxIdxs; maxIdxs.push(i + 1);
		dp[i + 1] = min(dp[i + 1], dp[i] + 1);

		for (int j = i + 2; j <= n; j++) {
			if (high[j] > cMax) {
				cMax = high[j];
				while (!maxIdxs.empty())
					maxIdxs.pop();
				maxIdxs.push(j);
			}
			else if (high[j] == cMax)
				maxIdxs.push(j);

//			debug(i, j, cMax, high[j], maxIdxs.front(), maxIdxs.size());

			while (!maxIdxs.empty() && maxIdxs.front() < j - m)
				maxIdxs.pop();

			if (maxIdxs.empty() || maxIdxs.front() > i + m + 1)
				break;

			dp[j] = min(dp[j], dp[i] + 1);
		}
	}

	cout << dp[n] << "\n";
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

#ifndef ONLINE_JUDGE
	int t = 2;
#else
	int t = 5;
#endif

	while(t--) {
		scan(n, m);

		for (int i = 1; i <= n; i++)
			scan(high[i]);

		memset(dp, 0x3f, sizeof dp); dp[0] = 0;
		solve();
	}

	return 0;
}