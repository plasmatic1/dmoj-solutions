//============================================================================
// Name        : RogersRangeSqrtUpdate.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 100001;
int n, m, bi, bl, br;

ll arr[MAX], counttree[MAX * 16];
bool done[MAX * 33];

ll build(int i, int l, int r){
	if(l == r){
		return counttree[i] = arr[l];
	}

	int mid = (l + r) / 2;

	return counttree[i] = build(i << 1, l, mid) + build(i << 1 | 1, mid + 1, r);
}

ll totalquery(int i, int bl, int br, int ql, int qr){
	if(ql > qr){
		return 0;
	}

	if(bl == ql && br == qr){
		return counttree[i];
	}

	int mid = (bl + br) / 2;

	return totalquery(i << 1, bl, mid, ql, min(qr, mid)) + totalquery(i << 1 | 1, mid + 1, br, max(ql, mid + 1), qr);
}

ll update(int i, int bl, int br, int ql, int qr){
	if(ql > qr){
		return counttree[i];
	}

//	if(done[i]){
//		return tree[i];
//	}

	if(bl == br){
		if(counttree[i] > 1){
			return counttree[i] = (ll)(sqrt(counttree[i]));
		}

		done[i] = true;
		return counttree[i];
	}

	int mid = (bl + br) / 2;

	counttree[i] = update(i << 1, bl, mid, ql, min(qr, mid)) +
				update(i << 1 | 1, mid + 1, br, max(ql, mid + 1), qr);
	done[i] = done[i << 1] && done[i << 1 | 1];

	return counttree[i];
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 1; i <= n; ++i) {
		cin >> arr[i];
	}

	build(1, 1, n);

	cin >> m;

	for (int i = 0; i < m; ++i) {
		cin >> bi >> bl >> br;

		if(bi == 1){
			printf("%lld\n", totalquery(1, 1, n, bl, br));
		}
		else{ // bi == 2 (update)
			update(1, 1, n, bl, br);
		}
	}
}
