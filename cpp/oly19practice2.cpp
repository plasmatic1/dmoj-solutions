//============================================================================
// Name        : BuildFences.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct p{
	int x, y;
};

bool cmpx(const p &a, const p &b){
	return a.x < b.x;
}

bool cmpy(const p &a, const p &b){
	return a.y < b.y;
}

const int MAX = 50001;
int n, xmin = INT_MAX, xmax = INT_MIN, ymin = INT_MAX, ymax = INT_MIN,
	minx[2][MAX], maxx[2][MAX],
	miny[2][MAX], maxy[2][MAX];
p pts[MAX];
ll perim = 0, minp = LLONG_MAX;

inline int rangex(int end, bool suffix){
	return maxx[suffix][end] - minx[suffix][end];
}

inline int rangey(int end, bool suffix){
	return maxy[suffix][end] - miny[suffix][end];
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> pts[i].x >> pts[i].y;

		xmin = min(xmin, pts[i].x);
		xmax = max(xmax, pts[i].x);
		ymin = min(ymin, pts[i].y);
		ymax = max(ymax, pts[i].y);
	}

	perim = (((ll)xmax - xmin) * ((ll)ymax - ymin));
	int nm = n - 1;

	// X-partition pass

	sort(pts, pts + n, cmpx);

	miny[0][0] = maxy[0][0] = pts[0].y;

	for (int i = 1; i < n; ++i) {
		miny[0][i] = min(miny[0][i - 1], pts[i].y);
		maxy[0][i] = max(maxy[0][i - 1], pts[i].y);
	}

	miny[1][n - 1] = maxy[1][n - 1] = pts[n - 1].y;

	for (int i = n - 2; i >= 0; --i) {
		miny[1][i] = min(miny[1][i + 1], pts[i].y);
		maxy[1][i] = max(maxy[1][i + 1], pts[i].y);
	}

	// get values

	deque<int> vals;

	for(int i = 0; i < nm; i++){
		if(!vals.empty() && pts[i].x == pts[vals.back()].x) vals.pop_back();
		vals.push_back(i);
	}

	//l oo p moth

	for(int i : vals){
		ll a1 = ((ll)pts[i].x - xmin) * rangey(i, 0), a2 = ((ll)xmax - pts[i + 1].x) * rangey(i + 1, 1);
		minp = min(minp, a1 + a2);
	}

	// Y partition pass

	sort(pts, pts + n, cmpy);

	minx[0][0] = maxx[0][0] = pts[0].x;

	for (int i = 1; i < n; ++i) {
		minx[0][i] = min(minx[0][i - 1], pts[i].x);
		maxx[0][i] = max(maxx[0][i - 1], pts[i].x);
	}

	minx[1][n - 1] = maxx[1][n - 1] = pts[n - 1].x;

	for (int i = n - 2; i >= 0; --i) {
		minx[1][i] = min(minx[1][i + 1], pts[i].x);
		maxx[1][i] = max(maxx[1][i + 1], pts[i].x);
	}

	// get values

	vals.clear();

	for(int i = 0; i < nm; i++){
		if(!vals.empty() && pts[i].y == pts[vals.back()].y) vals.pop_back();
		vals.push_back(i);
	}

	//l oo p moth

	for(int i : vals){
		ll a1 = ((ll)pts[i].y - ymin) * rangex(i, 0), a2 = ((ll)ymax - pts[i + 1].y) * rangex(i + 1, 1);
		minp = min(minp, a1 + a2);
	}

	// Output

	printf("%lld\n", perim - minp);
}
