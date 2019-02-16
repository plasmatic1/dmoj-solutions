//============================================================================
// Name        : valentines19j2.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

int n, ba, bb, bc, tot = 0;

inline bool between(int l, int r, int v){
	return v >= l && v <= r;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> ba >> bb >> bc;
		tot += between(240, 255, ba) && between(0, 200, bb) && between(95, 220, bc);
	}

	printf("%d\n", tot);
}
