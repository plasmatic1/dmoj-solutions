//============================================================================
// Name        : TinCanTelephone.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct ln{
	double m, b, x1, y1, x2, y2;
	bool vert;
};

struct p{
	double x, y;

	p(double x0, double y0) : x(x0), y(y0){}
	p() : x(-1), y(-1){}
};

const int MAX = 101, MV = 32;
int n, be, total = 0;
double ba, bb, bc, bd, minx, maxx;
vector<ln> builds[MAX];
ln mainln;
p pts[32];

inline void set_line(double ba, double bb, double bc, double bd, ln &line){
	double m = (bd - bb) / (bc - ba);

	if(ba == bc){
		line = {m, ba, ba, bb, bc, bd, true};
	}
	else{
		line = {m, bb - (m * ba), ba, bb, bc, bd, false};
	}
}

const double NOT_EXIST = numeric_limits<double>::max();
inline pair<double, bool> intersection(ln a, ln b){
	if(a.vert && b.vert){
		if(a.x1 == b.x1){
			double miny1 = min(a.y1, a.y2), maxy1 = max(a.y1, a.y2), miny2 = min(b.y1, b.y2), maxy2 = max(b.y1, b.y2);
			return make_pair(a.x1, max(miny1, miny2) <= min(maxy1, maxy2));
		}

		return make_pair(NOT_EXIST, false);
	}

	if(a.vert){
		swap(a, b);
	}

	if(b.vert){
		double yfor = a.m * b.x1 + a.b;
		return make_pair(b.x1, yfor >= min(b.y1, b.y2) && yfor <= max(b.y1, b.y2));
	}

	double nm = a.m - b.m, nb = a.b - b.b;

	if(nm == 0){
		return make_pair(NOT_EXIST, false);
	}

	return make_pair(-nb / nm, true);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> ba >> bb >> bc >> bd >> n;

	set_line(ba, bb, bc, bd, mainln);
	minx = min(ba, bc);
	maxx = max(ba, bc);

	// Making lines
	for (int i = 0; i < n; ++i) {
		cin >> be;

		for (int j = 0; j < be; ++j) {
			cin >> ba >> bb;
			pts[j] = p(ba, bb);
		}

		for (int j = 0; j < be - 1; ++j) {
			ln tmp;
			set_line(pts[j].x, pts[j].y, pts[j + 1].x, pts[j + 1].y, tmp);
			builds[i].push_back(tmp);
		}

		ln tmp;
		set_line(pts[be - 1].x, pts[be - 1].y, pts[0].x, pts[0].y, tmp);
		builds[i].push_back(tmp);
	}

	// Getting intersections
	for (int i = 0; i < n; ++i) {
		bool pass = false;

		for(ln line : builds[i]){
			double bl = max(minx, min(line.x1, line.x2)), br = min(maxx, max(line.x1, line.x2));

			pair<double, bool> intersect = intersection(mainln, line);
			if(intersect.second && intersect.first >= bl && intersect.first <= br){
				pass = true;
				break;
			}
		}

		total += pass;
	}

	// Output
	printf("%d\n", total);
}
