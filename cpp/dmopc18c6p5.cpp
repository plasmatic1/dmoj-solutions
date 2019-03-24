//============================================================================
// Name        : dmopc18c6p5.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

struct p{
	// types:
	// 0 -> query add
	// 2 -> query sub
	// 1 -> duck
	// order by priority

	int type, i, x, bot, top;

	bool operator<(const p &o) const {
		if(x == o.x) return type < o.type;
		return x < o.x;
	}
};

struct duck{
	int x, y;
};

struct qu{
	int x1, y1, x2, y2;
};

typedef long long ll;

const int MAX = 100001, MT = 300001, MSEG = 1000001;
int n, m, k, q, t, iptr = 0, ctr = 0,
	tree[MSEG << 2], lazy[MSEG << 3], best[MAX];
unordered_map<int, int> ranks;
p items[MT];
duck ducks[MAX];
qu queries[MAX];

inline void updlazy(int i){
	if(lazy[i]){
		tree[i] += lazy[i];
		lazy[i << 1] += lazy[i];
		lazy[i << 1 | 1] += lazy[i];
		lazy[i] = 0;
	}
}

int query(int i, int l, int r, int ql, int qr){
	updlazy(i);
	if(l >= ql && r <= qr) return tree[i];
	if(l > qr || r < ql) return INT_MIN;

	int mid = (l + r) >> 1;
	return max(query(i << 1, l, mid, ql, qr), query(i << 1 | 1, mid + 1, r, ql, qr));
}

int update(int i, int l, int r, int ql, int qr, int v){
	updlazy(i);
	if(l >= ql && r <= qr){
		lazy[i] = v;
		updlazy(i);
		return tree[i];
	}
	if(l > qr || r < ql) return tree[i];

	int mid = (l + r) >> 1;
	return tree[i] = max(update(i << 1, l, mid, ql, qr, v), update(i << 1 | 1, mid + 1, r, ql, qr, v));
}

#define ALL 1, 1, ctr
inline void sweep(){
	for (int i = 0; i < iptr; ++i) {
		p item = items[i];
		item.bot = ranks[item.bot];
		item.top = ranks[item.top];

		if(item.type == 0)
			update(ALL, item.bot, item.top, 1);
		else if(item.type == 2)
			update(ALL, item.bot, item.top, -1);
		else // duck
			best[item.i] = max(best[item.i], query(ALL, item.bot, item.top));
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> m >> k >> q >> t;

	set<int> tmprank;
	for (int i = 0; i < k; ++i){
		cin >> ducks[i].x >> ducks[i].y;

		tmprank.insert(ducks[i].x);
		tmprank.insert(ducks[i].x - t);
		tmprank.insert(ducks[i].x + t);
		tmprank.insert(ducks[i].y);
		tmprank.insert(ducks[i].y - t);
		tmprank.insert(ducks[i].y + t);
	}

	for (int i = 0; i < q; ++i){
		cin >> queries[i].x1 >> queries[i].y1 >> queries[i].x2 >> queries[i].y2;

		tmprank.insert(queries[i].x1);
		tmprank.insert(queries[i].x2);
		tmprank.insert(queries[i].y1);
		tmprank.insert(queries[i].y2);
	}

	for(int x : tmprank)
		ranks[x] = ++ctr;

	// Setup first sweep (left - right)
	for (int i = 0; i < k; ++i)
		items[iptr++] = {1, i, ducks[i].x, ducks[i].y - t, ducks[i].y + t};
	for (int i = 0; i < q; i++){
		items[iptr++] = {0, i, queries[i].x1, queries[i].y1, queries[i].y2};
		items[iptr++] = {2, i, queries[i].x2, queries[i].y1, queries[i].y2};
	}
	sort(items, items + iptr);

	sweep();

	// Setup second sweep (bottom - top)
	iptr = 0;
	for (int i = 0; i < k; ++i)
		items[iptr++] = {1, i, ducks[i].y, ducks[i].x - t, ducks[i].x + t};
	for (int i = 0; i < q; i++){
		items[iptr++] = {0, i, queries[i].y1, queries[i].x1, queries[i].x2};
		items[iptr++] = {2, i, queries[i].y2, queries[i].x1, queries[i].x2};
	}
	sort(items, items + iptr);

	sweep();

	// Output
	ll tot = 0;
	for (int i = 0; i < k; i++)
		tot += best[i];
	printf("%lld\n", tot);
}