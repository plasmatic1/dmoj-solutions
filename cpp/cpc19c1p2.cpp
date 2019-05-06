//============================================================================
// Name        : cpc18c1p2.cpp
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
int n, k, best = 1,
	arr[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> k;

	for (int i = 0; i < n; i++)
		cin >> arr[i], assert(arr[i] >= 0 && arr[i] <= 1000000000);
	sort(arr, arr + n);

	for (int i = 0; i < n; i++)
		best = max(best, (int)(upper_bound(arr, arr + n, arr[i] + k) - arr - i));

	printf("%d\n", best);
}