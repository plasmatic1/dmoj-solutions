//============================================================================
// Name        : GrowingTrees.cpp
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
int n, minv = INT_MAX,
	h[MAX], g[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> h[i] >> g[i];
	}

	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			int ha = h[i], hb = h[j], ga = g[i], gb = g[j];

			if(ha == hb){
				printf("0\n");
				return 0;
			}

			if(ha > hb){
				swap(ha, hb);
				swap(ga, gb);
			}

			int growdiff = ga - gb;

//			printf("tree i=%d j=%d diff=%d\n", i, j, growdiff);

			if(growdiff <= 0){
				continue;
			}

			if((hb - ha) % growdiff == 0){
				minv = min(minv, (hb - ha) / growdiff);
			}
		}
	}

	if(minv == INT_MAX){
		printf("-1\n");
	}
	else{
		printf("%d\n", minv);
	}
}
