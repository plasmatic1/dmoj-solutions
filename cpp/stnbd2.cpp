//============================================================================
// Name        : ClaireElstein.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 100001;
ll MOD = 1000000007;
int n, m, ba, bb,
	indeg[MAX], outdeg[MAX];
vector<int> outs,
	matrix[MAX];
ll total = 0,
	dpa[MAX], dpb[MAX];

#define M_ADD(x, y) ((((x) % (MOD)) + ((y) % (MOD))) % (MOD))
#define M_SUB(x, y) ((((x) % (MOD)) - ((y) % (MOD))) % (MOD))
#define M_MUL(x, y) ((((x) % (MOD)) * ((y) % (MOD))) % (MOD))

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	for (int i = 0; i < m; ++i) {
		cin >> ba >> bb;

		matrix[ba].push_back(bb);
		outdeg[ba]++;
		indeg[bb]++;
	}

	// Initializing path count dp

	for (int i = 1; i <= n; ++i) {
		if(!indeg[i]){
			dpa[i] = 1;
		}
	}

	// DP

	for (int i = 1; i <= n; ++i) {
		for(int adj : matrix[i]){
			dpa[adj] = M_ADD(dpa[adj], dpa[i]);
		}
	}

	for (int i = 1; i <= n; ++i) {
		for(int adj : matrix[i]){
			dpb[adj] = M_ADD(dpb[adj], M_ADD(dpb[i], dpa[i]));
		}
	}

	// Getting total

	for (int i = 1; i <= n; ++i) {
		if(!outdeg[i]){
			total = M_ADD(total, dpb[i]);
		}
	}

	// Output

	printf("%lld\n", total);
}
