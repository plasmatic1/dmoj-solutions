//============================================================================
// Name        : ncp3.cpp
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
int n, m, bp, bt, bv, maxl = -1, maxr = -1;
string tmp;
int arr[MAX], counttree[MAX * 6], totallazyp[MAX * 12];

inline void resolve_lazy_total(int i, int bl, int br){
	if(totallazyp[i]){
		counttree[i] = totallazyp[i] * (br - bl + 1);

		totallazyp[i << 1] = totallazyp[i];
		totallazyp[i << 1 | 1] = totallazyp[i];
		totallazyp[i] = 0;
	}
}

// Example: `build(1, 1, n);`
int build(int i, int l, int r){
	if(l == r){
		return counttree[i] = arr[l];
	}

	int mid = (l + r) / 2;

	return counttree[i] = build(i << 1, l, mid) + build(i << 1 | 1, mid + 1, r);
}

// Example: (from range `a` to `b`) `query(1, 1, n, a, b);`
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

int ascnt = 40;
int totalupdate(int i, int bl, int br, int ql, int qr, int v){
	resolve_lazy_total(i, bl, br);

	if(ql > qr){
		return counttree[i];
	}

	if(bl == ql && br == qr){
		totallazyp[i << 1] = v;
		totallazyp[i << 1 | 1] = v;

		return counttree[i] = v * (br - bl + 1);
	}

	int mid = (bl + br) / 2;

	return counttree[i] = totalupdate(i << 1, bl, mid, ql, min(qr, mid), v) +
			totalupdate(i << 1 | 1, mid + 1, br, max(ql, mid + 1), qr, v);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	for (int i = 1; i <= n; ++i) {
		cin >> arr[i];
	}

	// First Build Segtree

	build(1, 1, n);

	// Get initial max subarray

	int maxend = 0, maxsum = INT_MIN;

	for (int i = 1; i <= n; ++i) {
		maxend += arr[i];

		if(maxsum < maxend){
			maxr = i;
			maxsum = maxend;
		}

		if(maxend < 0){
			maxl = i + 1;
			maxend = 0;
		}
	}

	printf("l=%d r=%d\n", maxl, maxr);

	// Query

	for (int i = 0; i < m; ++i) {
		cin >> tmp;

		if(tmp == "GET-SUM"){
			cin >> bp >> bt;

			printf("%d\n", totalquery(1, 1, n, bp, bp + bt - 1));
		}
		else if(tmp == "MAX-SUM"){
			printf("%d\n", maxsum);
		}
		else{ // tmp == MAKE_SAME
			cin >> bp >> bt >> bv;
			int l = bp, r = bp + bt - 1;

			if(l >= maxl && r <= maxr){ // Case 1: Op is completely concealed
				maxsum -= totalquery(1, 1, n, l, r);
				maxsum += bv * bt;
			}
			else if(bv > 0){ // Case 2: Op is outside of bound but also value is positive
				//
			}

			totalupdate(1, 1, n, l, r, bv);
		}
	}
}
