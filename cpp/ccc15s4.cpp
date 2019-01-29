//============================================================================
// Name        : ConvexHull.cpp
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
	int v, w, h;

	friend bool operator<(const ed &a, const ed &b){
		return a.w > b.w;
	}
};

const int MAX = 2001,
		KMAX = 201;

int n, m, k, a, b, ba, bb, bt, bh,
	dist[MAX][KMAX];

vector<ed> matrix[MAX];
priority_queue<ed> nextt;

const int INF = 0x3f3f3f3f, INFB = 0x3f;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> k >> n >> m;

	for (int i = 0; i < m; ++i) {
		cin >> ba >> bb >> bt >> bh;

		matrix[ba].push_back({bb, bt, bh});
		matrix[bb].push_back({ba, bt, bh});
	}

	cin >> a >> b;


	memset(dist, INFB, sizeof(dist));
	dist[a][0] = 0;
	nextt.push({a, 0, 0});

	while(!nextt.empty()){
		ed curr = nextt.top();
		nextt.pop();

		if(curr.v == b){
			break;
		}

		for(ed adj : matrix[curr.v]){
			int alt = curr.w + adj.w, alth = curr.h + adj.h;

			if(alth < k && alt < dist[adj.v][alth]){
				dist[adj.v][alth] = alt;
				nextt.push({adj.v, alt, alth});
			}
		}
	}

	int mindist = *min_element(dist[b], dist[b] + 201);

	if(mindist == INF){
		printf("-1\n");
	}
	else{
		printf("%d\n", mindist);
	}
}
