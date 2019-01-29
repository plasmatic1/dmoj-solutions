//============================================================================
// Name        : ZombieApocalypse.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct zomb{
	int x1, y1, x2, y2;
};

struct p{
	int x, y;
};

const int MAX = 2001, PMAX = 4011;
int n, m, k, q, ba, bb;
ll tot1 = 0, tot2 = 0;
p loc[MAX];
short pfx[PMAX][PMAX];
zomb zombs[MAX];

inline int rankof(vector<int> &vec, int v){
	return lower_bound(vec.begin(), vec.end(), v) - vec.begin();
}

ll run(int diff){
	for (int i = 0; i < k; ++i) {
		zombs[i] = {max(1, loc[i].x - diff), max(1, loc[i].y - diff), min(n, loc[i].x + diff) + 1, min(m, loc[i].y + diff) + 1};
	}

	// Coordinate Compression stuff

	set<int> tmpx, tmpy;
	vector<int> rankx, ranky;

	tmpx.insert(0);
	tmpy.insert(0);

	for (int i = 0; i < k; ++i) {
		tmpx.insert(zombs[i].x1);
		tmpx.insert(zombs[i].x2);

		tmpy.insert(zombs[i].y1);
		tmpy.insert(zombs[i].y2);
	}

	rankx = vector<int>(tmpx.begin(), tmpx.end());
	ranky = vector<int>(tmpy.begin(), tmpy.end());

	int rx = rankx.size(), ry = ranky.size();

	for (int i = 0; i < k; ++i) {
		zombs[i].x1 = rankof(rankx, zombs[i].x1);
		zombs[i].x2 = rankof(rankx, zombs[i].x2);
		zombs[i].y1 = rankof(ranky, zombs[i].y1);
		zombs[i].y2 = rankof(ranky, zombs[i].y2);
	}

	// Sum Array Building

	ll tot = 0;
	memset(pfx, 0, sizeof(pfx));

	for (int i = 0; i < k; ++i) {
		zomb z = zombs[i];

		pfx[z.x1][z.y1]++;
		pfx[z.x1][z.y2]--;
		pfx[z.x2][z.y1]--;
		pfx[z.x2][z.y2]++;
	}

	for (int i = 1; i <= rx; ++i) {
		for (int j = 1; j <= ry; ++j) {
			pfx[i][j] += pfx[i - 1][j] + pfx[i][j - 1] - pfx[i - 1][j - 1];
		}
	}

//	printf("pfx: [\n");
//	for(int i = 0; i < n + 1; i++){
//		printf("%d : ", i);
//		for(int j = 0; j < m + 1; j++){
//			printf("%d, ", pfx[i][j]);
//		}
//		printf("\n");
//	}
//	printf("]\n");

	for (int i = 1; i < rx - 1; ++i) {
		ll dx = rankx[i + 1] - rankx[i];

		for (int j = 1; j < ry - 1; ++j) {
			if(pfx[i][j] > 0){
				tot += (ll)(ranky[j + 1] - ranky[j]) * dx;
			}
		}
	}

	return tot;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m >> k;

	for (int i = 0; i < k; ++i) {
		cin >> loc[i].x >> loc[i].y;
	}

	cin >> q;

	if(q == 0){
		printf("%d\n", k);
		return 0;
	}

	// Output

	ll tot1 = run(q), tot2 = run(q - 1);
//	printf("large=%lld small=%lld\n", tot1, tot2);
	printf("%lld\n", tot1 - tot2);
}
