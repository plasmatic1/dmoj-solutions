//============================================================================
// Name        : dmopc18c6p1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 1000001;
int n;
char s[MAX];
bool hasT = false, hasU = false;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> s;

	for (int i = 0; i < n; ++i) {
		if(s[i] != 'A' && s[i] != 'C' && s[i] != 'G' && s[i] != 'T' && s[i] != 'U'){
			printf("neither\n");
			return 0;
		}

		hasT |= s[i] == 'T';
		hasU |= s[i] == 'U';
	}

	if(hasT && hasU)
		printf("neither\n");
	else if(hasT)
		printf("DNA\n");
	else if(hasU)
		printf("RNA\n");
	else
		printf("both\n");
}