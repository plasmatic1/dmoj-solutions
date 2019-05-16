//============================================================================
// Name        : ccc01s2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Scan and Debug
void scan(){}
template<typename F, typename... R> void scan(F &f,R&... r){cin>>f;scan(r...);}
int di_; string dnms_, co_ = ",";
void debug_(){cout<<endl;}
template<typename F, typename... R> void debug_(F f, R... r){while(dnms_[di_] != ',')cout<<dnms_[di_++];di_++;cout<<": "<<f<<",";debug_(r...);}
#define debug(...) dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__)

const int MAX = 500, INF = 0x3f3f3f3f, DIRS[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
constexpr int HALF = 500 / 2;
int a, b, xmin = INF, xmax = -INF, ymin = INF, ymax = -INF,
	grid[MAX][MAX], pattern[MAX << 1];

#define get(x, y) grid[(x) + HALF][(y) + HALF]

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	scan(a, b);

	int cdir = 0, amt = 1;
	for (int i = 0; i < MAX; ) {
		for (int j = 0; j < amt; j++)
			pattern[i++] = cdir;
		for (int j = 0; j < amt; j++)
			pattern[i++] = cdir + 1;
		cdir = (cdir + 2) % 4;
		amt++;
	}

	int x = 0, y = 0, ptr = 0;
	while (a <= b) {
		xmin = min(xmin, x); xmax = max(xmax, x);
		ymin = min(ymin, y); ymax = max(ymax, y);
		get(x, y) = a;

		// Moving to next
		auto dir = DIRS[pattern[ptr++]];
		x += dir[0];
		y += dir[1];
		a++;
	}

	for (int i = xmin; i <= xmax; i++) {
		for (int j = ymin; j <= ymax; j++) {
			if (get(i, j) == 0)
				printf("   ");
			else
				printf("%2d ", get(i, j));
		}
		printf("\n");
	}

	return 0;
}