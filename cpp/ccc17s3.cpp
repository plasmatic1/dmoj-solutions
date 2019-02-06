//============================================================================
// Name        : NailedIt.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 4001, MV = 2001;
int n, buf, board[MV], sums[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> buf;
		board[buf]++;
	}

	for(int i = 1; i < MV; i++)
		sums[i << 1] += board[i] / 2;

	for(int i = 1; i < MV; i++)
		for(int j = i + 1; j < MV; j++)
			sums[i + j] += min(board[i], board[j]);

	int best = -1, bestcnt = 0;

	for(int i = 1; i < MAX; i++){
		if(sums[i] > best){
			best = sums[i];
			bestcnt = 1;
		}
		else if(sums[i] == best)
			bestcnt++;
	}

	printf("%d %d\n", best, bestcnt);
}
