//============================================================================
// Name        : PumpkinPatches.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

int n, b1, b2;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	int minx = INT_MAX, miny = INT_MAX, maxx = INT_MIN, maxy = INT_MIN;

	for (int i = 0; i < n; ++i) {
		cin >> b1 >> b2;

		minx = min(minx, b1);
		miny = min(miny, b2);

		maxx = max(maxx, b1);
		maxy = max(maxy, b2);
	}

	int dx = maxx - minx, dy = maxy - miny;

	printf("%d\n", 2 * (dx + dy));
}
