//============================================================================
// Name        : Graphs.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 100001;
int n, m, q, ba, bb;

vector<int> matrix[MAX];

struct pi{
	int i, j;

	pi(int i0, int j0) : i(i0), j(j0){}
	pi() : i(-1), j(-1){}
};

struct disjoint{
	int set[MAX], size;

	disjoint(int sz){
		size = sz;
		for(int i = 0; i < size; i++){
			set[i] = i;
		}
	}

	int root(int val){
		if(set[val] == val){
			return val;
		}

		return set[val] = root(set[val]);
	}

	void unite(int v1, int v2){
		int rv1 = root(v1);
		int rv2 = root(v2);

		if(v1 == v2){
			return;
		}

		if(v1 < v2){
			set[rv2] = rv1;
			root(v2);
		}
		else{
			set[rv1] = rv2;
			root(v1);
		}
	}

	bool same(int v1, int v2){
		return root(v1) == root(v2);
	}
};

/*
4 2 3
1 2
2 3
1 3
2 3
1 4
 */

int levels[MAX], levels2[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> m >> q;

	disjoint dset(n);

	for (int i = 0; i < m; ++i) {
		cin >> ba >> bb;

		matrix[ba].push_back(bb);
		matrix[bb].push_back(ba);

		dset.unite(ba - 1, bb - 1);
	}

	for (int i = 0; i < q; ++i) {
		cin >> ba >> bb;

		if(ba == bb){
			printf("0\n");
			continue;
		}

		if(!dset.same(ba - 1, bb - 1)){
			printf("-1\n");
			continue;
		}

//		int levels[n + 1], levels2[n + 1];

		deque<pi> nextt;
//		vector<int> viss;

		memset(levels, -1, sizeof(levels));
		memset(levels2, -1, sizeof(levels2));

		levels[ba] = 0;
		levels2[bb] = 0;

		nextt.emplace_back(ba, 0);
		nextt.emplace_back(bb, 1);

		int meet = -1;

		while(!nextt.empty()){
			pi curr = nextt.front();
			nextt.pop_front();

			bool bk = false;

			for(int adj : matrix[curr.i]){
				if(curr.j){
					if(levels2[adj] != -1){
						continue;
					}
				}
				else{
					if(levels[adj] != -1){
						continue;
					}
				}

//				viss.push_back(adj);

				if(curr.j){ //curr.j == 1
					levels2[adj] = levels2[curr.i] + 1;

					if(levels[adj] != -1){
						meet = adj;
						bk = true;
						break;
					}
				}
				else{
					levels[adj] = levels[curr.i] + 1;

					if(levels2[adj] != -1){
						meet = adj;
						bk = true;
						break;
					}
				}

				nextt.emplace_back(adj, curr.j);
			}

			if(bk){
				break;
			}
		}

//		printf("levels: ");
//		for (int i = 0; i < n + 1; ++i) {
//			printf("%d, ", levels[i]);
//		}
//		printf("\n");
//		printf("levels2: ");
//		for (int i = 0; i < n + 1; ++i) {
//			printf("%d, ", levels2[i]);
//		}
//		printf("\n");

		printf("%d\n", levels[meet] + levels2[meet]);
	}
}
