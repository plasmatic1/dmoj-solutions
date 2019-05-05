//============================================================================
// Name        : dmpg18s1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int a[3], c;

bool rec(int idx, int cur) {
	if (idx == 3)
		return cur == c;

	bool flag = false;
	for (int i = 1; i <= 100; i++)
		flag |= rec(idx + 1, cur + a[idx] * i);

	return flag;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> a[0] >> a[1] >> a[2] >> c;

	if (rec(0, 0))
		printf("QUEST CLEARED\n");
	else
		printf("TRY AGAIN\n");
}