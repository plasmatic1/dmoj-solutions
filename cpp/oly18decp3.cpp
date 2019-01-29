//============================================================================
// Name        : MaximumSumOfTwoNumbers.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 100001;
int n, m, mv = INT_MIN,
	arr[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	for (int i = 0; i < n; ++i) {
		cin >> arr[i];
	}

	sort(arr, arr + n);

	for (int i = 0; i < n; ++i) {
		int idx = upper_bound(arr, arr + n, m - arr[i]) - arr - 1;

//		printf("i=%d idx=%d val=%d\n", i, idx, m - arr[i]);

		if(idx < 0 || (i == 0 && i == idx)){
			continue;
		}

		if(i == idx){
			idx--;
		}

		mv = max(mv, arr[i] + arr[idx]);
	}

	printf("%d\n", mv);
}
