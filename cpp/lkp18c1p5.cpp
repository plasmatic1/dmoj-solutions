//============================================================================
// Name        : TreatyOfWellacotia.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 21, NMAX = 100001;
int n, m, k, bl, br, buf,
	counttree[MAX][NMAX * 6], totallazyp[MAX][NMAX * 12], currcounts[MAX];

// Segtree
inline void resolve_lazy(int cntry, int i, int bl, int br){
	if(totallazyp[cntry][i] != 0){
		counttree[cntry][i] = max(0, totallazyp[cntry][i] * (br - bl + 1));

		totallazyp[cntry][i << 1] = totallazyp[cntry][i];
		totallazyp[cntry][i << 1 | 1] = totallazyp[cntry][i];
		totallazyp[cntry][i] = 0;
	}
}

int query(int coun, int i, int bl, int br, int ql, int qr){
	resolve_lazy(coun, i, bl, br);

	if(ql > qr){
		return 0;
	}

	if(bl == ql && br == qr){
		return counttree[coun][i];
	}

	int mid = (bl + br) / 2;

	int qval = query(coun, i << 1, bl, mid, ql, min(qr, mid)) +
			query(coun, i << 1 | 1, mid + 1, br, max(ql, mid + 1), qr);

	return qval;
}

int update(int coun, int i, int bl, int br, int ql, int qr, int v){
	resolve_lazy(coun, i, bl, br);

	if(ql > qr){
		return counttree[coun][i];
	}

	if(bl == ql && br == qr){
		totallazyp[coun][i << 1] = v;
		totallazyp[coun][i << 1 | 1] = v;

		return counttree[coun][i] = max(0, v * (br - bl + 1));
	}

	int mid = (bl + br) / 2;

	return counttree[coun][i] = update(coun, i << 1, bl, mid, ql, min(qr, mid), v) +
			update(coun, i << 1 | 1, mid + 1, br, max(ql, mid + 1), qr, v);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m >> k;

	for (int i = 1; i <= n; ++i) {
		cin >> buf;

		update(buf, 1, 1, n, i, i, 1);
	}

	for (int i = 0; i < m; ++i) {
		cin >> bl >> br;

		for (int j = 1; j <= k; ++j) {
			currcounts[j] = query(j, 1, 1, n, bl, br);
			update(j, 1, 1, n, bl, br, -1);
		}

		int curr = bl;
		for (int j = 0; j < k; ++j) {
			cin >> buf;

			if(currcounts[buf] > 0){
				int next = curr + currcounts[buf] - 1;

				assert(next <= br);
				update(buf, 1, 1, n, curr, next, 1);

				curr = next + 1;
			}
		}
	}

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= k; ++j) {
			if(query(j, 1, 1, n, i, i)){
				printf("%d ", j);
				break;
			}
		}
	}

	printf("\n");
}

/*
5 2 3
3 3 2 2 1
1 4
1 2 3
1 4
1 2 3

2 2 3 3 1

5 1 3
1 1 1 1 1
1 5
2 3 1

1 1 1 1 1
 */
