//============================================================================
// Name        : MoreQueries.cpp
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
int n, q, ba, bb,
	arr[MAX];
string str;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> str;
	n = str.length();

	// PFX

	for (int i = 0; i < n - 1; ++i) {
		if(str[i] == str[i + 1]){
			arr[i] = 1;
		}
	}

	for (int i = 1; i < n; ++i) {
		arr[i] += arr[i - 1];
	}

	// Queries

	cin >> q;

	for (int i = 0; i < q; ++i) {
		cin >> ba >> bb;
		ba--;
		bb--;

		printf("%d\n", arr[bb - 1] - (ba > 0 ? arr[ba - 1] : 0));
	}
}
