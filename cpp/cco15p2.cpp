//============================================================================
// Name        : Artskjid.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
//#define DEBUG

using namespace std;

typedef long long ll;
typedef pair<int, int> p; //first = id, second = cost

struct e : p{
	friend bool operator<(const e &a, const e &b){
		return a.second > b.second;
	}
};

struct q{
	int v, cost, mask;

	q(int vv, int costt, int maskk) : v(vv), cost(costt), mask(maskk){}

	friend bool operator<(const q &a, const q &b){
		return a.cost > b.cost;
	}
};

const int MAX = 18, MAX_BM = 1 << MAX;
int n, m, buf, buf2, buf3, dist[MAX][MAX_BM];

queue<q> nextt;
vector<p> matrix[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	int bm = 1 << n;
	for (int i = 0; i < n; ++i) {
		fill(dist[i], dist[i] + bm, INT_MIN);
	}

	dist[0][1] = 0;

	for (int i = 0; i < m; ++i) {
		cin >> buf >> buf2 >> buf3;
		matrix[buf].emplace_back(buf2, buf3);
	}

	nextt.emplace(0, 0, 1);
	while(!nextt.empty()){
//		q curr = nextt.top();
		q curr = nextt.front();
		nextt.pop();

		if(curr.cost != dist[curr.v][curr.mask]){
			continue;
		}

#ifdef DEBUG
		printf(" -- curr=%d,%d,%d\n", curr.v, curr.cost, curr.mask);
#endif

		for(p adj : matrix[curr.v]){
			int altmaskcode = 1 << adj.first;

			if(curr.mask & altmaskcode){
				continue;
			}

			int alt = curr.cost + adj.second, altmask = curr.mask | altmaskcode;

#ifdef DEBUG
			printf("adj=%d,%d (+%d),%d\n", adj.first, alt, adj.second, altmask);
#endif

			if(alt > dist[adj.first][altmask]){
				dist[adj.first][altmask] = alt;
				nextt.emplace(adj.first, alt, altmask);
			}
		}
	}

#ifdef DEBUG
	printf("dist: [\n");
	for(int i = 0; i < n; i++){
		printf("%d : ", i);
		for(int j = 0; j < (1 << n); j++){
			printf("%d, ", dist[i][j]);
		}
		printf("\n");
	}
	printf("]\n");
#endif

	printf("%d\n", *max_element(dist[n - 1], dist[n - 1] + (1 << n)));
}
