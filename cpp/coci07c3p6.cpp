//============================================================================
// Name        : coci07c3p6.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 250001, SQM = (int)sqrt(MAX) + 10;
int n, m, ba, bb,
	blockn[MAX], arr[MAX],
	leftb[SQM], rightb[SQM], delta[SQM], block[10][SQM],
	buf[10];
string bufs;

inline void fixblock(int id){
	if(id < 0 || id > n || delta[id] == 0) return;

	for(int i = leftb[id]; i <= rightb[id]; i++)
		arr[i] = (arr[i] + delta[id]) % 10;

	delta[id] = 0;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m >> bufs;
	bufs = " " + bufs;

	int sqn = sqrt(n);
	memset(leftb, 0x3f, sizeof leftb);
	for (int i = 1; i <= n; ++i) {
		blockn[i] = i / sqn;
		leftb[blockn[i]] = min(leftb[blockn[i]], i);
		rightb[blockn[i]] = max(rightb[blockn[i]], i);

		int val = bufs[i] - '0';
		arr[i] = val;
		block[val][blockn[i]]++;
	}
	blockn[0] = -1;
	blockn[n + 1] = 0x3f3f3f3f;

	for (int i = 0; i < m; ++i) {
		cin >> ba >> bb;

		int lhs = blockn[ba] + 1, rhs = blockn[bb] - 1,
				tot = 0;

		fixblock(lhs - 1);
		fixblock(rhs + 1);

		for(int j = ba; blockn[j] < lhs && j <= bb; j++){
			tot += arr[j];
			int nextv = (arr[j] + 1) % 10;
			block[arr[j]][blockn[j]]--;
			block[nextv][blockn[j]]++;
			arr[j] = nextv;
		}
		for(int j = lhs; j <= rhs; j++){
			for(int k = 0; k < 10; k++)
				tot += block[k][j] * k, buf[k] = block[k][j];
			for(int k = 0; k < 10; k++)
				block[(k + 1) % 10][j] = buf[k];
			delta[j]++;
		}
		if(lhs <= rhs + 1){
			for(int j = bb; blockn[j] > rhs; j--){
				tot += arr[j];
				int nextv = (arr[j] + 1) % 10;
				block[arr[j]][blockn[j]]--;
				block[nextv][blockn[j]]++;
				arr[j] = nextv;
			}
		}

		printf("%d\n", tot);
	}
}