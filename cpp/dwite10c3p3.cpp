//============================================================================
// Name        : dwite10c3p3.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
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

const int MAX = 35, M = 3, MSUB = 1 << M, MOD = 1000000;
int n,
	dp[MAX][MSUB];

#define isSet(x, bit) (((x) >> (bit)) & 1)
#define flipBit(x, bit) ((x) ^ (1 << (bit)))

int rec(int cur, int mask) {
	if (cur < 1) return 0;
	if (cur == 1 && mask == 0) return 1;
	int &val = dp[cur][mask];
	if (val != -1) return val;
	val = 0;

	if (mask == 0)
		return val = rec(cur - 1, 7);

	// horizontal domino
	val = (val + rec(cur - 1, ~mask & 7)) % MOD;

	// vertical domino
	for (int i = 1; i < M; i++)
		if (isSet(mask, i) && isSet(mask, i - 1))
			val = (val + rec(cur, flipBit(flipBit(mask, i), i - 1))) % MOD;

	return val;
}

inline void solve() {
	scan(n);

	memset(dp, -1, sizeof dp);
	printf("%d\n", rec(n, 7));
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int ctr = 5;
	while (ctr--)
		solve();
}