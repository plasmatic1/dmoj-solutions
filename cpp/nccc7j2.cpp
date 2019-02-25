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

int n, buf;
bool a[7];
char bc;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	for(int i = 0; i < 7; i++){
		cin >> bc;
		a[i] = bc == 'J';
	}

	bool streak = false;
	int cnt = 0;
	for(int i = 0; i < 7; i++){
		if(a[i] && !streak){
			cnt++;
			streak = true;
		}
		else if(!a[i]) streak = false;
	}

	printf("%d\n", cnt);
}