//============================================================================
// Name        : Nered.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

struct p{
	int l, w;
};

const int MAX = 101, MAXF = 200;
int n, m, bx, by, pfx[MAX][MAX], fptr = 0;
p fact[MAXF];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> m;

	for (int i = 0; i < m; ++i) {
		cin >> bx >> by;
		pfx[bx][by] = 1;
	}

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			pfx[i][j] += pfx[i - 1][j] + pfx[i][j - 1] - pfx[i - 1][j - 1];
		}
	}

	for (int i = 1; i <= m; ++i) {
		if(m % i == 0){
			fact[fptr++] = {i, m / i};
		}
	}

//	printf("fact: [");
//	for(int i = 0; i < fptr; i++){
//		printf("(%d, %d), ", fact[i].l, fact[i].w);
//	}
//	printf("]\n");
//
//	printf("pfx: [\n");
//	for(int i = 0; i < n + 1; i++){
//		for(int j = 0; j < n + 1; j++){
//			printf("%d, ", pfx[i][j]);
//		}
//		printf("\n");
//	}
//	printf("]\n");

	int maxv = INT_MIN;
	for (int i = 0; i < fptr; ++i) {
		int maxx = n - fact[i].l + 1, maxy = n - fact[i].w + 1;
		for (int j = 1; j <= maxx; ++j) {
			for (int k = 1; k <= maxy; ++k) {
				int j2 = j + fact[i].l - 1, k2 = k + fact[i].w - 1;

				maxv = max(maxv, pfx[j2][k2] + pfx[j - 1][k - 1] - pfx[j - 1][k2] - pfx[j2][k - 1]);
			}
		}
	}

//	printf("maxv=%d\n", maxv);
	printf("%d\n", m - maxv);
}
