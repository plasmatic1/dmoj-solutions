//============================================================================
// Name        : Wireless.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct sp{
	int x, y, r, b, x1, x2;

	sp(int x0, int y0, int r0, int b0, int x10, int x20) : x(x0), y(y0), r(r0), b(b0), x1(x10), x2(x20){}
	sp() : x(-1), y(-1), r(-1), b(-1), x1(-1), x2(-1){}

	friend bool operator<(const sp &a, const sp &b){
		return a.x2 > b.x2;
	}
};

const int MAX = 1000;
int m, n, k, ba, bb, bc, bd,
	best = INT_MIN, cnt = 0;
sp shops[MAX];

bool cmp_lhs(const sp &a, const sp &b){
	return a.x1 < b.x1;
}

#ifndef ONLINE_JUDGE
#define dprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define dprintf(...) ;
#endif

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> m >> n >> k;

	for (int i = 0; i < k; ++i) {
		cin >> ba >> bb >> bc >> bd;
		shops[i] = sp(ba, bb, bc, bd, -1, -1);
	}

	for (int j = 1; j <= m; ++j) {
		// Getting x and y intercepts

		for (int i = 0; i < k; ++i) {
			double ymb = (double)j - (double)shops[i].y, delta = sqrt((double)(shops[i].r * shops[i].r) - ymb * ymb);
			int int1 = (int)ceil(shops[i].x - delta), int2 = (int)floor(shops[i].x + delta);

			dprintf("y=%d circle idx=%d xint1=%d xint2=%d\n", j, i, int1, int2);
			dprintf("a=%d delta=%f\n", shops[i].x, delta);

			shops[i].x1 = int1;
			shops[i].x2 = int2;
		}

		sort(shops, shops + k, cmp_lhs);
		int ptr = 0, csum = 0;
		priority_queue<sp> inrange;

		// Getting totals
		for (int i = 1; i <= n; ++i) {
			while(ptr < k && shops[ptr].x1 <= i){
				csum += shops[ptr].b;
				inrange.push(shops[ptr++]);
			}

			while(!inrange.empty() && inrange.top().x2 < i){
				csum -= inrange.top().b;
				inrange.pop();
			}

			if(csum > best){
				best = csum;
				cnt = 1;
			}
			else if(csum == best){
				cnt++;
			}

			dprintf("x=%d y=%d csum=%d best=%d cnt=%d\n", i, j, csum, best, cnt);
			dprintf("idx=%d topx1=%d\n", ptr, shops[ptr].x1);
		}
	}

	printf("%d\n%d\n", best, cnt);
}
