//============================================================================
// Name        : Raytracing.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 8193;
int n, q, ins, bi, bj, ba, bb,
	totaltree[MAX][MAX], lens[MAX];

void addd(int x, int y, int z){
	for(int cx = x; cx <= n; cx += cx & -cx){
		for(int cy = y; cy <= n; cy += cy & -cy){
			totaltree[cx][cy] += z;
		}
	}
}

int summ(int x, int y){
	int summ = 0;

	for(int cx = x; cx > 0; cx -= cx & -cx){
		for(int cy = y; cy > 0; cy -= cy & -cy){
			summ += totaltree[cx][cy];
		}
	}

	return summ;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 1; i <= n; ++i) {
		cin >> bi;
		bi++;

		addd(i, bi, 1);
		lens[i] = bi;
	}

	cin >> q;

	for (int i = 0; i < q; ++i) {
		cin >> ins >> bi >> bj;
		bi++;
		bj++;

		if(ins == 1){
			cin >> ba >> bb;
			//bi to bj, ba to bb
			//bi, ba to bj, bb
			ba++;
			bb++;

//			printf("x2,y2=%d, x1-1,y1-1=%d, x1-1,y2=%d, x2,")

			printf("%d\n", summ(bj, bb) + summ(bi - 1, ba - 1) - summ(bi - 1, bb) - summ(bj, ba - 1));
		}
		else{
			addd(bi, lens[bi], -1);
			lens[bi] = bj;
			addd(bi, bj, 1);
		}
	}
}
