//============================================================================
// Name        : FunInForag.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

struct ed{
	int l, v;
	ll w;

	ed(int l0, int v0, ll w0) : l(l0), v(v0), w(w0){}
	ed() : l(-1), v(-1), w(-1){}
};

struct edd{
	int v;
	ll w;

	edd(int v0, ll w0) : v(v0), w(w0){}
	edd() : v(-1), w(-1){}

	friend bool operator<(const edd &a, const edd &b){
		return a.w > b.w;
	}
};

const int MAX = 100001;

int n, m, a, b, ba, bb;
ll bc, c;
//priority_queue<edd> nextt;
ll dist[MAX];
vector<ed> matrix[MAX];

bool sim(int i){
	fill(dist, dist + n + 1, LLONG_MAX);
	priority_queue<edd> nextt;

	dist[a] = 0;
	nextt.emplace(a, 0);

	while(!nextt.empty()){
		edd curr = nextt.top();
		nextt.pop();

		if(curr.v == b){
			break;
		}

		for(ed adj : matrix[curr.v]){
			if(adj.l > i){
				continue;
			}

			ll alt = curr.w + adj.w;
				if(alt < dist[adj.v]){
					dist[adj.v] = alt;
					nextt.emplace(adj.v, alt);
			}
		}
	}

	return dist[b] < c;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	for (int i = 0; i < m; ++i) {
		cin >> ba >> bb >> bc;

		matrix[ba].emplace_back(i, bb, bc);
		matrix[bb].emplace_back(i, ba, bc);
	}

	cin >> a >> b >> c;

	// Bsearch

	int l = 0, r = m - 1;
	while(l + 1 < r){
		int mid = (l + r) / 2;

		if(sim(mid)){
			r = mid;
		}
		else{
			l = mid;
		}
	}

//	printf("l=%d r=%d\n", l, r);

	if(sim(r)){
		printf("%d\n", r + 1);
	}
	else{
		printf("-1\n");
	}
}
