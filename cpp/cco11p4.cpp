//============================================================================
// Name        : Reorganization.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
//#define DEBUG

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

int n, buf;
map<int, int> supervisor;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	supervisor[INT_MIN] = INT_MIN;

	for (int i = 0; i < n; ++i) {
		cin >> buf;
		//i: id, buf: rank

#ifdef DEBUG
		printf(" --- id=%d, rank=%d\n", i, buf);
#endif

		auto it = supervisor.upper_bound(buf);

		if(it == supervisor.begin()){
			printf("NO\n");
			exit(0);
		}

		it--;

		int val = it->second + 1;

#ifdef DEBUG
		printf("sv: id=%d, cnt=%d (ncnt=%d)\n", it->first, it->second, val);
#endif

		if(it->first == INT_MIN || val >= 2){
			supervisor.erase(it);
		}
		else{
			supervisor[it->first] = val;
		}

		supervisor[buf] = 0;

#ifdef DEBUG
		printf("supervisor: [");
		for(pair<int, int> pairr : supervisor){
			printf("(%d, %d), ", pairr.first, pairr.second);
		}
		printf("]\n");
#endif
	}

	printf("YES\n");
}
