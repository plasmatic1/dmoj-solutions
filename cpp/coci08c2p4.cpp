//============================================================================
// Name        : coci08c2p4.cpp
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

const int MT = 1000000001, MN = 101;
int t, n, m,
	a[MN], b[MN], c[MN], d[MN];

ll cnt(int time, int a[MN], int b[MN], int n) { // how many coconut can be collec
	ll tot = 0;
	for (int i = 0; i < n; i++)
		if (time >= a[i])
			tot += (time - a[i]) / b[i] + 1;
	return tot;
}

inline bool sim(int timeForFirst) { // true if the second monkey type have enough time to collec the KOKOnut
	ll fst = cnt(timeForFirst, a, b, n);
	return cnt(t - timeForFirst, c, d, m) >= fst;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	scan(t, n);

	for (int i = 0; i < n; i++)
		scan(a[i], b[i]);

	scan(m);

	for (int i = 0; i < m; i++)
		scan(c[i], d[i]);

	int l = -1, r = t + 1;
	while (l + 1 < r) {
		int mid = (l + r) >> 1;

		if (sim(mid))
			l = mid;
		else
			r = mid;
	}

//	debug(l, r);
	printf("%d\n", l);

	return 0;
}
