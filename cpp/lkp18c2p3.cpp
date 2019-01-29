//============================================================================
// Name        : NonStrategeticBombing.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 101;
int n, m, a, b, c, d, e, f;
int x[MAX], y[MAX];

struct line{
	double m, b; // y=mx+b, if it's vertical, it will be x=m
	bool vertical;
};

inline void lines(int a, int b, int c, int d, line &l){
	double dy = d - b, dx = c - a;

	if(dx == 0){
		l.vertical = true;
		l.m = a;
		l.b = -1;
	}
	else{
		l.vertical = false;
		l.m = dy / dx;
		l.b = b - l.m * a;
	}
}

inline int gstate(line &l, int a, int b){
	if(l.vertical){ // False is left, True is right (1 is same)
		if(a < l.m) return 0;
		return a == l.m ? 1 : 2;
	}
	else{ // False is below, true is above (1 is same)
		double yfor = l.m * (double)a + l.b;

		if(b < yfor) return 0;
		return b == yfor ? 1 : 2;
	}
}

inline bool issame(int sa, int sb){ // Comparing states
	if(sa == 1 || sb == 1) return true;
	return sa == sb;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	for (int i = 0; i < n; ++i) {
		cin >> x[i] >> y[i];
	}

	for (int i = 0; i < m; ++i) {
		cin >> a >> b >> c >> d >> e >> f;

		int tot = 0, state;
		bool truth[3][n];
		memset(truth, false, sizeof(truth));
		line l;

		// Stuff for point 1
		lines(a, b, c, d, l);
		state = gstate(l, e, f);

		for (int j = 0; j < n; ++j) {
			truth[0][j] = issame(state, gstate(l, x[j], y[j]));
		}

		// Stuff for point 2
		lines(a, b, e, f, l);
		state = gstate(l, c, d);

		for (int j = 0; j < n; ++j) {
			truth[1][j] = issame(state, gstate(l, x[j], y[j]));
		}

		// Stuff for point 3
		lines(c, d, e, f, l);
		state = gstate(l, a, b);

		for (int j = 0; j < n; ++j) {
			truth[2][j] = issame(state, gstate(l, x[j], y[j]));
		}

		// Truth table

		for (int j = 0; j < n; ++j) {
			if(truth[0][j] && truth[1][j] && truth[2][j]){
				tot++;
			}
		}

		printf("%d\n", tot);
	}
}
