//============================================================================
// Name        : dmpg17g2.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct trip{
	ll pfx, sfx, sub;
	bool valid;
};

const int MAX = 100001, MS = MAX << 2;
int n, q, ba, bb,
	arr[MAX];
ll sumt[MS], pfxt[MS], sfxt[MS], subt[MS]; // sumt => sum tree, pfxt => max prefix tree, sfxt => max suffix tree, subt => max subarray tree
char bt;

ll bsum(int i, int l, int r){
	if(l == r) return sumt[i] = arr[l];

	int mid = (l + r) >> 1;
	return sumt[i] = bsum(i << 1, l, mid) + bsum(i << 1 | 1, mid + 1, r);
}

ll updsum(int i, int l, int r, int q, int v){
	if(q < l || q > r) return sumt[i];
	if(q == l && q == r) return sumt[i] = v;

	int mid = (l + r) >> 1;
	return sumt[i] = updsum(i << 1, l, mid, q, v) + updsum(i << 1 | 1, mid + 1, r, q, v);
}

inline void setone(int i, int val){ // set the prefix, suffix, and best sub for a range [i, i]
	pfxt[i] = sfxt[i] = subt[i] = val;
}

inline void computesums(int i){ // Computes the best prefix sum, suffix sum, and best subarray sum for a node i
	int lhs = i << 1, rhs = lhs | 1;

	pfxt[i] = max(pfxt[lhs], sumt[lhs] + pfxt[rhs]);
	sfxt[i] = max(sfxt[rhs], sumt[rhs] + sfxt[lhs]);
	subt[i] = max(sfxt[lhs] + pfxt[rhs], max(subt[lhs], subt[rhs]));
}

void build(int i, int l, int r){
	if(l == r){
		setone(i, arr[l]);
		return;
	}

	int mid = (l + r) >> 1;

	build(i << 1, l, mid);
	build(i << 1 | 1, mid + 1, r);

	computesums(i);
}

void update(int i, int l, int r, int q, int v){
	if(q < l || q > r) return;
	if(q == l && q == r){
		setone(i, v);
		return;
	}

	int mid = (l + r) >> 1;

	update(i << 1, l, mid, q, v);
	update(i << 1 | 1, mid + 1, r, q, v);
	computesums(i);
}

void query(int i, int l, int r, int ql, int qr, trip &ret){
	if(qr < l || ql > r){
		ret = {-1, -1, -1, false};
		return;
	}
	if(l >= ql && r <= qr){
		ret = {pfxt[i], sfxt[i], subt[i], true};
		return;
	}

	int mid = (l + r) >> 1, lhs = i << 1, rhs = lhs | 1;
	trip lhst, rhst;

	query(lhs, l, mid, ql, qr, lhst);
	query(rhs, mid + 1, r, ql, qr, rhst);

	if(!lhst.valid) ret = rhst;
	else if(!rhst.valid) ret = lhst;
	else{
		ret.pfx = max(lhst.pfx, sumt[lhs] + rhst.pfx);
		ret.sfx = max(rhst.sfx, sumt[rhs] + lhst.sfx);
		ret.sub = max(lhst.sfx + rhst.pfx, max(lhst.sub, rhst.sub));
		ret.valid = true;
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> q;

	for(int i = 1; i <= n; i++)
		cin >> arr[i];

	bsum(1, 1, n);
	build(1, 1, n);

	for (int i = 0; i < q; ++i) {
		cin >> bt >> ba >> bb;

		if(bt == 'S'){ // Update
			updsum(1, 1, n, ba, bb);
			update(1, 1, n, ba, bb);
		}
		else{ // Query
			trip ret;
			query(1, 1, n, ba, bb, ret);
			printf("%lld\n", ret.sub);
		}
	}
}
