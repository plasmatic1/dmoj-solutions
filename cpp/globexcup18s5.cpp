//============================================================================
// Name        : MathBash.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 501, MV = 103;

struct q{
	int x, y, v;

	q(int x0, int y0, int v0) : x(x0), y(y0), v(v0){}
	q() : x(-1), y(-1), v(-1){}

	friend bool operator<(q &a, q &b){
		return a.v > b.v;
	}
};

int n, buf,
	counttree[MAX][MAX][MV];
ll tot = 0;
vector<q> values, queries;

void add(int x, int y, int z){
	for(int cx = x; cx <= n; cx += cx & -cx){
		for(int cy = y; cy <= n; cy += cy & -cy){
			for(int cz = z; cz < MV; cz += cz & -cz){
				counttree[cx][cy][cz]++;
			}
		}
	}
}

int sum(int x, int y, int z){
	int summ = 0;

	for(int cx = x; cx > 0; cx -= cx & -cx){
		for(int cy = y; cy > 0; cy -= cy & -cy){
			for(int cz = z; cz > 0; cz -= cz & -cz){
				summ += counttree[cx][cy][cz];
			}
		}
	}

	return summ;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> buf;
			int actual = buf;

			if(i > 1 && j > 1){
				int adjust = sum(i - 1, j - 1, MV) - sum(i - 1, j - 1, buf - 1);

				tot += adjust;
				actual += adjust;
			}

			add(i, j, min(101, actual));
		}
	}

	printf("%lld\n", tot);
}
