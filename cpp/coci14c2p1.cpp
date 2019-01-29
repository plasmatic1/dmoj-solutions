//============================================================================
// Name        : Mobitel.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

int dec(int x){
	return x - 1;
}

int len, last = -1, match[9];
string line, final;

int countt[26] = {1, 2, 3,
		1, 2, 3,
		1, 2, 3,
		1, 2, 3,
		1, 2, 3,
		1, 2, 3, 4,
		1, 2, 3,
		1, 2, 3, 4},

		digit[26] = {2, 2, 2,
		3, 3, 3,
		4, 4, 4,
		5, 5, 5,
		6, 6, 6,
		7, 7, 7, 7,
		8, 8, 8,
		9, 9, 9, 9};

int main() {
	for(int i = 0; i < 9; i++){
		int v;
		scanf("%d", &v);
		match[v - 1] = i + 1;
	}
	scanf("\n");

	getline(cin, line);
	len = line.length();

	for(int i = 0; i < len; i++){
		int d = line[i] - 'a', c_digit = match[digit[d] - 1], c_count = countt[d];

//		printf("char num: %d, old chr: %d, new chr: %d, count: %d\n", d, digit[d], c_digit, c_count);

		if(c_digit == last){
			final += "#";
		}

		for(int j = 0; j < c_count; j++){
			final += (char)(c_digit + '0');
		}

		last = c_digit;
	}

	printf("%s\n", final.c_str());

	return 0;
}
