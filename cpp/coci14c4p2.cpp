//============================================================================
// Name        : Psenica.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#define DEBUG

#include <algorithm>
#include <cstdio>
#include <deque>
#include <vector>
#include <assert.h>

using namespace std;

const int MAX = 100001;
int n, stalks[MAX], buf, sizes = 0, curr_turn = 0, mmin, mmin2, mmax, mmax2; // 0 = m, 1 = s
deque<int> mins;

int main() {
	scanf("%d", &n);

	for (int i = 0; i < n; ++i) {
		scanf("%d", &buf);
		if(!stalks[buf]){
			sizes++;
		}

		stalks[buf]++;
	}

	for(int i = 1; i < MAX; i++){
		if(stalks[i]){
			mins.push_back(i);
		}
	}

	if(sizes < 3){
		printf("Slavko\n%d %d\n", mins.front(), mins.back());
		return 0;
	}

	mmin = mins.front();
	mmin2 = *(++mins.begin());

	mmax = mins.back();
	mmax2 = *(----mins.end());

	while(sizes >= 3){
		if(stalks[mmax] < stalks[mmin]){
			//Slavko gets it
			stalks[mmin] -= stalks[mmax];
			stalks[mmin2] += stalks[mmax];
			stalks[mmax2] += stalks[mmax];
			stalks[mmax] = 0;

			sizes--;

			mins.pop_back();
			mmax = mmax2;
			mmax2 = *(----mins.end());

			curr_turn = 0;
		}
		else if(stalks[mmin] < stalks[mmax]){
			//Mirko gets it
			stalks[mmax] -= stalks[mmin];
			stalks[mmin2] += stalks[mmin];
			stalks[mmax2] += stalks[mmin];
			stalks[mmin] = 0;

			sizes--;

			mins.pop_front();
			mmin = mmin2;
			mmin2 = *(++mins.begin());

			curr_turn = 1;
		}
		else{
			//Mirko still fucking gets it because he goes first ('''totally''' bc white privelege ecks dee)
			stalks[mmin2] += stalks[mmin];
			stalks[mmax2] += stalks[mmin];
			stalks[mmin] = 0;
			stalks[mmax] = 0;

			//Bump next for mirko

			sizes--;

			mins.pop_front();
			mmin = mmin2;
			mmin2 = *(++mins.begin());

			//Hope mirko wins otherwise hes fucked

			if(sizes < 3){
				curr_turn = 1;
				break;
			}

			//If this is the end mirko is def fucked

			sizes--;

			mins.pop_back();
			mmax = mmax2;
			mmax2 = *(----mins.end());

			curr_turn = 0;
		}

#ifdef DEBUG
		printf("Ended turn mirko, vals are\n");
		printf("stalks: ");
		for (int i = 1; i <= 10; ++i) {
			printf("%d, ", stalks[i]);
		}
		printf("\n");
		printf("mins: [");
		for(int i : mins){
			printf("%d, ", i);
		}
		printf("]\n");
#endif
	}

	if(curr_turn){
		printf("Mirko\n");
	}
	else{
		printf("Slavko\n");
	}

	printf("%d %d\n", mins.front(), mins.back());

	return 0;
}
