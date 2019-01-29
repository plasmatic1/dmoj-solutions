//============================================================================
// Name        : Sorting.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 200002;
int n, minn = INT_MIN, maxx = INT_MAX, nums[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	nums[0] = -1;
	nums[n + 1] = INT_MAX;

	for (int i = 1; i <= n; ++i) {
		cin >> nums[i];
	}

	int lnz = -1;
	for (int i = 1; i <= n; ++i) {
//		printf("lnz=%d, nums[i]=%d\n", lnz, nums[i]);

		if(nums[i] != 0){
			if(lnz > nums[i]){
				printf("NO\n");
				return 0;
			}
			lnz = nums[i];
		}
	}

	int firstwc = -1, lastwc = -1;
	for (int i = 1; i <= n; ++i) {
		if(nums[i] == 0){
			if(firstwc == -1){
				firstwc = i;
			}
			lastwc = i;
		}
	}

	if(firstwc == -1 || lastwc == -1 || firstwc == lastwc){
		printf("YES\n");
		return 0;
	}

//	printf("firstwc=%d,lastwc=%d,nwcminv=%d,nwcmaxv=%d\n", firstwc, lastwc, nwcminv, nwcmaxv);

	int midval = -1;
	for (int i = firstwc; i <= lastwc; ++i) {
		if(nums[i] != 0){
			if(midval == -1){
				midval = nums[i];
			}
			else{
				if(nums[i] != midval){
					printf("NO\n");
					return 0;
				}
			}
		}
	}

	printf("YES\n");
}
