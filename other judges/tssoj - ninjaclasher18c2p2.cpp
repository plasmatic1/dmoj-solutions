//============================================================================
// Name        : nc2p3.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 100001;
int n;
ll even = 0, odd = 0;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	ll lasteven = n - (n % 2);
	even = lasteven * (lasteven / 2 - 1);

	if(n % 2){
		even += lasteven;
	}

	odd = even + lasteven;

	printf("%lld\n%lld\n", even, odd);
}
