//============================================================================
// Name        : BabblingBrooks.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cstdio>
#include <iterator>
#include <vector>
#include <math.h>

using namespace std;

int main() {
	int n;
	scanf("%d", &n);
	vector<double> creeks;

	for(int i = 0; i < n; i++){
		int stream;
		scanf("%d", &stream);
		creeks.push_back(stream);
	}

	int input, a, b;
	for(;;){
		scanf("%d", &input);

		if(input == 99){
			scanf("%d\n%d", &a, &b);
			a--;
			double left = (double)b / 100, right = 1 - left, cv = creeks[a];
			creeks[a] = cv * left;
			creeks.insert(creeks.begin() + a + 1, cv * right);

//			printf("At Split ");
//			int size = creeks.size() - 1;//misleading
//			for(int i = 0; i < size; i++){
//				printf("%g ", round(creeks[i]));
//			}
//			printf("%g\n", round(creeks[size]));
		}
		else if(input == 88){
			scanf("%d", &a);
			b = a;
			a--;
			double ta = creeks[a], tb = creeks[b];
			if(b > a){
				creeks.erase(creeks.begin() + b);
				creeks[a] = ta + tb;
			}
			else{
				creeks.erase(creeks.begin() + a);
				creeks[b] = ta + tb;
			}

//			printf("At Join ");
//			int size = creeks.size() - 1;//misleading
//			for(int i = 0; i < size; i++){
//				printf("%g ", round(creeks[i]));
//			}
//			printf("%g\n", round(creeks[size]));
		}
		if(input == 77){
			break;
		}
	}

	int size = creeks.size() - 1;//misleading
	for(int i = 0; i < size; i++){
		printf("%g ", round(creeks[i]));
	}
	printf("%g\n", round(creeks[size]));

	return 0;
}