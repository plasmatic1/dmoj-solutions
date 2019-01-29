//============================================================================
// Name        : TheNewKid.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int NMAX = 1001, MMAX = 3001;
const int MAX = 1000000;
int n, m, buf;

int nolike[MMAX], house[NMAX], maxh = -1, absmaxd = INT_MIN;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> m;

	for (int i = 0; i < n; ++i) {
		cin >> house[i];
	}

	for (int j = 0; j < m; ++j) {
		cin >> nolike[j];
	}

	sort(nolike, nolike + m);

	for (int i = 0; i < n; ++i) {
		auto ptr = lower_bound(nolike, nolike + m, house[i]);

		int maxd = INT_MAX;

		if(ptr == nolike){
			maxd = *ptr - house[i];
		}
		else if(ptr == (nolike + m)){
			maxd = house[i] - *(ptr - 1);
		}
		else{
			maxd = min(*ptr - house[i], house[i] - *(ptr - 1));
//			printf("house at %d\n", maxd);
		}

		if(maxd > absmaxd){
			absmaxd = maxd;
			maxh = house[i];
		}
	}

	printf("%d\n", maxh);
}
