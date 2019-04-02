//============================================================================
// Name        : dmopc16c3p2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 100001;
int n, k, d, ba, sub = 0;
char bt;
ll sfx[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> k >> d;

	fill(sfx, sfx + k + 1, 1);
	for (int i = 0; i < n; ++i) {
		cin >> bt;

		if(bt == 'T')
			sub++;
		else{
			cin >> ba;
			sfx[sub] *= ba;
			if(sfx[sub] > d) sfx[sub] = INT_MAX;
		}
	}

	for (int i = sub - 1; i >= 0; i--){
		sfx[i] *= sfx[i + 1];
		if(sfx[i] > d) sfx[i] = INT_MAX;
	}

	for (int i = 1; i <= k; i++){
		if(sfx[i] == INT_MAX)
			printf("dust\n");
		else
			printf("%lld\n", sfx[i]);
	}
}
