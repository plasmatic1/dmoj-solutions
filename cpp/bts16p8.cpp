//============================================================================
// Name        : Textbooks.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAXN = 500001, MAX = (MAXN << 1) + 2;
const ll MOD = 1000000007;
int n, bl,
	l[MAXN], r[MAXN], w[MAXN], counttree[MAX * 4], totallazyp[MAX * 8], pfx[MAX];
ll tot = 0;
vector<int> ranks;

inline int rankof(int v){
	return lower_bound(ranks.begin(), ranks.end(), v) - ranks.begin();
}

inline void resolve_lazy(int i){
	if(totallazyp[i]){
		counttree[i] = max(counttree[i], totallazyp[i]);

		totallazyp[i << 1] = totallazyp[i];
		totallazyp[i << 1 | 1] = totallazyp[i];
		totallazyp[i] = 0;
	}
}

int totalquery(int i, int bl, int br, int ql, int qr){
	resolve_lazy(i);

	if(br < ql || bl > qr){
		return INT_MIN;
	}

	if(bl >= ql && br <= qr){
		return counttree[i];
	}

	int mid = (bl + br) / 2;

	return max(totalquery(i << 1, bl, mid, ql, qr),
			totalquery(i << 1 | 1, mid + 1, br, ql, qr));
}

int totalupdate(int i, int bl, int br, int ql, int qr, int v){
	resolve_lazy(i);

	if(br < ql || bl > qr){
		return counttree[i];
	}

	if(bl >= ql && br <= qr){
		totallazyp[i << 1] = v;
		totallazyp[i << 1 | 1] = v;

		return counttree[i] = max(counttree[i], v);
	}

	int mid = (bl + br) / 2;

	return counttree[i] = max(totalupdate(i << 1, bl, mid, ql, qr, v),
			totalupdate(i << 1 | 1, mid + 1, br, ql, qr, v));
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	set<int> tmp;
	tmp.insert(-1);

	for (int i = 0; i < n; ++i) {
		cin >> l[i] >> bl >> w[i];
		r[i] = l[i] + bl;
		tmp.insert(l[i]);
		tmp.insert(r[i]);
	}

	ranks = vector<int>(tmp.begin(), tmp.end());

	for (int i = 0; i < n; ++i) {
		l[i] = rankof(l[i]);
		r[i] = rankof(r[i]);
	}

	for (int i = 0; i < n; ++i) {
		int yval = totalquery(1, 1, MAX, l[i], r[i] - 1) + w[i];

//		printf("textbook idx=%d got yval=%d\n", i, yval);

		pfx[l[i]] += w[i];
		pfx[r[i]] -= w[i];

		totalupdate(1, 1, MAX, l[i], r[i] - 1, yval);
	}

	int rx = ranks.size() - 1;
	for (int i = 1; i < rx; ++i) {
		pfx[i] += pfx[i - 1];

//		printf("i=%d query res=%d pfx[i]=%d from x=%d->%d\n", i, query(1, 1, MAX, i, i), pfx[i], ranks[i], ranks[i + 1]);

		tot += (ll)(totalquery(1, 1, MAX, i, i) - pfx[i]) * (ll)(ranks[i + 1] - ranks[i]);
		tot %= MOD;
	}

	printf("%lld\n", tot);
}
