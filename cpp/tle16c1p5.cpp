//============================================================================
// Name        : BattlePlanRecode.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
//#define DEBUG

using namespace std;

typedef long long ll;

struct ed{
	int v, w;

	ed(int v0, int w0) : v(v0), w(w0){}
	ed() : v(-1), w(-1){}

	friend bool operator<(const ed &a, const ed &b){
		return a.w > b.w;
	}
};

const int MAX = 100001, TM = MAX * 5;
int n, bp, bd, bc;
ll cost[MAX], dist[MAX];
ll totaltree[TM];
ll finalcost[MAX];

vector<ed> matrix[MAX];

int currs[MAX];

int query(int i, int bl, int br, ll q){
	if(bl == br){
		return bl;
	}

	int mid = (bl + br) / 2, lchild = i << 1, rchild = lchild | 1;

	if(totaltree[rchild] < q){
		return query(rchild, mid + 1, br, q);
	}
	return query(lchild, bl, mid, q);
}

ll update(int i, int bl, int br, int q, ll v){
    if(q < bl || q > br){
		return totaltree[i];
    }

	if(bl == q && br == q){
		return totaltree[i] = v;
	}

	int mid = (bl + br) / 2;

	return totaltree[i] = min(update(i << 1, bl, mid, q, v), update(i << 1 | 1, mid + 1, br, q, v));
}

//

void dfs(int curr, int lvl, int parent){
	for(ed other : matrix[curr]){
		//Dist
		dist[other.v] = dist[curr] + other.w;
		currs[lvl + 1] = other.v;

		//Update n query index of first lower cost node
		update(1, 1, n, lvl + 1, cost[other.v]);
		int first_lower = currs[query(1, 1, n, cost[other.v])];

		//find the final cost of the path
		if(cost[first_lower] >= cost[other.v]){
			finalcost[other.v] = cost[other.v] * dist[other.v];
		}
		else{
			finalcost[other.v] = (cost[other.v] * (dist[other.v] - dist[first_lower])) + finalcost[first_lower];
		}

		//dfs adj
		dfs(other.v, lvl + 1, curr);

		//update current node to invalid (maxv)
		update(1, 1, n, lvl + 1, LLONG_MAX);
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	//Input

	cin >> n;

	fill(totaltree, totaltree + 5 * n + 1, LLONG_MAX);

	cost[n] = INT_MAX;
	currs[1] = n;

	int n0 = n - 1;
	for (int i = 1; i <= n0; ++i) {
		cin >> bp >> bd >> bc;

		matrix[bp].emplace_back(i, bd);
		cost[i] = bc;
	}
	//Output

	dist[n] = 0;
	dfs(n, 1, -1);

	for (int i = 1; i <= n0; ++i) {
		printf("%lld\n", finalcost[i]);
	}
}
