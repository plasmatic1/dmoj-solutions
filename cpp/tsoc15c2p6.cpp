//============================================================================
// Name        : AllOutWar.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

//#define DEBUG

using namespace std;

typedef long long ll;

const int MAX = 30001;
int n, q, ba, bb, bv,
	arr[MAX], totaltree[MAX * 6], totallazyp[MAX * 12];

// Example: `build(1, 1, n);`
int build(int i, int l, int r){
	if(l == r){
		return totaltree[i] = arr[l];
	}

	int mid = (l + r) / 2;

	return totaltree[i] = min(build(i << 1, l, mid), build(i << 1 | 1, mid + 1, r));
}

// Example: (from range `a` to `b`) `query(1, 1, n, a, b);`
int totalquery(int i, int bl, int br, int ql, int qr){
	if(totallazyp[i]){
		totaltree[i] = max(0, totaltree[i] + totallazyp[i]);

		totallazyp[i << 1] += totallazyp[i];
		totallazyp[i << 1 | 1] += totallazyp[i];
		totallazyp[i] = 0;
	}

	if(br < ql || bl > qr){
		return INT_MAX;
	}

	if(bl >= ql && br <= qr){
		return totaltree[i];
	}

	int mid = (bl + br) / 2;

	return min(totalquery(i << 1, bl, mid, ql, qr),
			totalquery(i << 1 | 1, mid + 1, br, ql, qr));
}

// Example: (for index `i` with value `v`) `query(1, 1, n, i, v);`
int update_total(int i, int bl, int br, int ql, int qr, int v){
	if(totallazyp[i]){
		totaltree[i] = max(0, totaltree[i] + totallazyp[i]);

		totallazyp[i << 1] += totallazyp[i];
		totallazyp[i << 1 | 1] += totallazyp[i];
		totallazyp[i] = 0;
	}

	if(br < ql || bl > qr){
		return totaltree[i];
    }

	if(bl >= ql && br <= qr){
		totallazyp[i << 1] += v;
		totallazyp[i << 1 | 1] += v;

		return totaltree[i] = max(0, totaltree[i] + v);
	}

	int mid = (bl + br) / 2;

	return totaltree[i] = min(update_total(i << 1, bl, mid, ql, qr, v),
			update_total(i << 1 | 1, mid + 1, br, ql, qr, v));
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> q;

	for (int i = 1; i <= n; ++i) {
		cin >> arr[i];
	}

	build(1, 1, n);

	for (int i = 0; i < q; ++i) {
		cin >> ba >> bb >> bv;

		update_total(1, 1, n, ba, bb, -bv);

		int ar = totalquery(1, 1, n, ba, bb);

#ifdef DEBUG
		printf("tree: [");
		for(int i = 0; i < n * 5; i++){
			printf("%d, ", totaltree[i]);
		}
		printf("]\n");
#endif

		int br = totalquery(1, 1, n, 1, n);

		printf("%d %d\n", ar, br);
	}
}

/*
5 3
5 5 5 5 5
1 3 1
3 5 1
1 5 10
 */
