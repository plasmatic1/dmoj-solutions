//============================================================================
// Name        : ccc09s4.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct ed{
	int v, w;

	bool operator<(const ed &o) const {
		return w > o.w;
	}
};

const int MAX = 5001;
int n, t, k, d, ba, bb, bc, best = INT_MAX,
	dis[MAX], pencil[MAX], cost[MAX];
vector<ed> matrix[MAX];
deque<int> nxt;
bool tvis[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> t;

	for (int i = 0; i < t; ++i) {
		cin >> ba >> bb >> bc;
		matrix[ba].push_back({bb, bc});
		matrix[bb].push_back({ba, bc});
	}

	cin >> k;

	for (int i = 0; i < k; ++i) {
		cin >> ba >> bb;

		pencil[i] = ba;
		cost[i] = bb;
	}

	cin >> d;

	memset(dis, 0x3f, sizeof dis);
	nxt.push_back(d);
	dis[d] = 0;
	tvis[d] = true;

	while(!nxt.empty()){
		int cur = nxt.front();
		nxt.pop_front();
		tvis[cur] = false;

		for(ed adj : matrix[cur]){
			int alt = dis[cur] + adj.w;
			if(alt < dis[adj.v]){
				dis[adj.v] = alt;
				if(!tvis[adj.v]){
					nxt.push_back(adj.v);
					tvis[adj.v] = true;
				}
			}
		}
	}

	for (int i = 0; i < k; ++i)
		best = min(best, dis[pencil[i]] + cost[i]);

	printf("%d\n", best);
}