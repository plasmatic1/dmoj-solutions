//============================================================================
// Name        : FlightPlanning.cpp
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

	ed(int v0, int w0) : v(v0), w(w0){}
	ed() : v(-1), w(-1){}

	friend bool operator<(const ed &a, const ed &b){
		return a.w > b.w;
	}
};

const int MAX = 20001, KMAX = 201, MV = 0x3f3f3f3f;
int n, m, k, q, ba, bb, bc,
	hubs[MAX], hubdis[KMAX][MAX], hubdis2[KMAX][MAX];
vector<ed> matrix1[MAX], matrix2[MAX];
ll tot = 0, totcnt = 0;

void dijkstra(vector<ed> matrix[MAX], int *dis, int begin){
	priority_queue<ed> nextt;

	nextt.emplace(begin, 0);
	dis[begin] = 0;

	while(!nextt.empty()){
		ed curr = nextt.top();
		nextt.pop();

		if(curr.w > dis[curr.v]){
			continue;
		}

		for(ed adj : matrix[curr.v]){
			int alt = curr.w + adj.w;

			if(alt < dis[adj.v]){
				dis[adj.v] = alt;
				nextt.emplace(adj.v, alt);
			}
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m >> k >> q;

	for (int i = 0; i < m; ++i) {
		cin >> ba >> bb >> bc;

		matrix1[ba].emplace_back(bb, bc);
		matrix2[bb].emplace_back(ba, bc);
	}

	for (int i = 0; i < k; ++i) {
		cin >> ba;
		hubs[i] = ba;

		memset(hubdis[i], 0x3f, sizeof(hubdis[i]));
		memset(hubdis2[i], 0x3f, sizeof(hubdis2[i]));
		dijkstra(matrix1, hubdis[i], ba);
		dijkstra(matrix2, hubdis2[i], ba);
	}

	for (int i = 0; i < q; ++i) {
		cin >> ba >> bb;

		int mindis = MV;

		for (int j = 0; j < k; ++j) {
			mindis = min(mindis, hubdis2[j][ba] + hubdis[j][bb]);
		}

		if(mindis != MV){
			totcnt++;
			tot += mindis;
		}
	}

	printf("%lld\n%lld\n", totcnt, tot);
}
