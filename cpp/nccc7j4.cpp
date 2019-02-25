//============================================================================
// Name        : JoeyAndBiology.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

string a, b;
int tot = 0,
		cnta[26], cntb[26];

inline int code(char c){
	return (int)(c - 'A');
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> a >> b;

	for(char c : a) cnta[code(c)]++;
	for(char c : b) cntb[code(c)]++;

	for (int i = 0; i < 26; ++i) {
		if(cntb[i] < cnta[i]) tot += cnta[i] - cntb[i];
	}

	printf("%d\n", tot);
}