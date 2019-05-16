//============================================================================
// Name        : si17c3p5.cpp
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

struct ed {
	int v, w;
};

const int MAX = 100001, MV = 200001;
int n, ba, bb,
	cnt[MV + 5], sz[MAX];
char bt;
bool blocked[MAX];
vector<ed> matrix[MAX];
vector<int> back;
ll tot = 0;

#define CNT(x) cnt[(x) + MAX]

int gsz(int cur, int par) {
	sz[cur] = 1;
	for (ed adj : matrix[cur])
		if ((adj.v ^ par) && !blocked[adj.v])
			sz[cur] += gsz(adj.v, cur);
	return sz[cur];
}

int gcentroid(int cur, int par, int half) {
	for (ed adj : matrix[cur])
		if ((adj.v ^ par) && !blocked[adj.v] && sz[adj.v] > half)
			return gcentroid(adj.v, cur, half);
	return cur;
}

void dfs(int cur, int par, int dis, bool add) {
	if (add) {
		CNT(dis)++;
		back.push_back(dis);
	}
	else
		tot += CNT(-dis + 1) + CNT(-dis - 1);

	for (ed adj : matrix[cur])
		if ((adj.v ^ par) && !blocked[adj.v])
			dfs(adj.v, cur, dis + adj.w, add);
}

void decomp(int cur, int par=-1) {
	gsz(cur, par);
	if (sz[cur] == 1)
		return;

	CNT(0) = 1;
	int centroid = gcentroid(cur, par, sz[cur] >> 1);
	for (ed adj : matrix[centroid]) {
		if ((adj.v ^ par) && !blocked[adj.v]) {
			dfs(adj.v, centroid, adj.w, false);
			dfs(adj.v, centroid, adj.w, true);
		}
	}

	for (int x : back)
		CNT(x) = 0;
	back.clear();

	blocked[centroid] = true;
	for (ed adj : matrix[centroid])
		if (!blocked[adj.v])
			decomp(adj.v, centroid);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	scan(n);

	for (int i = 1; i < n; i++) {
		scan(ba, bb, bt);
		int wt = bt == 'r' ? 1 : -1;
		matrix[ba].push_back({bb, wt});
		matrix[bb].push_back({ba, wt});
	}

	decomp(1);
	printf("%lld\n", tot - (n - 1)); // remove 2-length cycles

	return 0;
}