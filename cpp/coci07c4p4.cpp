//============================================================================
// Name        : Muzicari.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 501, MV = 5001;
int t, n, tot = 0,
	l[MAX], ans[MAX], par[MV], pari[MV];
bool dp[MV];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> t >> n;

	memset(par, -1, sizeof(par));
	dp[0] = true;

	for (int i = 1; i <= n; ++i) {
		cin >> l[i];
		tot += l[i];

		for (int j = MV - 1; j >= l[i]; --j) {
			if(dp[j]) continue;

			int bf = j - l[i];

			if(dp[bf]){
				dp[j] = true;
				par[j] = bf;
				pari[j] = i;
			}
		}
	}

	// Getting best

	int best = INT_MAX, besti = -1, h = tot / 2;

	for(int j = 0; j < MV; j++){
		if(dp[j]){
			int dif = abs(h - j);

			if(dif < best){
				best = dif;
				besti = j;
			}
		}
	}

	// Remaking Sequence

//	printf("besti=%d\n", besti);
//
//	printf("pari: ");
//	for (int i = 0; i < t +1; ++i) {
//		printf("%d, ", pari[i]);
//	}
//	printf("\n");
//	printf("par: ");
//	for (int i = 0; i < t+1; ++i) {
//		printf("%d, ", par[i]);
//	}
//	printf("\n");

	set<int> g1;
	while(besti != 0){
		g1.insert(pari[besti]);
		besti = par[besti];
	}

//	printf("g1: [");
//	for(int i : g1){
//		printf("%d, ", i);
//	}
//	printf("]\n");

	int cv = 0;
	for(int i : g1){
		ans[i] = cv;
		cv += l[i];
	}

	cv = 0;
	for(int i = 1; i <= n; i++){
		if(!g1.count(i)){
			ans[i] = cv;
			cv += l[i];
		}
	}

	// Output

	for(int i = 1; i <= n; i++){
		printf("%d ", ans[i]);
	}
	printf("\n");
}
