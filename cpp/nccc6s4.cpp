//============================================================================
// Name        : PusheenPlaysNekoAtsume.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MV = 10000001;
int a, b, c, d, q, buf;
//unordered_map<int, ll> dp;
int dpa[MV];

int rec(int v){
	if(v < 1) return 1;
	if(v < MV) return dpa[v];

	return rec(v / a - b) + rec(v / c - d);
}

int x, y;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> a >> b >> c >> d >> q;

	for (int i = 1; i < MV; ++i) {
		x = i / a - b;
		y = i / c - d;
		dpa[i] = (x < 1 ? 1 : dpa[x]) + (y < 1 ? 1 : dpa[y]);
	}

	while(q--){
		cin >> buf;

		printf("%d\n", rec(buf));
	}

//	for(pair<int, int> pi : dpb){
//		printf("%d: %d\n", pi.first, pi.second);
//	}
//	printf("sz=%d\n", dpb.size());
}