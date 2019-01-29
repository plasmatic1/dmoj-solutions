//============================================================================
// Name        : tssojmockcccj5.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct p{
	int t, i;

	p(int t0, int i0) : t(t0), i(i0){}
	p() : t(-1), i(-1){}
};

const int MAX = 100001;
int n, m, a, s, t, ba, bb, best = 0,
	levels[2][MAX];
vector<int> matrix[MAX];
unordered_set<int> used[MAX];
deque<p> nextt;

bool vis[MAX], minpath[2][MAX];

void backbfs(int st, int t){
	deque<int> nextt;
	bool vis[MAX];
	nextt.push_back(st);
	memset(vis, false, sizeof vis);

	while(!nextt.empty()){
		int cur = nextt.front(), level = levels[t][cur];
		nextt.pop_front();
		minpath[t][cur] = true;
		vis[cur] = true;

		for(int adj : matrix[cur]){
			if(!vis[adj] && levels[t][adj] == level - 1){ // Was part of min path
				nextt.push_back(adj);
			}
		}
	}
}

void bfs2(){
	deque<int> nextt;
	int levels[n + 1];
	nextt.push_back(a);
	memset(levels, -1, sizeof levels);
	levels[a] = 0;

	while(!nextt.empty()){
		int cur = nextt.front(), level = levels[cur];
		nextt.pop_front();

		for(int adj : matrix[cur]){
			if(levels[adj] == -1 && minpath[0][adj] && minpath[1][adj]){
				levels[adj] = level + 1;
				nextt.push_back(adj);
			}
		}
	}

	best = *max_element(levels, levels + n + 1);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m >> a >> s >> t;

	for (int i = 1; i <= m; ++i) {
		cin >> ba >> bb;

		if(used[ba].count(bb)) continue;

		matrix[ba].push_back(bb);
		matrix[bb].push_back(ba);

		used[ba].insert(bb);
		used[bb].insert(ba);
	}

	memset(levels, -1, sizeof levels);
	levels[0][a] = levels[1][a] = 0;
	nextt.emplace_back(0, a);
	nextt.emplace_back(1, a);

	while(!nextt.empty()){
		p cur = nextt.front();
		int level = levels[cur.t][cur.i];
		nextt.pop_front();

		for(int adj : matrix[cur.i]){
			if(levels[cur.t][adj] == -1){
				levels[cur.t][adj] = level + 1;
				nextt.emplace_back(cur.t, adj);
			}
		}
	}

	backbfs(s, 0);
	backbfs(t, 1);

	bfs2();

	printf("%d\n", best);
}
