//============================================================================
// Name        : StrategeticPlacement.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct val{
	int i, v;

	friend bool operator<(const val &a, const val &b){
		return a.v < b.v;
	}
};

struct qu{
	int i, l, r, k;

	friend bool operator<(const qu &a, const qu &b){
		return a.k < b.k;
	}
};

const int NMAX = 100000001, QMAX = 1000001;
int n, q, ba, bb, bc, ans[QMAX],
	counttree[NMAX];
val vals[NMAX];
qu queries[QMAX];

void inc(int x){
	for(; x <= n; x += x & -x){
		counttree[x]++;
	}
}

int sum(int x){
	int summ = 0;
	for(; x > 0; x -= x & -x){
		summ += counttree[x];
	}

	return summ;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> q;

	for (int i = 0; i < n; ++i) {
		cin >> ba;
		vals[i] = {i + 1, ba};
	}

	for (int i = 0; i < q; ++i) {
		cin >> ba >> bb >> bc;

		queries[i] = {i, ba + 1, bb + 1, bc};
	}

	sort(vals, vals + n);
	sort(queries, queries + q);

	int nptr = 0;
	for(int i = 0; i < q; i++){
		while(nptr < n && vals[nptr].v <= queries[i].k){
			inc(vals[nptr].i);
			nptr++;
		}

		ans[queries[i].i] = sum(queries[i].r) - sum(queries[i].l - 1);
	}

	for (int i = 0; i < q; ++i) {
		printf("%d\n", ans[i]);
	}
}
