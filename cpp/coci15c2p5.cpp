//============================================================================
// Name        : coci15c2p5.cpp
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

const int MAX = 1000001;
int n, p, rSz = 0,
	tree[MAX << 1];
ll tot = 0,
	pfx[MAX], sumOf[MAX];
vector<ll> ranks_;

void add(int x, int v) {
	x = rSz - x + 1;
	for (; x <= rSz; x += x & -x)
		tree[x] += v;
}

int sum(int x) {
	x = rSz - x + 1;
	int sum = 0;
	for (; x; x -= x & -x)
		sum += tree[x];
	return sum;
}

int rankOf(ll x) {
	return upper_bound(ranks_.begin(), ranks_.end(), x) - ranks_.begin();
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	scan(n);

	for (int i = 1; i <= n; i++) {
		scan(pfx[i]);
		pfx[i] += pfx[i - 1];
	}

	scan(p);

	// Coords compress
	ll cur = 0;
	for (int i = 1; i <= n; i++) {
		ranks_.push_back(sumOf[i] = pfx[i] - (ll)p * i);
		ranks_.push_back(cur);
		cur += pfx[i] - pfx[i - 1] - p;
	}
	sort(ranks_.begin(), ranks_.end());
	ranks_.resize(unique(ranks_.begin(), ranks_.end()) - ranks_.begin());
	rSz = ranks_.size();

	// Bit stuff with averages
	for (int i = 1; i <= n; i++)
		add(rankOf(sumOf[i]), 1);

	cur = 0;
	for (int i = 1; i <= n; i++) {
		tot += sum(rankOf(cur));
		add(rankOf(sumOf[i]), -1);
		cur += pfx[i] - pfx[i - 1] - p;
	}

	printf("%lld\n", tot);

	return 0;
}
