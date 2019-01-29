//============================================================================
// Name        : nc2p3.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 1000001;
int n, m, ba, bb, grpcnt[MAX];
ll total = 0;

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

		if(rv1 == rv2){
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

disjoint dset(MAX);

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	for (int i = 0; i < m; ++i) {
		cin >> ba >> bb;
		dset.unite(ba, bb);
	}

	for (int i = 1; i <= n; ++i) {
		grpcnt[dset.root(i)]++;
	}

	// Get totals

	for (int i = 1; i <= n; ++i) {
		ll cv = grpcnt[i];
		total += cv * cv;
	}

	printf("%lld\n", total);
}
