//============================================================================
// Name        : MrWhitesCarnival.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 1000000;
ll n;
ll sum = 0;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n;

	for (int i = n / 2; i > 0; --i) {
		if(n % i == 0){
			sum += i;
		}
	}

	printf("%d\n", sum + n);
}
