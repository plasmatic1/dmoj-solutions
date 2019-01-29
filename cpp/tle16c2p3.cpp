//============================================================================
// Name        : FaxsThanksgivingDinner.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
//#define DEBUG

using namespace std;

const int MAXV = 1000001;
int n, c, buf;
bool exist[MAXV];

set<int> cuts, pieces;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> c;

	for (int i = 0; i < c; ++i) {
		cin >> buf;

		int sqbuf = sqrt(buf) + 2;

		if(buf % 2 == 0){
			if(!exist[2]){
				cuts.insert(2);
				exist[2] = true;
			}

			buf /= 2;

			while(buf % 2 == 0){
				buf /= 2;
			}
		}

		for(int j = 3; j <= sqbuf; j += 2){
			if(buf % j == 0){
				if(!exist[j]){
					cuts.insert(j);
					exist[j] = true;
				}

				buf /= j;

				while(buf % j == 0){
					buf /= j;
				}
			}
		}

		if(buf != 1){
			cuts.insert(buf);
		}
	}

#ifdef DEBUG
	printf("cuts: [");
	for(int i : cuts){
		printf("%d, ", i);
	}
	printf("]\n");
#endif

	for (int i = 0; i < n; ++i) {
//		cin >> reqs[i];
		cin >> buf;

		for(int cut : cuts){
			while(buf % cut == 0){
				buf /= cut;
			}

			if(buf == 1){
				break;
			}
		}

		if(buf != 1){
			printf("N\n");
			return 0;
		}
	}

	printf("Y\n");
}
