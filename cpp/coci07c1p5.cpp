//============================================================================
// Name        : coci07c1p5.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 100001, MAX2 = MAX << 1, OFFS = 100000;
int n, b,
	arr[MAX], cnts[MAX2];
ll tot = 0;

int get(int x){
	return cnts[x + OFFS];
}

void inc(int x){
	cnts[x + OFFS]++;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> b;

	int bidx = -1;
	for(int i = 0; i < n; i++){
		cin >> arr[i];
		if(arr[i] == b)
			bidx = i;
	}

	inc(0);
	int cur = 0;
	for(int i = bidx + 1; i < n; i++){
		if(arr[i] > b) cur++;
		else cur--;

		inc(cur);
	}

	tot += get(0);

	cur = 0;
	for(int i = bidx - 1; i >= 0; i--){
		if(arr[i] > b) cur++;
		else cur--;

		tot += get(-cur);
	}

	printf("%lld\n", tot);
}
