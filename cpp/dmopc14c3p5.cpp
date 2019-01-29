//============================================================================
// Name        : NotEnoughServers.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

struct pi{
	int parent, casen;
};

const int MAX = 20, MMAX = 50, DPM = 1 << 20;
int n, m,
	dp[DPM];
pi parents[DPM];

char grid[MAX][MMAX];

vector<int> cases;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	for (int i = 0; i < n; ++i) {
		cin >> grid[i];
	}

	memset(dp, 0x3f, sizeof(dp));
	dp[0] = 0;
	for (int i = 0; i < m; ++i) {
		int mask = 0;

		for (int j = 0; j < n; ++j) {
			if(grid[j][i] == 'X'){
				mask |= 1 << j;
			}
		}

		dp[mask] = mask > 0 ? 1 : 0;
		parents[mask] = {0, i};

		cases.push_back(mask);
	}

	int wamask = 0;
	for (int i = 0; i < n; ++i) {
		bool isWA = false;

		for (int j = 0; j < m; ++j) {
			if(grid[i][j] == 'X'){
				isWA = true;
				break;
			}
		}

		if(isWA){
			wamask |= 1 << i;
		}
	}

	//

	int maxsub = min(1 << n, wamask);
	for (int i = 0; i < maxsub; ++i) {
		for(int j = 0; j < cases.size(); j++){
			int casee = cases[j], alt = i | casee, altdpv = dp[i] + 1;
//			printf("i=%d, dpv=%d, case#=%d, dp[alt]=%d\n", i, altdpv, j, dp[alt]);

			if(altdpv < dp[alt]){
//				printf("on i=%d, adding for case # %d\n", i, j);

				dp[alt] = altdpv;
				parents[alt] = {i, j};
			}
		}
	}

	//

//	printf("dp: ");
//	for (int i = 0; i < n * 10; ++i) {
//		printf("(p=%d,c=%d), ", parents[i].parent, parents[i].casen);
//	}
//	printf("\n");

	if(wamask == 0){
		printf("1\n1\n");
	}
	else{
		printf("%d\n", dp[wamask]);

		set<int> casess;

		pi currparr = parents[wamask];
		while(currparr.parent != 0){
			casess.insert(currparr.casen);
			currparr = parents[currparr.parent];
		}
		casess.insert(currparr.casen);

		for(int c : casess){
			printf("%d ", c + 1);
		}
	}
}
