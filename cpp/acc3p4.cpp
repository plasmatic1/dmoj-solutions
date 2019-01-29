//============================================================================
// Name        : RangeUpdateAndRangeQuery.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 1000001;
int n, q, bi, bl, br, bx,
	arr[MAX], counttree[MAX * 6], totallazyp[MAX * 12], lazybeg[MAX * 12];

// Segment tree

inline void resolve_lazy_total(int i, int l, int r){
	if(totallazyp[i]){
		int beg = lazybeg[i], tr = br - beg + 1, tl = bl - beg + 1;
		counttree[i] += totallazyp[i] * ((tr * (tr + 1) - (tl - 1) * tl) / 2);

		totallazyp[i << 1] += totallazyp[i];
		totallazyp[i << 1 | 1] += totallazyp[i];
		lazybeg[i << 1] = beg;
		lazybeg[i << 1 | 1] = beg;

		totallazyp[i] = 0;
		lazybeg[i] = 0;
	}
}

int build(int i, int l, int r){
	if(l == r){
		return counttree[i] = arr[l];
	}

	int mid = (l + r) / 2;

	return counttree[i] = build(i << 1, l, mid) + build(i << 1 | 1, mid + 1, r);
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

	int qval = totalquery(i << 1, bl, mid, ql, min(qr, mid)) +
			totalquery(i << 1 | 1, mid + 1, br, max(ql, mid + 1), qr);

	return qval;
}

int update(int i, int bl, int br, int ql, int qr, int v, int beg){
	resolve_lazy_total(i, bl, br);

	if(ql > qr){
		return counttree[i];
	}

	if(bl == ql && br == qr){
		totallazyp[i << 1] += v;
		totallazyp[i << 1 | 1] += v;
		lazybeg[i << 1] = beg;
		lazybeg[i << 1 | 1] = beg;

		int tr = br - beg + 1, tl = bl - beg + 1;
		return counttree[i] += v * ((tr * (tr + 1) - (tl - 1) * tl) / 2);
	}

	int mid = (bl + br) / 2;

	return counttree[i] = update(i << 1, bl, mid, ql, min(qr, mid), v, beg) +
			update(i << 1 | 1, mid + 1, br, max(ql, mid + 1), qr, v, beg);
}

// Main Function

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> q;

	// Queries

	for (int i = 0; i < q; ++i) {
		cin >> bi >> bl >> br;

		if(bi == 1){ // Increment
			cin >> bx;

			update(1, 1, n, bl, br, bx, bl);
		}
		else{ // Sum
			printf("%d\n", totalquery(1, 1, n, bl, br));
		}
	}
}
