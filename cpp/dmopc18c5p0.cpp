//============================================================================
// Name        : dmopc18c5p0.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

string type;
double a[3], b[3];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> type;

	for(int i = 0; i < 3; i++)
		cin >> a[i];

	for(int i = 0; i < 3; i++)
		cin >> b[i];

	for(int i = 0; i < 3; i++){
		if(type == "Multiply")
			b[i] = a[i] * b[i];
		else if(type == "Screen")
			b[i] = 1. - (1. - a[i]) * (1. - b[i]);
		else{
			if(a[i] < 0.5)
				b[i] = 2 * a[i] * b[i];
			else
				b[i] = 1 - 2 * (1. - a[i]) * (1. - b[i]);
		}
	}

	for(int i = 0; i < 3; i++)
		printf("%.10f ", b[i]);
	printf("\n");
}
