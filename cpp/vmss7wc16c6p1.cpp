//============================================================================
// Name        : vmss7wc16c6p1.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 101;
int n, tot = 0,
		x[MAX], y[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 0; i < n; ++i)
		cin >> x[i] >> y[i];

	for (int i = 0; i < n; ++i)
		tot += x[i] * y[(i + 1) % n] - x[(i + 1) % n] * y[i];

	printf("%d\n", (int)ceil(abs(tot) / 2.));
}
