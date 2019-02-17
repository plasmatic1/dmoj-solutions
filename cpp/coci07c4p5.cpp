//============================================================================
// Name        : coci07c4p5.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct p{
	int a, b;

	bool operator<(const p &o) const {
		if(a == o.a)
			return b > o.b;
		return a < o.a;
	}
};

const int MAX = 100001, MV = 1000001;
int n, maxb = INT_MIN,
	dp[MAX], tree[MV << 2];
p ranges[MAX];

int query(int i, int l, int r, int ql, int qr){
	if(l > qr || r < ql) return INT_MIN;
	if(l >= ql && r <= qr) return tree[i];

	int mid = (l + r) / 2;
	return max(query(i << 1, l, mid, ql, qr), query(i << 1 | 1, mid + 1, r, ql, qr));
}

int update(int i, int l, int r, int q, int v){
	if(l > q || r < q) return tree[i];
	if(l == q && r == q) return tree[i] = v;

	int mid = (l + r) / 2;
	return tree[i] = max(update(i << 1, l, mid, q, v), update(i << 1 | 1, mid + 1, r, q, v));
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n;

	for(int i = 0; i < n; i++){
		cin >> ranges[i].a >> ranges[i].b;
		maxb = max(maxb, ranges[i].b);
	}
	sort(ranges, ranges + n);

	for (int i = 0; i < n; ++i) {
		dp[i] = query(1, 1, maxb, ranges[i].b, maxb) + 1;
		update(1, 1, maxb, ranges[i].b, dp[i]);
	}

	int best = -1, besti = -1;
	for (int i = 0; i < n; ++i) {
		if(dp[i] > best){
			best = dp[i];
			besti = i;
		}
	}

	vector<p> ret;
	int lookforDPV = 1, lookforR = 1;
	for(int i = besti; i >= 0; ){
		ret.push_back({ranges[i].a, ranges[i].b});
		lookforDPV = dp[i] - 1;
		lookforR = ranges[i].b;

		while(i >= 0 && (dp[i] != lookforDPV || ranges[i].b < lookforR))
			i--;
	}
	reverse(ret.begin(), ret.end());

	printf("%d\n", best);
	for(p pp : ret)
		printf("%d %d\n", pp.a, pp.b);
}