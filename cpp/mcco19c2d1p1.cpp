//============================================================================
// Name        : mcco19c2d1p1.cpp
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

const int MM = 200010, MN = MM << 1;
int n, m, k, comps,
	dsu[MN], ans[MN], qus[MN], edgeA[MM], edgeB[MM], pointCnt[MM];
vector<int> edgesFor[MN];

int rt(int x) { return x == dsu[x] ? x : dsu[x] = rt(dsu[x]); }
void merge(int x, int y) {
	int rx = rt(x), ry = rt(y);
	if (rx != ry) {
		comps--;
		dsu[ry] = rx;
	}
}
bool same(int x, int y) { return rt(x) == rt(y); }

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	scan(n, m);
	comps = n;

	for (int i = 0; i < m; ++i) {
		scan(edgeA[i], edgeB[i]);
		pointCnt[i] = 2;
		edgesFor[edgeA[i]].push_back(i);
		edgesFor[edgeB[i]].push_back(i);
	}

	iota(dsu, dsu + n, 0);

	scan(k);

	qus[0] = -1;
	for (int i = 1; i <= k; i++) {
		scan(qus[i]);
		for (int x : edgesFor[qus[i]])
			pointCnt[x]--;
	}
	reverse(qus, qus + k + 1);

	for (int i = 0; i < m; ++i)
		if (pointCnt[i] == 2)
			merge(edgeA[i], edgeB[i]);

	for (int i = 0; i <= k; i++) {
		ans[i] = comps - (k - i);

		if (qus[i] == -1)
			continue;
		for (int x : edgesFor[qus[i]]) {
			pointCnt[x]++;
			if (pointCnt[x] == 2)
				merge(edgeA[x], edgeB[x]);
		}
	}

	for (int i = k; i >= 0; i--)
		cout << ans[i] << "\n";

	return 0;
}