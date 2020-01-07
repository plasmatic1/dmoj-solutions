//============================================================================
// Name        : PowerTiles.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>

const int B_MAX = 8192;
int a, b, j, total;

int main(){
	for (int i = 0; i < 5; ++i) {
		scanf("%d %d", &a, &b);
		total = 0;
		for (j = 1; j <= B_MAX; j <<= 1) {
			if(a & j){
				a -= j;
				total += b / j;
			}
			if(b & j){
				b -= j;
				total += a / j;
			}
		}
		printf("%d\n", total);
	}
}