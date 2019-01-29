//============================================================================
// Name        : Cesta.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>

using namespace std;

int main() {
	string num;
	getline(cin, num);

	int len = num.size(), sum = 0, digits[len];
	bool zero = false;
	for(int i = 0; i < len; i++){
		int v = num[i] - '0';
//		printf("%d\n", v);
		if(v == 0){
			zero = true;
		}
		else{
			sum += v;
		}

		digits[i] = v;
	}

	if(sum % 3 == 0 && zero){
		sort(digits, digits + len, greater<int>());
		for(int i = 0; i < len; i++){
			printf("%d", digits[i]);
		}
		printf("\n");
	}
	else{
		printf("-1\n");
	}

	return 0;
}
