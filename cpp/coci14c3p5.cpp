//============================================================================
// Name        : Stogovi.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> p;

//n
const int MAX = 300001;
int n;

// sparse table
const int B_MAX = 19;
vector<int> sptable[B_MAX];

// input
char bi;
int bv, bw;

//dfs and graph theorying
vector<int> matrix[MAX];
int parent[MAX], size[MAX], top[MAX], dists[MAX];
int mappedtoa[MAX];

// LCA processing
int firstinstance[MAX]; // Edges list
#define PUSH_EDGE(a) sptable[0].push_back(a)

// offlien query processing
struct query{
	int val, val2; //the value that was popped if b, the value of `w` if c
};
vector<query> queries;
#define PUSH_QUERY(a, b) queries.push_back({a, b})

// Sparse Table Functions
inline int dmin(int na, int nb){
	if(dists[nb] >= dists[na]){
		return na;
	}
	return nb;
}

void build(){ // Builds sparse table `sptable` from array `arr`
	for (int i = 1; i < B_MAX; ++i) {
		int gap = 1 << (i - 1), maxv = sptable[0].size() - (1 << i);

		sptable[i].push_back(0);
		for (int j = 1; j <= maxv; ++j) {
			sptable[i].push_back(dmin(sptable[i - 1][j], sptable[i - 1][j + gap]));
		}
	}
}

int query(int a, int b){ // Querys the range from `a` to `b`
	// Find max bit
	int delta = b - a, maxbit = 1, // Max bit begins at 0 to account for `b - maxbit + 1` when `a == b`
			maxbitind = 0; // Row of the sparse table to use

	for (int i = B_MAX; i >= 0; --i) {
		int v = 1 << i;

		if(delta & v){
			maxbit = v;
			maxbitind = i;
			break;
		}
	}

	// Return Range
	return dmin(sptable[maxbitind][a],
			sptable[maxbitind][b - maxbit + 1]);
}

void dfs(int curr, int dist){
	dists[curr] = dist;
	PUSH_EDGE(curr);

	for(int adj : matrix[curr]){
		dfs(adj, dist + 1);

		PUSH_EDGE(curr);
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;
	fill(mappedtoa, mappedtoa + n + 1, -1);
	sptable[0].push_back(0);

	// Building Adjecency

	for (int i = 1; i <= n; ++i) {
		cin >> bi >> bv;

		if(mappedtoa[bv] != -1){
			bv = mappedtoa[bv];
		}

		// bv -> i

		if(bi == 'a'){
			parent[i] = bv;
			top[i] = i;
			size[i] = size[bv] + 1;

			matrix[bv].push_back(i);
		}
		else if(bi == 'b'){
			mappedtoa[i] = parent[bv];
			PUSH_QUERY(top[bv], -1);
		}
		else{ // bi == c
			cin >> bw;

			mappedtoa[i] = bv;
			PUSH_QUERY(bv, bw);
		}
	}

	//Sparse table construction and stuff

	dfs(0, 0);
	build();

	//Getting first occurences

	for (int i = 1; i < sptable[0].size(); ++i) {
		if(!firstinstance[sptable[0][i]]){
			firstinstance[sptable[0][i]] = i;
		}
	}

	// Process

	for (int i = 0; i < queries.size(); ++i) {
		int val = queries[i].val, val2 = queries[i].val2;

		if(val2 == -1){
			printf("%d\n", val);
		}
		else{
			if(mappedtoa[val] != -1){
				val = mappedtoa[val];
			}

			if(mappedtoa[val2] != -1){
				val2 = mappedtoa[val2];
			}

			int insta = firstinstance[val], instb = firstinstance[val2];

			printf("%d\n", size[query(
					min(insta, instb), max(insta, instb))]);
		}
	}
}

/*
6
a 0
a 1
c 1 2
c 2 3
b 4
b 2
 */
