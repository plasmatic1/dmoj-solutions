//============================================================================
// Name        : LeiLeiAndDragonScales.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 251;
int w, h, n, maxv = 0,
	arr[MAX][MAX], pfx[MAX][MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> w >> h >> n;

	for (int i = 1; i <= h; ++i) {
		for (int j = 1; j <= w; ++j) {
			cin >> arr[j][i];
		}
	}

	// PFX Sum Array

	for (int i = 1; i <= w; ++i) {
		for (int j = 1; j <= h; ++j) {
			pfx[i][j] = arr[i][j] + pfx[i - 1][j] + pfx[i][j - 1] - pfx[i - 1][j - 1];
		}
	}

	// Calculations

	int mw = min(w, n);
	for (int cw = 1; cw <= mw; ++cw) {
		int ch = min(h, (n / cw));

		for (int i = 1; i <= w - cw + 1; ++i) {
			for (int j = 1; j <= h - ch + 1; ++j) {
				int i2 = i + cw - 1, j2 = j + ch - 1;
				maxv = max(maxv, pfx[i2][j2] - pfx[i - 1][j2] - pfx[i2][j - 1] + pfx[i - 1][j - 1]);
			}
		}
	}

	// Output

	printf("%d\n", maxv);
}
