//============================================================================
// Name        : Plutonium.cpp
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
int n, mincnt = 0, maxcnt = 0,
	days[MAX], mdays[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> days[i];
		mdays[i] = days[i];

		if(i > 0){
			if((days[i] < days[i - 1] && days[i] > 1) || (days[i] == days[i - 1] && days[i] > 1)){
				printf("-1\n");
				return 0;
			}
		}
	}

	if(days[0] == 0){
		days[0] = 1;
		mdays[0] = 1;
	}

	if(days[0] != 1 && days[0] != 0){
		printf("-1\n");
		return 0;
	}

	// Filling in required build ups

	int run = 0;
	for (int i = n - 1; i >= 0; --i) {
		if(days[i] != 0){
			if(days[i] >= run){
//				printf("run=%d i=%d days[i]=%d\n", run, i, days[i]);

				for (int j = i + 1; j < n; ++j) {
					if(days[j] < 1){
						days[j] = 1;
					}
					else{
						break;
					}
				}
			}
			else{
				printf("-1\n");
				return 0;
			}

			run = days[i];
		}
		else{
			days[i] = run;
		}

		run = run > 0 ? run - 1 : 0;
	}

	run = 0;
	for (int i = n - 1; i >= 0; --i) {
		if(mdays[i] != 0){
			run = mdays[i];
		}
		else{
			mdays[i] = run;
		}

		run = run > 0 ? run - 1 : 0;
	}

	for (int i = 0; i < n; ++i) {
		if(mdays[i] == 0){
			mdays[i] = mdays[i - 1] + 1;
		}
	}

//	printf("days: ");
//	for (int i = 0; i < n; ++i) {
//		printf("%d, ", days[i]);
//	}
//	printf("\n");
//
//	printf("mdays: ");
//	for (int i = 0; i < n; ++i) {
//		printf("%d, ", mdays[i]);
//	}
//	printf("\n");

	// Getting min cnt

	for (int i = 1; i < n; ++i) {
		if(mdays[i] == 1){
			mincnt++;
		}
	}

	// Getting max cnt

	for (int i = 1; i < n; ++i) {
		if(days[i] == 1){
			maxcnt++;
		}
	}

	printf("%d %d\n", mincnt, maxcnt);
}
