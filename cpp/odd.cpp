//============================================================================
// Name        : TheOddNumber.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <map>
using namespace std;

map<int, int> m;
int n, buf;

bool find(int v){
	return m.find(v) != m.end();
}

int main() {
	scanf("%d", &n);

	for (int i = 0; i < n; ++i) {
		scanf("%d", &buf);

		if(find(buf)){
			m[buf]++;
		}
		else{
			m[buf] = 1;
		}
	}

	for(pair<int, char> p : m){
		if(p.second % 2){
			printf("%d\n", p.first);
			break;
		}
	}

	return 0;
}
