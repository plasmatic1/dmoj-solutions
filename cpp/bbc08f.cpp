//============================================================================
// Name        : bbc08f.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

int n, l, r, x, ba, bb;
ll tot = 0;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> x;
	l = r = x;

	for (int i = 0; i < n; ++i) {
		cin >> ba >> bb;

		if(l > bb){ // to the right of
			tot += l - bb;
			r = l;
			l = bb;
		}
		else if(r < ba){ // to the left of
			tot += ba - r;
			l = r;
			r = ba;
		}
		else{ // They intersect
			l = max(l, ba);
			r = min(r, bb);
		}
	}

	printf("%lld\n", tot);
}
