//============================================================================
// Name        : GOFaster.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cstdio>
#include <numeric>

using namespace std;

int main() {
	int n, n0;
	scanf("%d", &n);
	n0 = n - 1;
	int ons[n0], offs[n0];
	for(int i = 0; i < n0; i++){
		int on, off;
		scanf("%d %d", &on, &off);
		ons[i] = on;
		offs[i] = off;
	}

	//min
	int min = ons[0] - accumulate(offs, offs + n0, 0);
//	printf("offs total: %d, first board: %d\n", accumulate(offs, offs + n0, 0), ons[0]);
	if(min < 0){
		min = 0;
	}

	//max
	int max = ons[0], buffer = 0;
	for(int i = 1; i < n0; i++){
		if(buffer > offs[i]){
			buffer -= offs[i];
		}
		else{
			max -= (offs[i] - buffer);
			buffer = 0;
		}

		buffer += ons[i];
	}
	if(max < 0){
		max = 0;
	}

	printf("%d\n%d\n", min, max);

	return 0;
}
