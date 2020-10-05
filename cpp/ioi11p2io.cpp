//============================================================================
// Name        : ioi11p2.cpp
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

const int MAX = 200001, MK = 1000001;
int n, k, best = 0x3f3f3f3f,
	sz[MAX], bestFor[MK];
vector<ed> matrix[MAX];
bool blocked[MAX];
vector<pair<int, int>> back;

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

void dfs(int cur, int par, int dis, int lv) {
	if (dis <= k)
		best = min(best, lv + bestFor[k - dis]);
	for (ed adj : matrix[cur])
		if ((adj.v ^ par) && !blocked[adj.v])
			dfs(adj.v, cur, dis + adj.w, lv + 1);
}

void add(int cur, int par, int dis, int lv) {
	if (dis <= k) {
		back.push_back(make_pair(dis, bestFor[dis]));
		bestFor[dis] = min(bestFor[dis], lv);
	}
	for (ed adj : matrix[cur])
		if ((adj.v ^ par) && !blocked[adj.v])
			add(adj.v, cur, dis + adj.w, lv + 1);
}

void decomp(int cur, int par=-1) {
	gsz(cur, par);
	if (sz[cur] == 1)
		return;

	int centroid = gcentroid(cur, par, sz[cur] >> 1); //debug(cur, par, centroid);

//	setbuf(stdout, 0);
//	printf("cur=%d par=%d cent=%d sz=%d\n", cur, par, centroid, sz[cur]);

	for (ed adj : matrix[centroid]) {
		if (adj.v ^ par) {
			dfs(adj.v, centroid, adj.w, 1);
			add(adj.v, centroid, adj.w, 1);
		}
	}

	for (auto it = back.rbegin(); it != back.rend(); it++)
		bestFor[it->first] = it->second;
	back.clear();

	blocked[centroid] = true;
	for (ed adj : matrix[centroid])
		if (!blocked[adj.v])
			decomp(adj.v, centroid);
}

int best_path(int N, int K, int H[][2], int L[]) {
	n = N; k = K;
	for (int i = 0; i < N - 1; i++) {
		matrix[H[i][0]].push_back({H[i][1], L[i]});
		matrix[H[i][1]].push_back({H[i][0], L[i]});
	}

	memset(bestFor, 0x3f, sizeof bestFor);
	bestFor[0] = 0;
	decomp(0);

	return best >= 0x3f3f3f3f ? -1 : best;
}

int h[MAX][2], l[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> k;

	for (int i = 0; i < n - 1; i++) {
	    cin >> h[i][0] >> h[i][1] >> l[i];
	}

	printf("%d\n", best_path(n, k, h, l));
	return 0;
}
