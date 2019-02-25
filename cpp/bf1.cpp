//============================================================================
// Name        : ListMinimum.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cstdio>
#include <algorithm>

using namespace std;

int n, a[1000];

int main() {
	scanf("%d", &n);

	for (int i = 0; i < n; ++i) {
		int o;
		scanf("%d", &o);
		a[i] = o;
	}

	sort(a, a + n);

	for (int i = 0; i < n; ++i) {
		printf("%d\n", a[i]);
	}

	return 0;
}