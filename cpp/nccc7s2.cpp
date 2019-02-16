//============================================================================
// Name        : nccc7s2.cpp
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

int x, y, a, b, c, d;
double best =  0.;

inline double dist(int a, int b, int c, int d){
	double dx = c - a, dy = d - b;
	return sqrt(dx * dx + dy * dy);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> x >> y >> a >> b >> c >> d;

	// Vertical lines
	if(y >= b && y <= d)
		best = (double)min(abs(x - a), abs(x - c));

	// Horizontal lines
	else if(x >= a && x <= c)
		best = (double)min(abs(y - b), abs(y - d));

	// Neither
	else{
		best = min(dist(x, y, a, b),
				min(dist(x, y, c, b), min(dist(x, y, a, d), dist(x, y, c, d))));
	}

	printf("%.3f\n", best);
}