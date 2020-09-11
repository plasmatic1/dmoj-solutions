//============================================================================
// Name        : LaserGrid.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

int x, y, n, m, c, ba, bb,
	xmin = INT_MIN, ymin = INT_MIN, xmax = INT_MAX, ymax = INT_MAX;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> x >> y >> n >> m >> c;

	for (int i = 0; i < n; ++i) {
		cin >> ba;

		if(ba < x && ba > xmin){
			xmin = ba;
		}

		if(ba > x && ba < xmax){
			xmax = ba;
		}
	}

	for (int i = 0; i < m; ++i) {
		cin >> ba;

		if(ba < y && ba > ymin){
			ymin = ba;
		}

		if(ba > y && ba < ymax){
			ymax = ba;
		}
	}

	for (int i = 0; i < c; ++i) {
		cin >> ba >> bb;

		if(ba >= xmin && ba <= xmax && bb >= ymin && bb <= ymax){
			printf("Y\n");
		}
		else{
			printf("N\n");
		}
	}
}
