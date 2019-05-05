//============================================================================
// Name        : dmpg18s2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 1000000;
int n,
	posOf[10][10]; // posOf[i][j] = position of value j in key #i
string encr,
	keys[10];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	for (int i = 0; i < 10; i++) {
		cin >> keys[i];

		for (int j = 0; j < 10; j++) {
			char c = keys[i][j];
			posOf[i][(int)(c - '0')] = j;
		}
	}

	cin >> encr;

	printf("%c", encr[0]);
	int last = encr[0] - '0';
	for (int i = 1, sz = encr.length(); i < sz; i++) {
		last = posOf[last][encr[i] - '0'];
		printf("%c", last + '0');
	}
	printf("\n");
}