//============================================================================
// Name        : apio10p2.cpp
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
	int i, v;
};

const int MAX = 100001;
int n, k, ba, bb,
	levels[MAX], par[MAX], parEd[MAX];
vector<ed> matrix[MAX];
bool neg[MAX];

void dfs(int cur, int parv=-1, int pare=-1, int lv=0) {
	levels[cur] = lv;
	par[cur] = parv;
	parEd[cur] = pare;
	for (ed adj : matrix[cur])
		if (adj.v ^ parv)
			dfs(adj.v, cur, adj.i, lv + 1);
}

int dia2 = 0, best[MAX];
int dfs2(int cur, int parv=-1) {
	int pastBest = 0;
	for (ed adj : matrix[cur]) {
		if (adj.v == parv)
			continue;

		int weight = neg[adj.i] ? -1 : 1, curDis = dfs2(adj.v, cur) + weight;
		best[cur] = max(best[cur], curDis);
		dia2 = max(dia2, max(best[cur], curDis + pastBest));
		pastBest = max(pastBest, best[cur]);
	}

	return best[cur];
}

int maxIndex(int n, int arr[]) {
	int bestIdx = -1, best = INT_MIN;
	while (n > 0) {
		if (arr[n] > best) {
			best = arr[n];
			bestIdx = n;
		}
		n--;
	}
	return bestIdx;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	scan(n, k);

	for (int i = 1; i < n; i++) {
		scan(ba, bb);
		matrix[ba].push_back({i, bb});
		matrix[bb].push_back({i, ba});
	}

	dfs(1);
	int endP = maxIndex(n, levels);
	dfs(endP);
	int oEndP = maxIndex(n, levels), dia = levels[oEndP];

	if (k == 1) {
		printf("%d\n", ((n - 1) << 1) - dia + 1);
		return 0;
	}

	while (oEndP != -1) {
		neg[parEd[oEndP]] = true;
		oEndP = par[oEndP];
	}

	dfs2(1); // debug(dia2);
	printf("%d\n", ((n - 1) << 1) - dia - dia2 + 2);

	return 0;
}