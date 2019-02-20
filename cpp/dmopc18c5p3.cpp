//============================================================================
// Name        : dmopc18c5p3.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 200001;
int n, best = 0,
	arr[MAX];
ll m;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	for(int i = 0; i < n; i++)
		cin >> arr[i];

	ll csum = arr[0];
	for(int l = 0, r = 0; r < n; ){
		if(csum < m){
			best = max(best, r - l + 1);
			csum += arr[++r];
		}
		else{
			csum -= arr[l++];

			if(l > r)
				csum += arr[++r];
		}
	}

	printf("%d\n", best);
}
