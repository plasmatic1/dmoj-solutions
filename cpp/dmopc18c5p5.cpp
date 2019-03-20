//============================================================================
// Name        : dmopc18c5p5.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MAX = 200010, SM = MAX << 1;
int n, rsz,
	v[MAX], w[MAX];
ll dp[MAX], tree[2][SM << 2], lazy[2][SM << 3];
vector<int> rank_;

inline int grank(int x){
	return lower_bound(rank_.begin(), rank_.end(), x) - rank_.begin() + 1;
}

// 0 -> min, 1 -> max
inline ll fun(bool op, ll a, ll b){
	switch(op){
	case 0: return min(a, b);
	default: return max(a, b);
	}
}

inline void updlazy(bool op, int i){
	if(lazy[op][i]){
		tree[op][i] += lazy[op][i];
		lazy[op][i << 1] += lazy[op][i];
		lazy[op][i << 1 | 1] += lazy[op][i];
		lazy[op][i] = 0;
	}
}

// Init segtrees
void init(int i, int l, int r){
	tree[0][i] = INF;
	tree[1][i] = -INF;

	if(l == r) return;
	int mid = (l + r) >> 1;

	init(i << 1, l, mid);
	init(i << 1 | 1, mid + 1, r);
}

// Range min/max query
ll query(bool op, int i, int l, int r, int ql, int qr){
	updlazy(op, i);
	if(l > qr || r < ql) return op ? -INF : INF;
	if(l >= ql && r <= qr) return tree[op][i];

	int mid = (l + r) >> 1;
	return fun(op, query(op, i << 1, l, mid, ql, qr), query(op, i << 1 | 1, mid + 1, r, ql, qr));
}

// Single node (set) update
ll updx(bool op, int i, int l, int r, int q, ll v){
	updlazy(op, i);
	if(l > q || r < q) return tree[op][i];
	if(q == l && q == r) return tree[op][i] = fun(op, tree[op][i], v);

	int mid = (l + r) >> 1;
	return tree[op][i] = fun(op, updx(op, i << 1, l, mid, q, v), updx(op, i << 1 | 1, mid + 1, r, q, v));
}

// Range (add) update
ll updrange(bool op, int i, int l, int r, int ql, int qr, ll v){
	updlazy(op, i);
	if(l > qr || r < ql) return tree[op][i];
	if(l >= ql && r <= qr) {
		lazy[op][i] = v;
		updlazy(op, i);
		return tree[op][i];
	}

	int mid = (l + r) >> 1;
	return tree[op][i] = fun(op, updrange(op, i << 1, l, mid, ql, qr, v), updrange(op, i << 1 | 1, mid + 1, r, ql, qr, v));
}

// Macros to make operations simpler
#define ALL 1, 1, rsz
#define QUERY(op, l, r) query((op), ALL, (l), (r))
#define UPDX(op, idx, val) updx((op), ALL, (idx), (val))
#define UPDRANGE(op, l, r, val) updrange((op), ALL, (l), (r), (val))

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	// Input and rank compression
	cin >> n;

	set<int> tmprank;
	for(int i = 1; i <= n; i++)
		cin >> v[i] >> w[i], tmprank.insert(v[i]), tmprank.insert(w[i]);
	rank_ = vector<int>(tmprank.begin(), tmprank.end());
	rsz = rank_.size();

	// Initialization
	init(ALL);
	dp[0] = 0;
	int crank = grank(v[1]);
	UPDX(0, crank, v[1]);
	UPDX(1, crank, v[1]);

	// dp calculations
	for(int i = 1; i <= n; i++){
		int idx = grank(w[i]);
		dp[i] = min((ll)w[i] - QUERY(1, 1, idx), QUERY(0, idx + 1, rsz) - w[i]);

		// range update for ahead values (for previous)
		int cahead = abs(w[i] - v[i + 1]);
		UPDRANGE(0, 1, rsz, cahead);
		UPDRANGE(1, 1, rsz, -cahead);

		// update segtrees with dp[i]
		crank = grank(v[i + 1]);
		UPDX(0, crank, dp[i] + v[i + 1]);
		UPDX(1, crank, -dp[i] + v[i + 1]);
	}

	printf("%lld\n", dp[n]);
}