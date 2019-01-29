//============================================================================
// Name        : UnluckyNumbers.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int V_MAX = 1000001;
int n, k, buf,
	pfx[V_MAX];
bool arr[V_MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> k;

	for (int i = 0; i < k; ++i) {
		cin >> buf;
		arr[buf] = true;
	}

	for (int i = 1; i <= V_MAX; ++i) {
		pfx[i] = arr[i] + pfx[i - 1];
	}

	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> buf;
		printf("%d\n", buf - pfx[buf]);
	}
}
