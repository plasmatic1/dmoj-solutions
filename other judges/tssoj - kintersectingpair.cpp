//============================================================================
// Name        : KIntersectingPairs.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

#define MAX 100000
#define MV 32769
#define MK 14

int n, k,
	arr[MAX];
ll ttl = 0;
int cnt[MV];

inline int flip_bit(int v, int bit){
	return v & bit ? v ^ bit : v | bit;
}

ll alter(int v, int changed, int pos){
	if(changed == k){
		return cnt[v];
	}

	if(pos >= MK){
		return 0;
	}

	if(k - changed == MK - pos){
		for (int i = pos; i < MK; ++i) {
			v = flip_bit(v, 1 << i);
		}

		return cnt[v];
	}

	return alter(flip_bit(v, 1 << pos), changed + 1, pos + 1) + alter(v, changed, pos + 1);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> k;

	for (int i = 0; i < n; ++i) {
		cin >> arr[i];
	}

	cnt[arr[n - 1]]++;

	for (int i = n - 2; i >= 0; --i) {
//		printf("i=%d x=%lld\n", i, x);

		ttl += alter(arr[i], 0, 0);
		cnt[arr[i]]++;
	}

	printf("%lld\n", ttl);
}
