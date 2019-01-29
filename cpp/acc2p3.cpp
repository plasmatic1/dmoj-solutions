//============================================================================
// Name        : ACC2P3Poutine.cpp
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
};

struct cel{
	int p, f, s;

	cel(int p0, int v0, int w0) : p(p0), f(v0), s(w0){}
	cel() : p(-1), f(-1), s(-1){}
};

int n, q, ba, bb, bc;

const int MAX = 100001, ET_MAX = 200001, B_MAX = 18;
int edgec = 0, firsts[MAX];

vector<ed> matrix[MAX];
int dist[MAX];
ll distt[MAX];

cel sptable[B_MAX][MAX + 1];

#define _SECOND(v) v > smv && v < mv
inline void set_cel(cel &a, cel &b, cel &end){
	int mv = max(a.f, max(a.s, max(b.f, b.s))), smv = INT_MIN;

	if(_SECOND(a.f)){
		smv = a.f;
	}

	if(_SECOND(a.s)){
		smv = a.s;
	}

	if(_SECOND(b.f)){
		smv = b.f;
	}

	if(_SECOND(b.s)){
		smv = b.s;
	}

	end.f = mv;
	end.s = smv == INT_MIN ? mv : smv;
}

int query(int a, int b, int mv){ // Querys nodes `a` and `b`
	if(dist[a] > dist[b]){
		swap(a, b);
	}

	int smv = INT_MIN;

	// Equalizing levels
	int delta = dist[b] - dist[a];
	for (int i = B_MAX - 1; i >= 0; --i) {
		if(delta & (1 << i)){
			if(_SECOND(sptable[i][b].f)){
				smv = sptable[i][b].f;
			}
			if(_SECOND(sptable[i][b].s)){
				smv = sptable[i][b].s;
			}

			b = sptable[i][b].p;
		}
	}

	if(a == b){
		return smv;
	}

	for(int i = B_MAX - 1; i >= 0; --i){
		if(sptable[i][a].p != sptable[i][b].p && sptable[i][a].p != -1 && sptable[i][b].p != -1){
			if(_SECOND(sptable[i][b].f)){
				smv = sptable[i][b].f;
			}
			if(_SECOND(sptable[i][b].s)){
				smv = sptable[i][b].s;
			}
			if(_SECOND(sptable[i][a].f)){
				smv = sptable[i][a].f;
			}
			if(_SECOND(sptable[i][a].s)){
				smv = sptable[i][a].s;
			}

			a = sptable[i][a].p;
			b = sptable[i][b].p;
		}
	}

	if(_SECOND(sptable[0][b].f)){
		smv = sptable[0][b].f;
	}
	if(_SECOND(sptable[0][b].s)){
		smv = sptable[0][b].s;
	}
	if(_SECOND(sptable[0][a].f)){
		smv = sptable[0][a].f;
	}
	if(_SECOND(sptable[0][a].s)){
		smv = sptable[0][a].s;
	}

	return smv;
}
#undef _SECOND

// DFS
void dfs(int curr, int lvl, int lasted, int parent){
	dist[curr] = lvl;
	sptable[0][curr].p = parent;
	sptable[0][curr].f = lasted;
	sptable[0][curr].s = lasted;

	for(ed adj : matrix[curr]){
		if(adj.v != parent){
			dfs(adj.v, lvl + 1, adj.w, curr);
		}
	}
}

void build(){
	// DFS to build first parents and arrays
	dfs(1, 0, -1, -1);

	// Building sparse table
	for (int i = 1; i < B_MAX; ++i) {
		for (int j = 1; j <= n; ++j) {
			int directpar = sptable[i - 1][j].p;

			if(directpar != -1){
				sptable[i][j].p = sptable[i - 1][directpar].p;
				set_cel(sptable[i - 1][j], sptable[i - 1][directpar], sptable[i][j]);
			}
		}
	}
}

unordered_set<int> adjs[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 1; i < n; ++i) {
		cin >> ba >> bb >> bc;

		matrix[ba].emplace_back(bb, bc);
		matrix[bb].emplace_back(ba, bc);

		adjs[ba].insert(bb);
		adjs[bb].insert(ba);
	}

	// LCA

	build();

	// query

	cin >> q;

	for (int i = 0; i < q; ++i) {
		cin >> ba >> bb;

		if(adjs[ba].count(bb)){
			printf("-1\n");
		}
		else{
			int qr = query(ba, bb, query(ba, bb, INT_MAX));
			assert(qr != INT_MIN);
			printf("%d\n", qr == INT_MIN ? -1 : qr);
		}
	}
}
