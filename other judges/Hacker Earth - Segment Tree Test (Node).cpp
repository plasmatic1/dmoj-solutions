//============================================================================
// Name        : NodeBasedSegtree.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
using namespace std;

struct segtree{
	segtree *left, *right;
	int l, r, val;

	segtree(int l0, int r0) : left(nullptr), right(nullptr), l(l0), r(r0), val(0){}

	int init(int* arr){
		if(l == r){
			return val = arr[l];
		}

		int mid = (l + r) / 2;

		left = new segtree(l, mid);
		right = new segtree(mid + 1, r);

		return val = left->init(arr) + right->init(arr);
	}

	int query(int ql, int qr){
		if(r < ql || l > qr){
			return 0;
		}

		if(l >= ql && r <= qr){
			return val;
		}

		return left->query(ql, qr) + right->query(ql, qr);
	}

	int update(int i, int v){
		if(i < l || i > r){
			return val;
		}

		if(l == i && r == i){
			return val += v;
		}

		return val = left->update(i, v) + right->update(i, v);
	}
};

segtree seg(0, 0);
const int n = 6;
int queryn = 0, arr[n] = {1, 3, 5, 7, 9, 11};

void simulate_query(int l, int r, int expected){
	int ans = seg.query(l, r);
	printf("query #%d: type=query l=%d r=%d | answer=%d\n", queryn++, l, r, ans);
	assert(ans == expected);
}

void simulate_update(int i, int v){
	seg.update(i, v);
	printf("query #%d: type=update idx=%d val=%d\n", queryn++, i, v);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	seg.l = 1;
	seg.r = n;

	seg.init(arr);

	simulate_query(1, 3, 15);
	simulate_update(1, 10);
	simulate_query(1, 3, 25);
}
