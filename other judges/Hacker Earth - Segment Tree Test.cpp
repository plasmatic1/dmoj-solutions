//============================================================================
// Name        : RogerSegmentTreeRecode.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

/*
 *
 * Test Input
5 5
1 5 2 4 3
q 1 5
q 1 3
q 3 5
u 3 6
q 1 5

Test Output
15
8
9
19
 */

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 200001, TMAX = MAX * 2;
int n, q, ba, bb, arr[MAX], totaltree[TMAX];
char buf;

int recc = 20;

int build(int i, int l, int r){
	if(l == r){
		return totaltree[i] = arr[l];
	}

	int mid = (l + r) / 2;

	return totaltree[i] = build(2 * i, l, mid) + build(2 * i + 1, mid + 1, r);
}

int totalquery(int i, int bl, int br, int ql, int qr){
	if(ql > qr){
		return 0;
	}

	if(bl == ql && br == qr){
		return totaltree[i];
	}

	int mid = (bl + br) / 2;

	return totalquery(i * 2, bl, mid, ql, min(qr, mid)) + totalquery(i * 2 + 1, mid + 1, br, max(ql, mid + 1), qr);
}

int update(int i, int bl, int br, int q, int v){
    if(q < bl || q > br){
		return totaltree[i];
    }

	if(bl == q && br == q){
		return totaltree[i] += v;
	}

	int mid = (bl + br) / 2;

	return totaltree[i] = update(i * 2, bl, mid, q, v) + update(i * 2 + 1, mid + 1, br, q, v);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> q;

	for (int i = 1; i <= n; ++i) {
		cin >> arr[i];
	}

	build(1, 1, n);

	for (int i = 0; i < q; ++i) {
		cin >> buf >> ba >> bb;

		if(buf == 'q'){
		    printf("%d\n", totalquery(1, 1, n, ba, bb));
		}
		else{
		    update(1, 1, n, ba, -arr[ba]);
		    update(1, 1, n, ba, bb);
		    arr[ba] = bb;
		}

		printf("tree: ");
		for (int i = 1; i < n * 2 + 5; ++i) {
			printf("%d, ", totaltree[i]);
		}
		printf("\n");
	}
}
