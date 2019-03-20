//============================================================================
// Name        : rgpc18p3.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 1000010;
int n, t, ba, bb, bc, best = -1;
ll lv,
	pfx[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> t;

	for (int i = 0; i < t; ++i) {
		cin >> ba >> bb >> bc;
		pfx[ba] += bc;
		pfx[bb + 1] -= bc;
	}

	for(int i = 1; i <= n; i++)
		pfx[i] += pfx[i - 1];
	for(int i = 1; i <= n; i++)
		pfx[i] += pfx[i - 1];

	cin >> lv;

	int l = 1, r = 0;
	while(r <= n){
		ll sum = pfx[r] - pfx[l - 1];

		if(sum <= lv){
			best = max(best, r - l + 1);
			r++;
		}
		else
			l++;
	}

	printf("%d\n", best);
}