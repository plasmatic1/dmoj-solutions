//============================================================================
// Name        : Traffic.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

/*
 * rip CPC '18 Contest 1 P4 - Angie's Tournament
 */

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 100001;
int n, m, q, ba, bb,
	blocked[MAX];
vector<int> matrix[MAX];

bool sim(int passed){
	if(blocked[1] <= passed){
		return false;
	}

	deque<int> nextt;
	bool vis[n + 1];
	memset(vis, 0, sizeof(vis));

	nextt.push_back(1);
	vis[1] = true;

	while(!nextt.empty()){
		int curr = nextt.front();
		nextt.pop_front();

		if(curr == n){
			break;
		}

		for(int adj : matrix[curr]){
			if(vis[adj] || blocked[adj] <= passed){
				continue;
			}

			vis[adj] = true;
			nextt.push_back(adj);
		}
	}

	return vis[n];
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> m >> q;

	for (int i = 1; i <= m; ++i) {
		cin >> ba >> bb;
		matrix[ba].push_back(bb);
		matrix[bb].push_back(ba);
	}

	memset(blocked, 0x3f, sizeof(blocked));
	for(int i = 1; i <= q; i++){
		cin >> ba;
		blocked[ba] = min(blocked[ba], i);
	}

	// Bsearch
	int l = 1, r = q + 1;

	while(l + 1 < r){
		int mid = (l + r) >> 1;

		if(sim(mid)){
			l = mid;
		}
		else{
			r = mid;
		}
	}

	l = sim(l) ? l : 0;

//	printf("l=%d r=%d\n", l, r);

	for(int i = 1; i <= l; i++){
		printf("YES\n");
	}

	for(int i = l + 1; i <= q; i++){
		printf("NO\n");
	}
}
