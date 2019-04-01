//============================================================================
// Name        : dmpg18s1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 100001;
int n;
string s;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> s;
	n = s.length();

	int cur = 1;
	for (int i = 0; i < n; ++i) {
		if(cur-- < 0){
			printf("Invalid\n");
			return 0;
		}

		cur += (int)(s[i] - '0');
	}

	if(cur == 0) printf("Valid\n");
	else printf("Invalid\n");
}
