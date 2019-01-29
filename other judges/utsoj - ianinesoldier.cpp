//============================================================================
// Name        : IaninesSoldierProblem.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 100001;
int n, cl = 0, inarow = 0, maxv = INT_MIN;
char pos[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> pos;

	for (int i = 0; i < n; ++i) {
		if(pos[i] == 'L'){
			maxv = max(maxv, i - (cl++) + inarow);
		}

		inarow = pos[i] == 'L' ? inarow + 1 : max(0, inarow - 1);
	}

	printf("%d\n", maxv);
}
