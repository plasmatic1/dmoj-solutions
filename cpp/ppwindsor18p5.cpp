//============================================================================
// Name        : ProductiveMathClass.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 1000000;
int n, buf;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n;

	int mag = 10, nc = 1;
	while(n >= (mag * nc)){
		n -= (mag - (mag / 10)) * nc;
		mag *= 10;
		nc++;
	}

	int dign = (n % nc > 0 ? n % nc : nc) - 1, num = (mag / 10) + (int)(ceil((double)n / nc)) - 1;

//	printf("dign=%d,num=%d\n", dign, num);
//	printf("n=%d mag=%d nc=%d\n", n, mag, nc);

	printf("%c\n", to_string(num)[dign]);

	return 0;
}
