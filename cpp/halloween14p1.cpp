//============================================================================
// Name        : RabbitGirls.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int n, k, mod;

int main() {
	scanf("%d", &n);
	scanf("%d", &k);

	mod = n % k;

	if(mod == 0){
		printf("0\n");
		return 0;
	}

	if(n / k < 2){
		printf("%d\n", k - mod);
	}
	else{
		printf("%d\n", min(k - mod, mod));
	}

	return 0;
}
