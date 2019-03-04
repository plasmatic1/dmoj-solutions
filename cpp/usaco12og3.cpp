//============================================================================
// Name        : usaco12og3.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 20, MS = (1 << MAX) + 20;
int n, tot = 0,
	arr[MAX], eles[MAX], ret[MS], retmsk[MS];
bool possible[MS];

inline int calc(int l, int r){
	int ptr = 1, len = r - l, msub = 1 << len;

	ret[0] = retmsk[0] = 0;
	for (int i = 1; i < msub; ++i) {
		// Current subset to start counting sums from
		int sz = 0;
		for(int j = 0; j < len; j++)
			if((i >> j) & 1)
				eles[sz++] = arr[l + j];

		// Get all possible organizations of cows
		int msub2 = 1 << sz;
		for (int j = 0; j < msub2; ++j) {
			int sum = 0;
			for (int k = 0; k < sz; ++k) {
				if((j >> k) & 1)
					sum += eles[k];
				else
					sum -= eles[k];
			}
			retmsk[ptr] = i << l;
			ret[ptr++] = sum;
		}
	}

	return ptr;
}

unordered_map<int, vector<int>> sums;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for(int i = 0; i < n; i++)
		cin >> arr[i];

	int mid = n >> 1, sz = calc(mid, n);
	for (int i = 0; i < sz; ++i)
		sums[ret[i]].push_back(retmsk[i]);

	sz = calc(0, mid);
	for (int i = 0; i < sz; ++i)
		for(int mask : sums[-ret[i]])
			possible[mask | retmsk[i]] = true;

	int msub = 1 << n;
	for (int i = 1; i < msub; i++)
		tot += possible[i];

	printf("%d\n", tot);
}
