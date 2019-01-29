//============================================================================
// Name        : Trident.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int t, s, h;

int main() {
	scanf("%d", &t);
	scanf("%d", &s);
	scanf("%d", &h);

	for(int i = 0; i < t; i++){
		printf("*");
		for(int j = 0; j < s; j++){
			printf(" ");
		}
		printf("*");
		for(int j = 0; j < s; j++){
			printf(" ");
		}
		printf("*\n");
	}

	int span = 3 + s * 2;
	for(int i = 0; i < span; i++){
		printf("*");
	}
	printf("\n");

	for(int i = 0; i < h; i++){
		for(int i = 0; i <= s; i++){
			printf(" ");
		}
		printf("*\n");
	}

	return 0;
}
