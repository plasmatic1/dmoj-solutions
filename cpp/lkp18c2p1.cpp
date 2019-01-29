//============================================================================
// Name        : FoodLines.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 201;
int n, a, buf,
	freq[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> a;

	for (int i = 0; i < n; ++i) {
		cin >> buf;
		freq[buf]++;
	}

	int ptr = 0;
	for (int i = 0; i < a; ++i) {
		while(freq[ptr] == 0){
			ptr++;
		}

		printf("%d\n", ptr);
		freq[ptr]--;
		freq[ptr + 1]++;
	}
}
