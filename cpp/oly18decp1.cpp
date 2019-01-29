//============================================================================
// Name        : MostFrequentNumber.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MV = 10001;
int n, buf,
	freq[MV];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> buf;
		freq[buf]++;
	}

	int mv = -100, mi = -1;

	for (int i = 0; i < MV; ++i) {
		if(freq[i] > mv){
			mv = freq[i];
			mi = i;
		}
	}

	printf("%d\n", mi);
}
