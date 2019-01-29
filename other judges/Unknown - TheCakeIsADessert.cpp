//============================================================================
// Name        : TheCakeIsADessert.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

const int MAX = 5002;
int n, m, k, q, cake[MAX][MAX], interm[MAX][MAX], cakef[MAX][MAX];

void pfx(int begin[][MAX]){
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			begin[i][j] += begin[i - 1][j] + begin[i][j - 1] - begin[i - 1][j - 1];
		}
	}
}

int main() {
	scanf("%d %d %d", &n, &m, &k);

	for (int i = 0; i < n; ++i) {
		fill(cake[i], cake[i] + m, 0);
	}

	for (int i = 0; i < k; ++i) {
		int a, c, b, d;
		scanf("%d %d %d %d", &a, &b, &c, &d);

		cake[a][b]++;
		cake[c][b]--;
		cake[a][d]--;
		cake[c][d]++;
	}

	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= m; ++j) {
			printf("%d ", cake[i][j]);
		}
		printf("\n");
	}

	printf("-\n");
	pfx(cake);

	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= m; ++j) {
			printf("%d ", cake[i][j]);
		}
		printf("\n");
	}

	printf("-\n");
	pfx(cake);

	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= m; ++j) {
			printf("%d ", cake[i][j]);
		}
		printf("\n");
	}

	scanf("%d", &q);

	for (int i = 0; i < q; ++i) {
		int a, c, b, d;
		scanf("%d %d %d %d", &a, &b, &c, &d);

		printf("%d\n", cake[c][d] - cake[a][d] - cake[b][c] + cake[a][b]);
	}

	return 0;
}
