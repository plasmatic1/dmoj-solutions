//============================================================================
// Name        : RogersStarMap.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

int n, buf;

const int MAX = 32002;
unordered_map<int, int> counttree[MAX];

int levels[MAX], ba, bb;
vector<p> stars;

void add(int x, int y, int z){ // Adds `z` to index `(x, y)`
	for(int cx = x; cx <= 32001; cx += cx & -cx){
		for(int cy = y; cy <= 32001; cy += cy & -cy){
			counttree[cx][cy] += z;
		}
	}
}

int sum(int x, int y){ // Querys index `(x, y)`
	int summ = 0;

	for(int cx = x; cx > 0; cx -= cx & -cx){
		for(int cy = y; cy > 0; cy -= cy & -cy){
			summ += counttree[cx][cy];
		}
	}

	return summ;
}

// I ain't explaining how a fenwick tree works

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> ba >> bb;
		ba++;
		bb++;

		stars.emplace_back(ba, bb);
		add(ba, bb, 1);
	}

	for (int i = 0; i < n; ++i) {
//		printf("for %d,%d %d\n", stars[i].first, stars[i].second, sum(stars[i].first, stars[i].second));
		levels[sum(stars[i].first, stars[i].second) - 1]++;
	}

	for (int i = 0; i < n; ++i) {
		printf("%d\n", levels[i]);
	}
}
