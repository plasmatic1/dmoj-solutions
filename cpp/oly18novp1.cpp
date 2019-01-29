//============================================================================
// Name        : Segment.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct p{int i, j;
friend bool operator<(const p &a, const p &b){
	if(a.i == b.i){
		return a.j < b.j;
	}
	return a.i < b.i;
}
};

const int MAX = 1000000;
int n, ba, bb, cnt = 0;
p segs[MAX]; // Maxicans

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> ba >> bb;
		segs[i] = {ba, bb};
	}

	sort(segs, segs + n);

	int lastmax = -100;
	for (int i = 0; i < n; ++i) {
		if(segs[i].i >= lastmax){
			lastmax = segs[i].j;
			cnt++;
		}
		else if(segs[i].j < lastmax){
			lastmax = segs[i].j;
		}
	}

	printf("%d\n", cnt);
}
