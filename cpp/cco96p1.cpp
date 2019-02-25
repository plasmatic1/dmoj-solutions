//============================================================================
// Name        : cco96p1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 51;
int t, l, arr[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> t;
	while(t--){
		cin >> l;
		for(int i = 0; i < l; i++)
			cin >> arr[i];

		int tot = 0;
		for(int i = 0; i < l; i++)
			for(int j = 0; j < i; j++)
				tot += arr[j] > arr[i];

		printf("Optimal train swapping takes %d swaps.\n", tot);
	}
}
