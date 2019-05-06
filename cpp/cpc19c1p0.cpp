//============================================================================
// Name        : coci14c7p5.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n, h;
char b;
vector<int> a[2];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

    n = 4;
	h = n >> 1;
	
	for(int i = 0; i < n; i++){
	    cin >> b;
	    a[b == 'R'].push_back(i);
	}
	
	for(int i = 0; i < h; i++)
	    printf("%d %d\n", a[0][i] + 1, a[1][i] + 1);
}