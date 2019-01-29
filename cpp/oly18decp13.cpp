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
typedef pair<int, int> p;

struct q{
	ll a, b, c, d;
};


inline int grank(vector<int> &r, int oldrnk){
	return lower_bound(r.begin(), r.end(), oldrnk) - r.begin();
}

const int MAX = 1001, PMAX = 4001;
int n, ba, bb, bc, bd,
	pfx[PMAX][PMAX];
q pics[MAX];
ll tot = 0;
vector<int> xrank, yrank;

inline int gxrank(int r){
	return grank(xrank, r);
}

inline int gyrank(int r){
	return grank(yrank, r);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	set<int> tyrank, txrank;
	txrank.insert(-2000000000);
	tyrank.insert(-2000000000);

	for (int i = 0; i < n; ++i) {
		cin >> ba >> bb >> bc >> bd;

		pics[i] = {min(ba, bc), min(bb, bd), max(ba, bc), max(bb, bd)};
	}

	for (int i = 0; i < n; ++i) {
		txrank.insert(pics[i].a);
		txrank.insert(pics[i].c);
		tyrank.insert(pics[i].b);
		tyrank.insert(pics[i].d);
	}

	xrank = vector<int>(txrank.begin(), txrank.end());
	yrank = vector<int>(tyrank.begin(), tyrank.end());

	for (int i = 0; i < n; ++i) {
		int a = gxrank(pics[i].a), b = gyrank(pics[i].b), c = gxrank(pics[i].c), d = gyrank(pics[i].d);

		pfx[a][b]++;
		pfx[c][b]--;
		pfx[a][d]--;
		pfx[c][d]++;
	}

	int rx = xrank.size(), ry = yrank.size();

	for (int i = 1; i <= rx + 1; ++i) {
		for (int j = 1; j <= ry + 1; ++j) {
			pfx[i][j] += pfx[i - 1][j] + pfx[i][j - 1] - pfx[i - 1][j - 1];
		}
	}

	for (int i = 1; i < rx - 1; ++i) {
		int dx = xrank[i + 1] - xrank[i];

		for (int j = 1; j < ry - 1; ++j) {
			if(pfx[i][j]){
				tot += (ll)(dx) * (ll)(yrank[j + 1] - yrank[j]);
			}
		}
	}

	printf("%lld\n", tot);
}
