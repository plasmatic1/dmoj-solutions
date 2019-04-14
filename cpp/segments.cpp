//============================================================================
// Name        : segments.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Scan and Debug
void scan(){}
template<typename F, typename... R> void scan(F &f,R&... r){cin>>f;scan(r...);}
int di_; string dnms_, co_ = ",";
void debug_(){cout<<endl;}
template<typename F, typename... R> void debug_(F f, R... r){while(dnms_[di_] != ',')cout<<dnms_[di_++];di_++;cout<<": "<<f<<",";debug_(r...);}
#define debug(...) dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__)

struct p{
	int l, r;

	bool operator<(const p &o) const {
		if(l == o.l)
			return r < o.r;
		return l < o.l;
	}
};

const int MAX = 200001, MN = 100001;
int t, n, sz = 0,
	tree[2][MAX << 2], lazy[2][MAX << 3];
p segs[MN];

inline void updLazy(int id, int i){
	if(lazy[id][i]){
		tree[id][i] += lazy[id][i];
		lazy[id][i << 1] += lazy[id][i];
		lazy[id][i << 1 | 1] += lazy[id][i];
		lazy[id][i] = 0;
	}
}

int query(int id, int i, int l, int r, int ql, int qr){
	updLazy(id, i);
	if(l >= ql && r <= qr) return tree[id][i];
	if(r < ql || l > qr) return 0;

	int mid = (l + r) >> 1;
	return max(query(id, i << 1, l, mid, ql, qr), query(id, i << 1 | 1, mid + 1, r, ql, qr));
}

int update(int id, int i, int l, int r, int ql, int qr, int v){
	updLazy(id, i);
	if(l >= ql && r <= qr) {
		lazy[id][i] += v;
		return tree[id][i] + v;
	}
	if(r < ql || l > qr) return tree[id][i];

	int mid = (l + r) >> 1;
	return tree[id][i] = max(update(id, i << 1, l, mid, ql, qr, v), update(id, i << 1 | 1, mid + 1, r, ql, qr, v));
}

#define ALL(id) id, 1, 1, sz

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	scan(t);

	for (int tcn_ = 1; tcn_ <= t; ++tcn_) {
		scan(n);

		vector<int> ranks;
		for (int i = 0; i < n; ++i) {
			scan(segs[i].l, segs[i].r);
			ranks.push_back(segs[i].l);
			ranks.push_back(segs[i].r);
		}
		sort(ranks.begin(), ranks.end());
		ranks.resize(unique(ranks.begin(), ranks.end()) - ranks.begin());
		sort(segs, segs + n);

		sz = ranks.size();
		for (int i = 0; i < n; ++i){
			segs[i].l = lower_bound(ranks.begin(), ranks.end(), segs[i].l) - ranks.begin() + 1;
			segs[i].r = lower_bound(ranks.begin(), ranks.end(), segs[i].r) - ranks.begin() + 1;
		}

		for (int i = 0; i < n; ++i)
			update(ALL(1), segs[i].l, segs[i].r, 1);

		int best = query(ALL(1), 1, sz);
		for (int i = 0; i < n; ++i) {
			update(ALL(1), segs[i].l, segs[i].r, -1);
			update(ALL(0), segs[i].l, segs[i].r, 1);
			best = max(best, query(ALL(0), 1, sz) + query(ALL(1), 1, sz));
		}

		printf("Case %d: %d\n", tcn_, best);
		memset(tree, 0, sizeof tree);
		memset(lazy, 0, sizeof lazy);
	}
}