//============================================================================
// Name        : dwite10c5p2.cpp
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

const int MAX = 21;
int r, c, n,
	x[MAX], y[MAX];

void solve() {
	int tot = r * c;
	for (int i = 1; i <= r; i++) {
		bool all = false;
		for (int j = 0; j < n; j++)
			all |= x[j] == i;
		if (all)
			tot -= c;
		else {
			set<int> dist;
			for (int j = 0; j < n; j++)
				dist.insert(y[j]);
			tot -= dist.size();
		}
	}

	printf("%d\n", tot);
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
		scan(r, c, n);
		for (int i = 0; i < n; i++)
			scan(x[i], y[i]);

		solve();
	}

	return 0;
}