//============================================================================
// Name        : TinCanTelephone.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

struct line{
	double m, b, x1, y1, x2, y2;
	bool v;
};

const int MAX = 100;
int n, bn, ba, bb, bc, bd,
	tot = 0;
line base;
vector<line> polys[MAX];

line setline(double x1, double y1, double x2, double y2){
	double dx = x2 - x1, dy = y2 - y1;

	if(dx == 0) // Vertical
		return {-1, x1, x1, y1, x2, y2, true};
	double m = dy / dx;
	return {m, y1 - m * x1, x1, y1, x2, y2, false};
}

inline bool between(double l, double r, double x){
	return x >= min(l, r) && x <= max(l, r);
}

inline bool intersection(line a, line b){
	if(a.v) swap(a, b);
	if(b.v){
		double intery = a.m * b.b + a.b;
		return between(a.x1, a.x2, b.b) && between(b.y1, b.y2, intery);
	}
	else{
		double interx = -(a.b - b.b) / (a.m - b.m);
		return between(a.x1, a.x2, interx) && between(b.x1, b.x2, interx);
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> ba >> bb >> bc >> bd >> n;
	base = setline(ba, bb, bc, bd);

	for (int i = 0; i < n; ++i) {
		cin >> bn >> ba >> bb;
		int lastx = ba, lasty = bb, firstx = ba, firsty = bb;

		for (int j = 1; j < bn; ++j) {
			cin >> ba >> bb;

			polys[i].push_back(setline(lastx, lasty, ba, bb));

			lastx = ba;
			lasty = bb;
		}

		polys[i].push_back(setline(firstx, firsty, lastx, lasty));
	}

	for (int i = 0; i < n; ++i) {
		bool flag = false;

		for(line oth : polys[i]){
			if(base.v && oth.v){
				if(base.b == oth.b){
					double ymin = min(base.y1, base.y2), ymax = max(base.y1, base.y2),
							ymin2 = min(oth.y1, oth.y2), ymax2 = max(oth.y1, oth.y2);

					if(ymax >= ymin2 || ymax2 >= ymin) flag = true;
				}
			}
			else if(intersection(base, oth)) flag = true;

			if(flag) break;
		}

		tot += flag;
	}

	printf("%d\n", tot);
}
