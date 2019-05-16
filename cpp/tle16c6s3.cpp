//============================================================================
// Name        : tle16c6s3.cpp
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

struct sug {
	ll x, v;

	bool operator<(const sug &o) const {
		return x < o.x;
	}
};

const int MAX = 2001;
const ll INF = 0x3f3f3f3f3f3f3f3f;
int n, start = -1;
ll dp[MAX][MAX][2], pfx[MAX];
bool vis[MAX][MAX][2];
sug sugs[MAX];

ll rec(int l, int r, bool side) {
	if (l > r) return 0;
	if (l > start || r < start) return -INF;
	ll &ret = dp[l][r][side];
	if (vis[l][r][side]) return ret;

	vis[l][r][side] = true;
	if (side) // right, left
		ret = max(ret, max(rec(l, r - 1, 1) - (sugs[r].x - sugs[r - 1].x), rec(l, r - 1, 0) - (sugs[r].x - sugs[l].x)));
	else // left, right
		ret = max(ret, max(rec(l + 1, r, 0) - (sugs[l + 1].x - sugs[l].x), rec(l + 1, r, 1) - (sugs[r].x - sugs[l].x)));

	if (ret >= 0) {
		ret += side ? sugs[r].v : sugs[l].v;
		if (ret > INF)
			ret = INF;
		return ret;
	}
	return ret = -INF;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	scan(n);

	for (int i = 1; i <= n; i++)
		scan(sugs[i].x, sugs[i].v);
	sort(sugs + 1, sugs + n + 1);
	sugs[0] = {-INF, 0};
	sugs[n + 1] = {INF, 0};

	for (int i = 1; i <= n; i++)
		pfx[i] = pfx[i - 1] + sugs[i].v;

	for (int i = 1; i <= n; i++)
		if (sugs[i].x == 0)
			start = i;

	for (int i = 1; i <= n; i++)
		for (int j = i; j <= n; j++)
			dp[i][j][0] = dp[i][j][1] = -INF;

	ll best = -1;
	for (int i = 1; i <= n; i++)
		for (int j = i; j <= n; j++)
			if (i <= start && j >= start && max(rec(i, j, 0), rec(i, j, 1)) >= 0)
				best = max(best, pfx[j] - pfx[i - 1]);
	printf("%lld\n", best);

	return 0;
}