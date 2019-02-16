//============================================================================
// Name        : LHC.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, ll> p;

const int MAX = 400001;
int n, ba, bb,
	belowdia[MAX], dia[MAX];
ll belowcnt[MAX], cnt[MAX];
vector<int> matrix[MAX];

void dfs(int cur, int lvl, int par){
	vector<p> brets, rets;
	int sz = 0, cbelowdia = 0;
	ll cbelowcnt = 1;

	for(int adj : matrix[cur]){
		if(adj ^ par){
			dfs(adj, lvl + 1, cur);

			brets.push_back(make_pair(belowdia[adj] + 1, belowcnt[adj]));
			rets.push_back(make_pair(dia[adj], cnt[adj]));
			sz++;

			// Getting best path ending at current node
			if(belowdia[adj] + 1 > cbelowdia){
				cbelowdia = belowdia[adj] + 1;
				cbelowcnt = belowcnt[adj];
			}
			else if(belowdia[adj] + 1 == cbelowdia)
				cbelowcnt += belowcnt[adj];
		}
	}

	// You can use either any existing path or join two paths together at the current node
	if(!sz)
		cnt[cur] = 1;
	else if(sz == 1){
		if(cbelowdia > rets[0].first){
			dia[cur] = cbelowdia;
			cnt[cur] = cbelowcnt;
		}
		else if(cbelowdia == rets[0].first){
			dia[cur] = cbelowdia;
			cnt[cur] = cbelowcnt + rets[0].second;
		}
		else{
			dia[cur] = rets[0].first;
			cnt[cur] = rets[0].second;
		}
	}
	else{
		sort(brets.begin(), brets.end());

		int nbest = -1;
		ll ncnt = 0;
		for(int i = 0; i < sz; i++){
			if(rets[i].first > nbest){
				nbest = rets[i].first;
				ncnt = rets[i].second;
			}
			else if(rets[i].first == nbest)
				ncnt += rets[i].second;
		}

		int bfirst = brets[sz - 1].first, bsecond = brets[sz - 2].first, bbest = bfirst + bsecond;
		ll bcnt = 0;

		if(bfirst == bsecond){
			ll tot = 0;
			for(int i = sz - 1; i >= 0 && brets[i].first == bfirst; i--){
				bcnt += brets[i].second * tot;
				tot += brets[i].second;
			}
		}
		else if(bfirst != bsecond){
			ll tot = 0;
			for(int i = sz - 2; i >= 0 && brets[i].first == bsecond; i--)
				tot += brets[i].second;
			bcnt = brets[sz - 1].second * tot;
		}

		if(bbest > nbest){
			dia[cur] = bbest;
			cnt[cur] = bcnt;
		}
		else if(bbest == nbest){
			dia[cur] = bbest;
			cnt[cur] = bcnt + ncnt;
		}
		else{
			dia[cur] = nbest;
			cnt[cur] = ncnt;
		}
	}

	belowdia[cur] = cbelowdia;
	belowcnt[cur] = cbelowcnt;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 1; i < n; ++i) {
		cin >> ba >> bb;

		matrix[ba].push_back(bb);
		matrix[bb].push_back(ba);
	}

	dfs(1, 0, -1);

	printf("%d %lld\n", dia[1] + 1, cnt[1]);
}
