//============================================================================
// Name        : ncp3.cpp
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
int n, m, pfx[MAX], bp, bt, maxsum = INT_MIN;
string tmp;
bool reversee = false;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	for (int i = 1; i <= n; ++i) {
		cin >> pfx[i];
		pfx[i] += pfx[i - 1];
	}

	// PreCompute Max Sum

	int maxend = 0;

	for (int i = 1; i <= n; ++i) {
		maxend += pfx[i] - pfx[i - 1];

		if(maxsum < maxend){
			maxsum = maxend;
		}

		if(maxend < 0){
			maxend = 0;
		}
	}

	// Query

	for (int i = 0; i < m; ++i) {
		cin >> tmp;

		if(tmp == "GET-SUM"){
			cin >> bp >> bt;

			if(!reversee){
				printf("%d\n", pfx[bp + bt - 1] - pfx[bp - 1]);
			}
			else{
				printf("%d\n", pfx[n - bp + 1] - pfx[n - bp - bt + 1]);
			}
		}
		else if(tmp == "MAX-SUM"){
			printf("%d\n", maxsum);
		}
		else{ // tmp == REVERSE
			reversee = !reversee;
		}
	}
}
