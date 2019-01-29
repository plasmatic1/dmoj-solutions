//============================================================================
// Name        : CopsAndRobbers.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <algorithm>
#include <cstdio>
#include <deque>

using namespace std;

const int MAX = 1000000;

int n;
bool protecs[MAX + 1], protecs2[MAX]; //Protecs: whether a bank is protected, Protecs2: whether a bank is protected on a certain day (f time only)
deque<int> protec, unprotec;

int main() {
	fill(protecs, protecs + MAX + 1, false);
	fill(protecs2, protecs2 + MAX, false);

	scanf("%d\n", &n);
	for(int i = 0; i < n; i++){
		int v;
		scanf("%d", &v);

		if(!protecs[v]){
			protecs2[i] = true;
			protec.push_back(v);
		}
		protecs[v] = true;
	}

	if(protec.size() == 1){
		printf("-1\n");
		return 0;
	}

	for(int i = 1; i <= n; i++){
		if(!protecs[i]){
			unprotec.push_back(i);
		}
	}

	int l = protec.front();
	protec.pop_front();
	protec.push_back(l);

//	printf("protec: ");
//	for(int i = 0; i < protec.size(); i++){
//		printf("%d ", protec[i]);
//	}
//	printf("\n");
//
//	printf("unprotec: ");
//	for(int i = 0; i < unprotec.size(); i++){
//		printf("%d ", unprotec[i]);
//	}
//	printf("\n");

	for(int i = 0; i < n; i++){
		if(protecs2[i]){
			int f = protec.front();
			protec.pop_front();
			printf("%d ", f);
		}
		else{
			int f = unprotec.front();
			unprotec.pop_front();
			printf("%d ", f);
		}
	}
	printf("\n");

	return 0;
}
