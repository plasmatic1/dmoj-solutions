//============================================================================
// Name        : PusheensPuzzlePresent.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 1001;
int n, buf, minv = INT_MAX, maxv = INT_MIN,
	reff[MAX][MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	int cur = 1;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			reff[i][j] = cur++;
		}
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> buf;
//			printf("i=%d j=%d buf=%d ref=%d\n", i, j, buf, reff[i][j]);
			if(buf != reff[i][j]){
				minv = min(minv, i);
				maxv = max(maxv, i);
			}
		}
	}

	printf("%d\n", maxv - minv + 1);
}
