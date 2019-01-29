//============================================================================
// Name        : DisjointSetTest.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 100001;

struct disjoint{
	int set[MAX], ranks[MAX], size;

	disjoint(int sz){
		size = sz;
		for(int i = 0; i < size; i++){
			set[i] = i;
		}
		fill(ranks, ranks + sz, 1);
	}

	int root(int val){
		if(set[val] == val){
			return val;
		}
		return root(set[val]);
	}

	void unite(int v1, int v2){
		v1 = root(v1);
		v2 = root(v2);

		if(ranks[v1] < ranks[v2]){
			set[v1] = v2;
		}
		else if(ranks[v1] > ranks[v2]){
			set[v2] = v1;
		}
		else{
			set[v2] = v1;
			ranks[v1]++;
		}
	}

	bool same(int v1, int v2){
		return root(v1) == root(v2);
	}
};

int n, m, ba, bb, edcount = 0;
vector<int> eds;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> m;

	disjoint dset(n);

	for (int i = 1; i <= m; ++i) {
		cin >> ba >> bb;

		if(!dset.same(ba, bb)){
			eds.push_back(i);
			dset.unite(ba, bb);
			edcount++;
		}
	}

	if(edcount + 1 >= n){
		for(int i : eds){
			printf("%d\n", i);
		}
	}
	else{
		printf("Disconnected Graph\n");
	}
}
