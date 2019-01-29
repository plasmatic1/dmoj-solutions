//============================================================================
// Name        : JsumabatContestP2.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct p{
	int l, r;

	p(int l0, int r0) : l(l0), r(r0){}
	p() : l(-1), r(-1){}

	friend bool operator<(const p &a, const p &b){
		if(a.r == b.r){
			return a.l < b.l;
		}

		return a.r < b.r;
	}
};

const int MAX = 100001;
int n, q, ba, bb, bt,
	pfx[MAX], tree[MAX], vals[MAX];
set<p> collapses;

void add(int x, int z){
	for(; x <= n; x += x & -x){
		tree[x] += z;
	}
}

void vadd(int x, int z){
	add(x, z);
	vals[x] += z;
}

void setv(int x, int z){
	add(x, z - vals[x]);
	vals[x] = z;
}

int sum(int x){
	int s = 0;
	for(; x > 0; x -= x & -x){
		s += tree[x];
	}
	return s;
}

inline int truemod(int a, int b){
	if(a % b == 0){
		return b;
	}
	return a % b;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> q;

	for (int i = 1; i <= n; ++i) {
		cin >> pfx[i];
	}

	for(int i = 1; i <= n; i++){
		pfx[i] += pfx[i - 1];
	}

	for (int i = 0; i < q; ++i) {
		cin >> bt >> ba;

		int totcnt = n - sum(n);
		ba = truemod(ba, totcnt);

		printf(" -- i=%d totcnt=%d ba=%d\n", i, totcnt, ba);

		if(bt == 1){
			cin >> bb;

			int rightof = totcnt - ba + 1;
			bb = truemod(bb, rightof);

			if(bb == 1){ // Pointless collapse
				continue;
			}

			int rhs = sum(ba + bb - 1) - sum(ba - 1);

			if(rhs > 0){
				vadd(ba, rhs);
				for(int j = ba + 1; j < ba + bb - 1; j++){
					setv(j, 0);
				}
			}

			vadd(ba, bb - 1);

		}
		else if(bt == 2){
			int rhs = ba + vals[ba];
			collapses.erase(collapses.lower_bound(p(ba, rhs)));

			setv(ba, 0);
		}
		else{ //bt == 3
			cin >> bb;

			int rightof = totcnt - ba + 1;
			bb = truemod(bb, rightof);

			int r = ba + bb - 1, trueright = r + sum(r) - sum(ba - 1);
			printf("r=%d trueright=%d\n", r, trueright);
			printf("%d\n", pfx[trueright] - pfx[ba - 1]);
		}
	}
}
