//============================================================================
// Name        : VampireTunnels.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <algorithm>
#include <cstdio>
#include <deque>
#include <queue>
#include <vector>
#include <climits>

using namespace std;

struct ed{
	int b, c, t;

	ed(int b0, int c0, int t0) : b(b0), c(c0), t(t0){}

	friend bool operator<(const ed &a, const ed &b){
		if(a.c == b.c){
			return a.t > b.t;
		}
		return a.c > b.c;
	}
};

const int MAXN = 1600, MAXS = 3601;
int s, n, e,
	dist[MAXS][MAXN];
vector<ed> matrix[MAXN];
priority_queue<ed> nextt;

int main() {
	scanf("%d\n%d %d", &s, &n, &e);

	for(int i = 0; i < e; i++){
		int a, b, c, t;
		scanf("%d %d %d %d", &a, &b, &c, &t);

		matrix[a].emplace_back(b, c, t);
		matrix[b].emplace_back(a, c, t);
	}

	for(int i = 0; i <= s; i++){
		fill(dist[i], dist[i] + n, INT_MAX);
	}

	nextt.emplace(0, 0, 0);
	for(int i = 0; i <= s; i++){
		dist[i][0] = 0;
	}

	int sun = -1;
	while(!nextt.empty()){
		ed curr = nextt.top();
		nextt.pop();
//		printf("ON NODE: %d, dist %d, time %d\n", curr.b, curr.c, curr.t);

		if(curr.b == n - 1){
			sun = curr.t;
			break;
		}

//		if(curr.c > dist[curr.t][curr.b]){
////			printf("skipped %d\n", curr.b);
//			continue;
//		}

		for(ed adj : matrix[curr.b]){
			int alt = curr.c + adj.c;

//			printf("main node %d (ct %d), adj %d, alt %d (is und %d)\n", curr.b, curr.t, adj.b, alt, adj.t);

			if(adj.t){
				int ctime = curr.t + adj.c;
				if(ctime <= s && alt < dist[ctime][adj.b]){
					dist[ctime][adj.b] = alt;
					nextt.emplace(adj.b, alt, ctime);
				}
			}
			else{
//				printf("curdist: %d\n", dist[curr.t][adj.b]);
				if(alt < dist[curr.t][adj.b]){
//					printf("adding...\n");
					dist[curr.t][adj.b] = alt;
					nextt.emplace(adj.b, alt, curr.t);
				}
			}
		}
	}

	if(sun == -1){
		printf("-1\n");
	}
	else{
		printf("%d\n", dist[sun][n - 1]);
	}

	return 0;
}
