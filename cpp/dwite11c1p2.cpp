//============================================================================
// Name        : dwite11c1p2.cpp
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

const int MAX = 51;
int n, best,
	arr[MAX];

void solve() {
	for (int i = 0; i <= 1000; i++) {
		int diff = 0;
		for (int j = 0; j < n; j++)
			diff += arr[j] - i;
		if (diff != 0)
			continue;

		int cur = 0;
		for (int j = 0; j < n; j++)
			cur += abs(arr[j] - i);
		best = min(best, cur);
	}

	assert((best & 1) == 0);
	printf("%d\n", best >> 1);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

#ifndef ONLINE_JUDGE
	int t = 1;
#else
	int t = 5;
#endif

	while(t--) {
		scan(n);
		for (int i = 0; i < n; i++)
			scan(arr[i]);
		best = 0x3f3f3f3f;

		solve();
	}

	return 0;
}