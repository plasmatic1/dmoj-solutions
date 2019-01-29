//============================================================================
// Name        : GranicaRecode.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 100;
int n, mind = INT_MAX, nums[MAX];

int gcd(int a, int b){
	if(b == 0){
		return a;
	}
	return gcd(b, a % b);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> nums[i];
	}

	sort(nums, nums + n);

	int n0 = n - 1;
	for (int i = 0; i < n0; ++i) {
		if(i == 0){
			mind = nums[1] - nums[0];
		}
		else{
			mind = gcd(mind, nums[i + 1] - nums[i]);
		}

//		printf("mind=%d after %d - %d\n", mind, nums[i + 1], nums[i]);
	}

	for (int i = 2; i <= mind / 2; ++i) {
		if(mind % i == 0){
			printf("%d ", i);
		}
	}
	printf("%d\n", mind);

	/*
	 * with a, b, m
	 *
	 * if a % m == b % m
	 * then (a - b) % m == 0
	 */
}
