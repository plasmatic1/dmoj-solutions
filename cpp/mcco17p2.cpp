//============================================================================
// Name        : PenetratingPower.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 200001;
int n, k, q, bi, ba, bb;
ll counttree[MAX * 6], totallazyp[MAX * 12]; // Large arbitrary coefficients to account for O(nlogn) size

inline void resolve_lazy(int i){
	if(totallazyp[i]){
		counttree[i] += totallazyp[i];

		totallazyp[i << 1] += totallazyp[i];
		totallazyp[i << 1 | 1] += totallazyp[i];
		totallazyp[i] = 0;
	}
}

ll totalquery(int i, int bl, int br, int ql, int qr){
	resolve_lazy(i);

	if(ql > qr){
		return INT_MIN;
	}

	if(bl == ql && br == qr){
		return counttree[i];
	}

	int mid = (bl + br) / 2;

	ll qval = max(totalquery(i << 1, bl, mid, ql, min(qr, mid)),
			totalquery(i << 1 | 1, mid + 1, br, max(ql, mid + 1), qr));

	return qval;
}

ll update(int i, int bl, int br, int ql, int qr, ll v){
	resolve_lazy(i);

	if(ql > qr){
		return counttree[i];
	}

	if(bl == ql && br == qr){
		totallazyp[i << 1] += v;
		totallazyp[i << 1 | 1] += v;

		return counttree[i] += v;
	}

	int mid = (bl + br) / 2;

	return counttree[i] = max(update(i << 1, bl, mid, ql, min(qr, mid), v),
			update(i << 1 | 1, mid + 1, br, max(ql, mid + 1), qr, v));
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> k >> q;

	for (int i = 0; i < q; ++i) {
		cin >> bi >> ba >> bb;
		ba++;

		if(bi == 0){
			update(1, 1, n, max(1, ba - k + 1), ba, bb);
		}
		else{ // bi == 1
			bb++;
			printf("%lld\n", totalquery(1, 1, n, ba, min(bb, n)));
		}
	}
}
