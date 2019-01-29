//============================================================================
// Name        : LeLeiAndContest.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 200001;
int m, n, q, bi, bl, br, bx,
	arr[MAX], counttree[MAX * 6], totallazyp[MAX * 12]; // Large arbitrary coefficients to account for O(nlogn) size

#define M_ADD(x, y) ((((x) % (m)) + ((y) % (m))) % (m))
#define M_MUL(x, y) ((((x) % (m)) * ((y) % (m))) % (m))

// This code works based on the premise that (x % m) is equal to (x^m % m)
// Segment tree

inline void resolve_lazy_total(int i, int l, int r){
	if(totallazyp[i]){
		counttree[i] = M_ADD(counttree[i], M_MUL(totallazyp[i], r - l + 1));

		totallazyp[i << 1] += totallazyp[i];
		totallazyp[i << 1 | 1] += totallazyp[i];
		totallazyp[i] = 0;
	}
}

int build(int i, int l, int r){
	if(l == r){
		return counttree[i] = arr[l] % m;
	}

	int mid = (l + r) / 2;

	return counttree[i] = M_ADD(build(i << 1, l, mid), build(i << 1 | 1, mid + 1, r));
}

int totalquery(int i, int bl, int br, int ql, int qr){
	resolve_lazy_total(i, bl, br);

	if(ql > qr){
		return 0;
	}

	if(bl == ql && br == qr){
		return counttree[i];
	}

	int mid = (bl + br) / 2;

	int qval = M_ADD(totalquery(i << 1, bl, mid, ql, min(qr, mid)),
			totalquery(i << 1 | 1, mid + 1, br, max(ql, mid + 1), qr));

	return qval;
}

int totalupdate(int i, int bl, int br, int ql, int qr, int v){
	resolve_lazy_total(i, bl, br);

	if(ql > qr){
		return counttree[i];
	}

	if(bl == ql && br == qr){
		totallazyp[i << 1] += v;
		totallazyp[i << 1 | 1] += v;

		return counttree[i] = M_ADD(counttree[i], M_MUL(v, br - bl + 1));
	}

	int mid = (bl + br) / 2;

	return counttree[i] = M_ADD(totalupdate(i << 1, bl, mid, ql, min(qr, mid), v),
			totalupdate(i << 1 | 1, mid + 1, br, max(ql, mid + 1), qr, v));
}

// Main Function

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> m >> n >> q;

	for (int i = 1; i <= n; ++i) {
		cin >> arr[i];
	}

	build(1, 1, n);

	// Queries

	for (int i = 0; i < q; ++i) {
		cin >> bi >> bl >> br;

		if(bi == 1){
			cin >> bx;

			totalupdate(1, 1, n, bl, br, bx % m);
		}
		else{ // bi == 2
			printf("%d\n", totalquery(1, 1, n, bl, br));
		}
	}
}
