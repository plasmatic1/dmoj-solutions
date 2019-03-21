//============================================================================
// Name        : usaco19febbronze1.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 101, MV = 100001;
int n, l[MAX], r[MAX];
string type[MAX];

int main(){
	freopen("traffic.in", "r", stdin);
	freopen("traffic.out", "w", stdout);

	cin >> n;

	for (int i = 0; i < n; ++i)
		cin >> type[i] >> l[i] >> r[i];

	int lin = INT_MAX, rin = INT_MIN, lout = INT_MAX, rout = INT_MIN;

	for(int i = 0; i < MV; i++){
		int curl = i, curr = i;
		bool pass = true;
		for(int j = 0; j < n; j++){
			if(type[j] == "none"){
				if(curl > r[j] || curr < l[j]){
					pass = false;
					break;
				}
				curl = max(curl, l[j]);
				curr = min(curr, r[j]);
			}
			else if(type[j] == "on")
				curl += l[j], curr += r[j];
			else if(type[j] == "off")
				curl -= r[j], curr -= l[j];

			if(curl < 0) curl = 0;
		}

		if(pass){
			lin = min(lin, i);
			lout = min(lout, curl);
			rin = max(rin, i);
			rout = max(rout, curr);
		}
	}

	assert(lin != INT_MAX && lout != INT_MAX && rin != INT_MIN && rout != INT_MIN);

	printf("%d %d\n%d %d\n", lin, rin, lout, rout);
}
