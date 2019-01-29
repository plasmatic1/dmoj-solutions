//============================================================================
// Name        : MinimumCostFlow.cpp
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
	int a, b, c, n;

	ed(int a0, int b0, int c0, int n0) : a(a0), b(b0), c(c0), n(n0){}
	ed() : a(-1), b(-1), c(-1), n(-1){}

	friend bool operator<(const ed &a, const ed &b){
		if(a.c == b.c){
			return a.n < b.n;
		}
		return a.c < b.c;
	}
};

const int MAX = 200001;
int n, m, d, ba, bb, bc;
ed edges[MAX];

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

disjoint dset(MAX), dset2(MAX);
int total = 0;
ed maxe;

ed better(ed &a, ed &b){
	if(a < b){
		return b;
	}
	return a;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m >> d;

	int n0 = n - 1;
	for (int i = 0; i < m; ++i) {
		cin >> ba >> bb >> bc;

		edges[i] = ed(ba, bb, bc, i >= n0);
	}

	sort(edges, edges + m);

	for(ed edge : edges){
		if(!dset.same(edge.a, edge.b)){
			dset.unite(edge.a, edge.b);
			maxe = better(maxe, edge);

			if(edge.n){
				total++;
			}
		}
	}

	if(maxe.c < d){ // Otherwise just enhance the most expensive pipe in the MST
		for(ed edge : edges){
			if(!dset2.same(edge.a, edge.b)){
				if(edge.c < maxe.c || (
						edge.c == maxe.c && !edge.n)){
					dset2.unite(edge.a, edge.b);
				}
				else if(!edge.n && edge.c <= d){
					total--;
					break;
				}
			}
		}
	}

	printf("%d\n", total);
}
