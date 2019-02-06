//============================================================================
// Name        : cco14p2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 0x3f3f3f3f;

struct ed{
	int i, v, w, s; // s = shutdown cost
};

struct edd{
	int v, w;

	bool operator<(const edd &o) const{
		return w > o.w;
	}
};

struct shut{
	int d, s;

	shut(int d0, int s0) : d(d0), s(s0){}
	shut() : d((int)INF), s(-1){}

	bool operator<(const shut &o) const{
		return d < o.d;
	}
};

const int MAX = 100001;
int n, m, a, b, q, ba, bb, bc, bd, repdist,
	dist[MAX], distto[MAX];
int shutscnt = 0;
shut shuts[MAX], tmpshuts[MAX]; // the minimum distance path the edge is part of, its shutdown cost
vector<ed> matrix[MAX], amatrix[MAX];

inline void dijkstra(int st, int end, int dist[MAX], size_t sz, vector<ed> adjs[MAX]){
	priority_queue<edd> nxt;

	memset(dist, 0x3f, sz);
	dist[st] = 0;
	nxt.push({st, 0});

	while(!nxt.empty()){
		edd cur = nxt.top();
		nxt.pop();

		if(cur.w > dist[cur.v]) continue;

		for(ed adj : adjs[cur.v]){
			int alt = cur.w + adj.w;
			if(alt < dist[adj.v]){
				dist[adj.v] = alt;
				nxt.push({adj.v, alt});
			}
		}
	}
}

inline void makeshutdowns(int extra){
	for(int i = 1; i <= n; i++){
		for(ed adj : matrix[i]){
			ll tot = (ll)dist[i] + adj.w + distto[adj.v] + extra;
			if(tot < INF)
				tmpshuts[adj.i] = min(tmpshuts[adj.i], shut((int)tot, adj.s));
		}
	}

}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> m >> a >> b;

	for (int i = 0; i < m; ++i) {
		cin >> ba >> bb >> bc >> bd;

		matrix[ba].push_back({i, bb, bc, bd});
		amatrix[bb].push_back({i, ba, bc, bd});
	}

	// Dijkstra
	dijkstra(a, b, dist, sizeof dist, matrix);
	dijkstra(b, a, distto, sizeof distto, amatrix);
	makeshutdowns(0);

	repdist = dist[b] << 1;

	dijkstra(b, a, dist, sizeof dist, matrix);
	dijkstra(a, b, distto, sizeof distto, amatrix);
	makeshutdowns(repdist);

	// shutdown shit
	for(int i = 0; i < m; i++){
		if(tmpshuts[i].d != INF)
			shuts[shutscnt++] = tmpshuts[i];
	}

	sort(shuts, shuts + shutscnt);

	for(int i = 1; i < shutscnt; i++)
		shuts[i].s += shuts[i - 1].s;

	// Answer queries
	cin >> q;

	for (int i = 0; i < q; ++i) {
		cin >> ba;

		int idx = upper_bound(shuts, shuts + shutscnt, shut(ba, -1LL)) - shuts - 1;

		if(idx < 0) printf("0\n");
		else printf("%d\n", shuts[idx].s);
	}

	return 0;
}