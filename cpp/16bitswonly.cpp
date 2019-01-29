//============================================================================
// Name        : 16BitSWOnly.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int n;

int main() {
	scanf("%d", &n);

	for (int i = 0; i < n; ++i) {
		long long a, b, c;
		scanf("%lld %lld %lld", &a, &b, &c);

		if(a * b != c){
			printf("16 BIT S/W ONLY\n");
		}
		else{
			printf("POSSIBLE DOUBLE SIGMA\n");
		}
	}

	return 0;
}
