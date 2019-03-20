//============================================================================
// Name        : cco14p5.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 100001, MM = 600001;
int n, m, frontCnt = 0, backCnt = 0,
	tree[MAX];
ll a, b, minTot = 0, best = 0x3f3f3f3f3f3f3f3f, aux = 0,
	frontBest[MM], backBest[MM];
string buf;
bool hasWriter[MAX][6];

inline void add(int x, int v){
	for(; x <= n; x += x & -x)
		tree[x] += v;
}

inline int sum(int x){
	int sum = 0;
	for(; x; x -= x & -x)
		sum += tree[x];
	return sum;
}

// sumBelow(x) = 1 + 2 + 3 + ... + (x - 1)
inline ll sumBelow(ll x){
	if(x == 0) return 0;
	return (x * (x - 1)) >> 1;
}

// currFrontCnt -> Amount of people going to front room
inline ll sim(int currFrontCnt){
	ll ctot = minTot;

	if(currFrontCnt < frontCnt){ // Swap stuff going to the front, also diff > 0
		int diff = frontCnt - currFrontCnt;
		ctot += frontBest[diff - 1];
	}
	else{ // Swap stuff going to the back, diff >= 0
		int diff = currFrontCnt - frontCnt;
		ctot += diff > 0 ? backBest[diff - 1] : 0;
	}

	return ctot * a + (sumBelow(currFrontCnt) + sumBelow(m - currFrontCnt)) * b;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> m >> a >> b;

	for(int i = 1; i <= n; i++)
		add(i, 2);
	memset(hasWriter, true, sizeof hasWriter);

	for(int i = 0; i < m; i++){
		cin >> buf;
		int bl = buf.length(), row = stoi(buf.substr(0, bl - 1)), col = buf[bl - 1] - 'A';

		// Setting auxillary tot
		ll ctot = 0;

		if(col < 3)
			for(int j = col + 1; j <= 3; j++)
				ctot += hasWriter[row][j];
		else
			for(int j = col - 1; j >= 2; j--)
				ctot += hasWriter[row][j];
		hasWriter[row][col] = false;

		aux += ctot;

		// Figuring out which side is best (front or back)
		int front = sum(row - 1), back = sum(n) - sum(row), diff = abs(front - back);
		if(front < back){
			frontBest[frontCnt++] = diff;
			minTot += front;
		}
		else{
			backBest[backCnt++] = diff;
			minTot += back;
		}

		if(col == 2 || col == 3)
			add(row, -1);
	}

	// Sort and setup pfx sum array
	sort(frontBest, frontBest + frontCnt);
	sort(backBest, backBest + backCnt);

	for(int i = 1; i < frontCnt; i++)
		frontBest[i] += frontBest[i - 1];
	for(int i = 1; i < backCnt; i++)
		backBest[i] += backBest[i - 1];

	// find best
	for(int i = 0; i <= m; i++)
		best = min(best, sim(i));

	printf("%lld\n", best + aux * a);
}