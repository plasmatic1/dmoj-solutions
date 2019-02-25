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

ll n, k;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> k;

	ll quo = k + 1, div = n / quo, tot = div * k;
	if(n % quo != 0){
		tot += n % quo;
	}

	printf("%lld\n", tot);
}