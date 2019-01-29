//============================================================================
// Name        : MultipleChoice.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int n, c = 0;
char key[10000], v[1];

int main() {
	scanf("%d", &n);

	for (int i = 0; i < n; ++i) {
		scanf("%s", v);

		key[i] = v[0];
	}

	for (int i = 0; i < n; ++i) {
		scanf("%s", v);

		if(v[0] == key[i]){
			c++;
		}
	}

	printf("%d\n", c);

	return 0;
}
