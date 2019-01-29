//============================================================================
// Name        : Dodgeball.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cstdio>

using namespace std;

int main() {
	int n;
	scanf("%d", &n);
	char names[n];
	for(int i = 0; i < n; i++){
		char name[20];
		scanf("%s", name);
		names[i] = name[0];
//		printf("%c\n", names[i]);
	}

	int total = n;

	int v = 0;
	char curr = names[0];
	for(int i = 0; i < n; i++){
		if(names[i] == curr){
			v++;
		}
		else{
			v = 1;
			curr = names[i];
		}

		if(v > 1){
			total += v - 1;
		}

		if(total > 1000000007){
			total %= 1000000007;
		}
	}

//	for(int i = 0; i < n; i++){
//		printf("%d, ", same[i]);
//	}
//	printf("\n");

//	for(int i = 2; i <= n; i++){
//		for(int j = i - 1; j < n; j++){
//			if(same[j] >= i){
//				total++;
//				if(total > 1000000007){
//					total = 0;
//				}
//			}
//		}
//	}

	printf("%d\n", total);

	return 0;
}
