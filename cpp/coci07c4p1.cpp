//============================================================================
// Name        : Vauvau.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int a, b, c, d, p[3], as, bs;

int main() {
	scanf("%d %d %d %d", &a, &b, &c, &d);
	scanf("%d %d %d", &p[0], &p[1], &p[2]);

	as = a + b;
	bs = c + d;

//	printf("a, b, c, d = %d, %d, %d, %d\n", a, b, c, d);

	for(int i = 0; i < 3; i++){
		int cnt = 0, va = p[i] % as, vb = p[i] % bs;
		if(va <= a && va != 0){
			cnt++;
		}
		if(vb <= c && vb != 0){
			cnt++;
		}

//		printf("p[%d]: %d, va: %d, vb: %d\n", i, p[i], va, vb);

		if(cnt == 0){
			printf("none\n");
		}
		else if(cnt == 1){
			printf("one\n");
		}
		else{
			printf("both\n");
		}
	}
}
