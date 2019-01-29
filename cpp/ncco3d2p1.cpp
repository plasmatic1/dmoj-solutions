	//============================================================================
// Name        : RogerSegmentTreeRecode.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 50001, TMAX = MAX * 2;
int n, q, ba, bb, arr[MAX], mintree[TMAX], maxtree[TMAX];

int recc = 20;

int create_min(int i, int l, int r){
	if(l == r){
		return mintree[i] = arr[l];
	}

	int mid = (l + r) / 2;

	return mintree[i] = min(create_min(2 * i, l, mid), create_min(2 * i + 1, mid + 1, r));
}

int create_max(int i, int l, int r){
	if(l == r){
		return maxtree[i] = arr[l];
	}

	int mid = (l + r) / 2;

	return maxtree[i] = max(create_max(2 * i, l, mid), create_max(2 * i + 1, mid + 1, r));
}

int qmin(int i, int bl, int br, int ql, int qr){
	if(br < ql || bl > qr){
		return INT_MAX;
	}

	if(bl >= ql && br <= qr){
		return mintree[i];
	}

	int mid = (bl + br) / 2;

	return min(qmin(i * 2, bl, mid, ql, qr), qmin(i * 2 + 1, mid + 1, br, ql, qr));
}

int qmax(int i, int bl, int br, int ql, int qr){
	if(br < ql || bl > qr){
		return INT_MIN;
	}

	if(bl >= ql && br <= qr){
		return maxtree[i];
	}

	int mid = (bl + br) / 2;

	return max(qmax(i * 2, bl, mid, ql, qr), qmax(i * 2 + 1, mid + 1, br, ql, qr));
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> q;

	for (int i = 1; i <= n; ++i) {
		cin >> arr[i];
	}

	create_min(1, 1, n);
	create_max(1, 1, n);

	for (int i = 0; i < q; ++i) {
		cin >> ba >> bb;

		printf("%d\n", qmax(1, 1, n, ba, bb) - qmin(1, 1, n, ba, bb));
	}
}
