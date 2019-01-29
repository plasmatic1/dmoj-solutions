//============================================================================
// Name        : StalinSort.cpp
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

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	int last = INT_MIN;

	for (int i = 0; i < n; ++i) {
		cin >> buf;

		if(buf >= last){
			printf("%d\n", buf);
			last = buf;
		}
	}
}
