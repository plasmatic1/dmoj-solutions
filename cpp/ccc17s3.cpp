//============================================================================
// Name        : NailedIt.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 1000000, MAXL = 2001;
int n, buf, wood[MAXL];//, sums[MAXL * 2];

unordered_map<int, int> fences;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	int maxl = INT_MIN;
	for (int i = 0; i < n; ++i) {
		cin >> buf;
		wood[buf]++;

		maxl = max(maxl, buf);
	}

	for (int i = 1; i <= maxl; ++i) {
		if(wood[i]){
			for (int j = i; j <= maxl; ++j) {
				if(i == j){
					fences[i << 1] += wood[i] >> 1;
				}
				else if(wood[j]){
					fences[i + j] += min(wood[i], wood[j]);
				}
			}
		}
	}

//	for(p fence : fences){
//		printf("height: %d -> l=%d\n", fence.first, fence.second);
//	}

	maxl = INT_MIN;
	int total = 0;

	//first = height, second = length
	for(p fence : fences){
		maxl = max(maxl, fence.second);
	}

	for(p fence : fences){
		if(fence.second == maxl){
			total++;
		}
	}

	printf("%d %d\n", maxl, total);
}
