//============================================================================
// Name        : inaho10.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

const double MULTI = 1e10, KVAL = 1 / MULTI;
int n;
double ret;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	printf("Q %.20f\n", KVAL);
	cin >> ret;
	printf("A %d\n", (int)round(ret * MULTI));
}
