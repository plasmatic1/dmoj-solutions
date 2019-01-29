//============================================================================
// Name        : RangeMaxQuery.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

int n, m, ba, bb;

const int MAX = 100001;
int counttree[MAX * 5], arr[MAX]; // Some random constant value that's big enough since segtree has O(n log n) space complexity

// Example: `build(1, 1, n);`
int build(int i, int l, int r){
	if(l == r){
		return counttree[i] = arr[l];
	}

	int mid = (l + r) / 2;

	return counttree[i] = max(build(i << 1, l, mid), build(i << 1 | 1, mid + 1, r));
}

// Example: (from range `a` to `b`) `query(1, 1, n, a, b);`
int totalquery(int i, int bl, int br, int ql, int qr){
	if(ql > qr){
		return INT_MIN;
	}

	if(bl == ql && br == qr){
		return counttree[i];
	}

	int mid = (bl + br) / 2;

	return max(totalquery(i << 1, bl, mid, ql, min(qr, mid)), totalquery(i << 1 | 1, mid + 1, br, max(ql, mid + 1), qr));
}

// Example: (for index `i` with value `v`) `query(1, 1, n, i, v);`
int update(int i, int bl, int br, int q, int v){
    if(q < bl || q > br){
		return counttree[i];
    }

	if(bl == q && br == q){
		return counttree[i] = v;
	}

	int mid = (bl + br) / 2;

	return counttree[i] = max(update(i << 1, bl, mid, q, v), update(i << 1 | 1, mid + 1, br, q, v));
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	for (int i = 1; i <= n; ++i) {
		cin >> arr[i];
	}

	build(1, 1, n);

	for (int i = 0; i < m; ++i) {
		cin >> ba >> bb;

		printf("%d\n", totalquery(1, 1, n, ba, bb));
	}
}
