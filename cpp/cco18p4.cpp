//============================================================================
// Name        : cco18p4.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int rv, c, k;

#ifndef ONLINE_JUDGE
const int N = 4, pts[N][2] = {{2, 3}, {2, 3}, {4, 3}, {5, 1}};
//const int N = 3, pts[N][2] = {{1, 2}, {1, 4}, {1, 10}};
#endif

ll question(int p, int q){
	if(p == 0 || q == 0) return 0L;
	ll ret = 0;
#ifndef ONLINE_JUDGE
	for(int i = 0; i < N; i++)
		ret += abs(p - pts[i][0]) + abs(q - pts[i][1]);
#else
	printf("? %d %d\n", p, q);
	cin >> ret;
#endif
	return ret;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	setbuf(stdout, NULL);

	cin >> rv >> c >> k;

	int lx = 1, ly = 1, rx = rv + 1, ry = c + 1;
	while((lx + 1 < rx) || (ly + 1 < ry)){
		int midx = (lx + rx) >> 1, midy = (ly + ry) >> 1;
		ll left = question(midx - 1, midy), down = question(midx, midy - 1),
				centre = question(midx, midy);

		if(left > centre)
			lx = midx;
		else
			rx = midx;

		if(down > centre)
			ly = midy;
		else
			ry = midy;
	}

	printf("! %lld\n", question(lx, ly));
}