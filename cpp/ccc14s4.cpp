//============================================================================
// Name        : TintedGlassWindow.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

/*
 * This code is for my self esteem
 */

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct g{
	int a, b, c, d, e;
};

const int MAX = 1001, PMAX = 2010;
int n, t, ba, bb, bc, bd, be,
	pfx[PMAX][PMAX];
ll tot;
g gls[MAX];
vector<int> xrank, yrank;

inline int grank(vector<int> &r, int v){
	return lower_bound(r.begin(), r.end(), v) - r.begin();
}

inline int gxrank(int v){
	return grank(xrank, v);
}

inline int gyrank(int v){
	return grank(yrank, v);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> t;

	set<int> txrank, tyrank;
	txrank.insert(-1);
	tyrank.insert(-1);

	for (int i = 0; i < n; ++i) {
		cin >> ba >> bb >> bc >> bd >> be;

		gls[i] = {ba, bb + 1, bc, bd + 1, be};
	}

	for (int i = 0; i < n; ++i) {
		txrank.insert(gls[i].a);
		txrank.insert(gls[i].c);

		tyrank.insert(gls[i].b);
		tyrank.insert(gls[i].d);
	}

	xrank = vector<int>(txrank.begin(), txrank.end());
	yrank = vector<int>(tyrank.begin(), tyrank.end());

	for (int i = 0; i < n; ++i) {
		int a = gxrank(gls[i].a), b = gyrank(gls[i].b), c = gxrank(gls[i].c), d = gyrank(gls[i].d), e = gls[i].e;

		pfx[a][b] += e;
		pfx[a][d] -= e;
		pfx[c][b] -= e;
		pfx[c][d] += e;
	}

	int rx = xrank.size(), ry = yrank.size();

	for (int i = 1; i < rx; ++i) {
		for (int j = 1; j < ry; ++j) {
			pfx[i][j] += pfx[i - 1][j] + pfx[i][j - 1] - pfx[i - 1][j - 1];
		}
	}

	for (int i = 1; i < rx - 1; ++i) {
		ll dx = xrank[i + 1] - xrank[i];

		for (int j = 1; j < ry - 1; ++j) {
			if(pfx[i][j] >= t){
				tot += dx * (ll)(yrank[j + 1] - yrank[j]);
			}
		}
	}

	printf("%lld\n", tot);
}
