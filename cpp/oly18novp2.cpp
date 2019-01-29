//============================================================================
// Name        : RogersHomework.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct ass{ // Ass for assignment
	int d, p; // not actually dp

	ass(int d0, int p0) : d(d0), p(p0){}
	ass() : d(-1), p(-1){}

	friend bool operator<(const ass &a, const ass &b){
		return a.p > b.p;
	}
};

const int MAX = 1000000;

struct disjoint{
	int set[MAX], ranks[MAX], size;

	disjoint(int sz){
		size = sz;
		for(int i = 1; i <= size; i++){
			set[i] = i;
		}
		fill(ranks, ranks + sz, 1);
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

int n, bd, bp;
ass assigns[MAX];
disjoint daysleft(MAX);

ll totalp = 0;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	int maxday = -1;
	for (int i = 0; i < n; ++i) {
		cin >> bd >> bp;
		assigns[i] = ass(bd, bp);

		maxday = max(maxday, bd);
	}

	sort(assigns, assigns + n);

	bool used1 = false;

	for (int i = 0; i < n; ++i) {
		int bestday = daysleft.root(assigns[i].d);
//		printf("bestday for d=%d p=%d is %d\n", assigns[i].d, assigns[i].p, bestday);

		if(bestday != 1){
			daysleft.unite(bestday - 1, bestday); // Enforce pointing to lower

			totalp += assigns[i].p;
		}
		else if(!used1){
			used1 = true;
			totalp += assigns[i].p;
		}
	}

	printf("%lld\n", totalp);
}
