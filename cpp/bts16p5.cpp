//============================================================================
// Name        : CherryTree.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
//#define DEBUG

using namespace std;

struct p{
	int v, cost;

	p(int vv, int costt) : v(vv), cost(costt){}
	p() : v(-1), cost(-1){}
};

struct p2{
	int v, cost;

	p2(int vv, int costt) : v(vv), cost(costt){}
	p2() : v(-1), cost(-1){}

	friend bool operator<(const p2 &a, const p2 &b){
		return a.cost > b.cost;
	}
};

const int MAX = 100001; //CM = KM = 100000
int n, c, k, buf, buf2, buf3, beginn = 1, ans = 0, endlevel = -1, //lmao wtf
		levels[MAX], points[MAX], cost[MAX], final_pts[MAX];
bool endnode[MAX], not_begin[MAX];
p parent[MAX];
vector<p> matrix[MAX];
queue<int> nextt;
multiset<p2> sorted_points;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	memset(levels, -1, sizeof(levels));

	cin >> n >> c >> k;
	//c = min cherries
	//k = max cost

	for (int i = 1; i <= n; ++i) {
		cin >> points[i];
	}

	for (int i = 1; i < n; ++i) {
		cin >> buf >> buf2 >> buf3;
		matrix[buf].emplace_back(buf2, buf3);
		parent[buf2] = p(buf, buf3);

		not_begin[buf2] = true;
	}

	//Find begin
	for (int i = 1; i <= n; ++i) {
		if(!not_begin[i]){
			beginn = i;
			break;
		}
	}

	//BFS
	nextt.push(beginn);
	levels[beginn] = 0;

	while(!nextt.empty()){
		int curr = nextt.front(), level = levels[curr];
		nextt.pop();
		sorted_points.emplace(curr, level);

		for(p adj : matrix[curr]){
			if(levels[adj.v] == -1){
				levels[adj.v] = level + 1;

				nextt.push(adj.v);
			}
		}
	}

	//Find end
	for(p2 point : sorted_points){
		if(endlevel == -1){
			endlevel = point.cost;
			endnode[point.v] = true;
		}
		else if(point.cost == endlevel){
			endnode[point.v] = true;
		}
	}

	for(p2 point : sorted_points){
		int v = point.v;
		if(!endnode[v]){
			int total = parent[v].cost != -1 ? parent[v].cost : 0, total_pts = points[v];
			for(p adj : matrix[v]){
				total += cost[adj.v];
				total_pts += final_pts[adj.v];
			}
			cost[v] = total;
			final_pts[v] = total_pts;
		}
		else{
			cost[v] = parent[v].cost;
			final_pts[v] = points[v];
		}
	}

	for (int i = 1; i <= n; ++i) {
		if(i == beginn){
			continue;
		}

		if(cost[i] <= k && final_pts[i] >= c){
			ans++;
		}
	}

	printf("%d\n", ans);
}
