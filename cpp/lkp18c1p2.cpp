//============================================================================
// Name        : ObservingFrogs.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

ll n;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	ll on = n;
	bool odd = n % 2;
	if(odd){
		n--;
	}
	else{
		n -= 2;
	}

	ll h = on / 2;
	ll total = n * (n + 2) / 4;

	if(!odd){
		total += h;
	}

	printf("%lld\n", total * 2);
}
