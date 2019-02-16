//============================================================================
// Name        : nccc7s1.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

ll x, y, tv;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> x >> y;
	tv = x * y;

	if(tv % 2) printf("%lld.5\n", tv / 2);
	else printf("%lld.0\n", tv / 2);
}