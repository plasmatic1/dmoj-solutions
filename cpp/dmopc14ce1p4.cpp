//============================================================================
// Name        : ExamDelay.cpp
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
	int v;
	double w;

	ed(int v0, double w0) : v(v0), w(w0){}
	ed() : v(-1), w(-1){}

	friend bool operator<(const ed &a, const ed &b){
		return a.w > b.w;
	}
};

const int MAX = 1001;
const double COEFF = 1.333333333333, DIFF = 1. / 3., INF = numeric_limits<double>().max();
int n, m, ba, bb,
	levels[MAX];
double bc, bd,
	dist[MAX];
priority_queue<ed> nextt;
vector<ed> matrix[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	for (int i = 0; i < m; ++i) {
		cin >> ba >> bb >> bc >> bd;

		double v = bc / bd * 60.;
		matrix[ba].emplace_back(bb, v);
		matrix[bb].emplace_back(ba, v);
	}

	// Dijkstra

	fill(dist, dist + n + 1, INF);
	memset(levels, 0x3f, sizeof(levels));
	dist[1] = 0;
	levels[1] = 0;

	nextt.emplace(1, 0);

	while(!nextt.empty()){
		ed curr = nextt.top();
		int level = levels[curr.v] + 1;
		nextt.pop();

		if(curr.w > dist[curr.v]){
			continue;
		}

		for(ed adj : matrix[curr.v]){
			double alt = curr.w + adj.w;

			if(alt < dist[adj.v]){
				dist[adj.v] = alt;
				levels[adj.v] = level;

				nextt.emplace(adj.v, alt);
			}
			else if(alt == dist[adj.v] && level < levels[adj.v]){
				levels[adj.v] = level;

				nextt.emplace(adj.v, alt);
			}
		}
	}

//	printf("dist: ");
//	for (int i = 0; i < n + 1; ++i) {
//		printf("%f, ", dist[i] == INF ? -2. : dist[i]);
//	}
//	printf("\n");

	// End

	printf("%d\n%d\n", levels[n], (int)round(dist[n] * DIFF));
}
