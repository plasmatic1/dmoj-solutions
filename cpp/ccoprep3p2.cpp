//============================================================================
// Name        : ccoprep3p2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct p{
	int i, dpi;

	bool operator<(const p &o) const {
		return i < o.i;
	}
};

const int MAX = 2000001;
int n, l;
ll pfx[MAX], dp[MAX];
vector<p> best;

inline ll dpFrom(int from, int to){
	ll diff = (ll)to - from - 1 + pfx[to] - pfx[from] - l, tot = dp[from] + diff * diff;
	return tot >= 0 ? tot : LLONG_MAX; // Hacky overflow fix
}

inline int bestAt(int idx){
	p tmp = {idx, -1};
	return (upper_bound(best.begin(), best.end(), tmp) - 1)->dpi;
}

#define TOP() (*(best.end() - 1))
#define POP() (best.erase(best.end() - 1))

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> l;

	for(int i = 1; i <= n; i++)
		cin >> pfx[i], pfx[i] += pfx[i - 1];

	dp[0] = 0;
	best.push_back({0, 0});
	for(int i = 1; i <= n; i++){
		dp[i] = dpFrom(bestAt(i), i);

		p top = TOP();
		while(top.i > i && dpFrom(i, top.i) <= dpFrom(top.dpi, top.i)){
			POP();
			top = TOP();
		}

		int l = i, r = n;
		while(l + 1 < r){
			int mid = (l + r) >> 1;

			if(dpFrom(i, mid) <= dpFrom(top.dpi, mid))
				r = mid;
			else
				l = mid;
		}

		if(dpFrom(i, n) <= dpFrom(top.dpi, n))
			best.push_back({r, i});
	}

	printf("%lld\n", dp[n]);
}