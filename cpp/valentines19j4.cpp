//============================================================================
// Name        : valentines19j4.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 301;
int n, m, ba, bb, best = INT_MIN,
		a[MAX], b[MAX];
bool bad[MAX][MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	for(int i = 0; i < n; i++)
		cin >> a[i] >> b[i];

	for (int i = 0; i < m; ++i) {
		cin >> ba >> bb;
		ba--;
		bb--;
		bad[ba][bb] = bad[bb][ba] = true;
	}

	for (int i = 0; i < n; ++i) {
		best = max(best, b[i]);

		if(n < 2) continue;
		for (int j = 0; j < n; ++j) {
			if(i == j || bad[i][j]) continue;

			best = max(best, b[i] * a[j] + b[j]);

			if(n < 3) continue;
			for (int k = 0; k < n; ++k) {
				if(j == k || i == k || bad[j][k] || bad[i][k]) continue;

				best = max(best, (b[i] * a[j] + b[j]) * a[k] + b[k]);
			}
		}
	}

	printf("%d\n", best);
}
