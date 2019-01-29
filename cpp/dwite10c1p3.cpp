//============================================================================
// Name        : PowerTiles.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
using namespace std;

int a, b, j, total;

int main(){
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	for (int i = 0; i < 5; ++i) {
		cin >> a >> b;
		total = 0;
		for (j = 1; j <= 8192; j <<= 1) {
			if(a & j){
				a -= j;
				total += b / j;
			}
			if(b & j){
				b -= j;
				total += a / j;
			}
		}
		printf("%d\n", total);
	}
}
