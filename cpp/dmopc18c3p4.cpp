//============================================================================
// Name        : dmopc18c3p4.cpp
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

struct p {
	int v, w;
};

const int MAX = 200001;
int n, k, ba, bb, bc,
	cnt[MAX], sz[MAX];
vector<p> matrix[MAX];
ll tot = 0;

int gsize(int cur, int par) {
	for (p adj : matrix[cur])
		if (adj.v ^ par)
			sz[cur] += gsize(adj.v, cur);
	return sz[cur];
}

int gcentroid(int cur, int par) {
	for (p adj : matrix[cur])
		if ((adj.v ^ par) && sz[adj.v] > (k >> 1))
			return gcentroid(adj.v, cur);
	return cur;
}

void dfs(int cur, int par, int dis) {
	tot += (ll)dis * cnt[cur];
	for (p adj : matrix[cur])
		if (adj.v ^ par)
			dfs(adj.v, cur, dis + adj.w);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	scan(k, n);

	for (int i = 0; i < k; i++) {
		scan(ba);
		cnt[ba]++;
		sz[ba]++;
	}

	for (int i = 1; i < n; i++) {
		scan(ba, bb, bc);
		matrix[ba].push_back({bb, bc});
		matrix[bb].push_back({ba, bc});
	}

	gsize(1, -1);
	dfs(gcentroid(1, -1), -1, 0);

	printf("%lld\n", tot);
}