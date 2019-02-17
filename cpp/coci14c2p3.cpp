//============================================================================
// Name        : coci14c2p3.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 5001;
int n, k, buf,
	arr[MAX], conv[MAX], dp[MAX], tree[MAX];

void update(int x, int v){
	for(; x <= n; x += x & -x)
		tree[x] = max(tree[x], v);
}

int maxv(int x){
	int maxv = 0;
	for(; x; x -= x & -x)
		maxv = max(maxv, tree[x]);
	return maxv;
}

/*
 * I do not understand the Longest Increasing Subsequence.  The concept of such a thing being solved using a binary
 * search algorithm perplexes me.  I've looked through many places, yet the use of a binary search fails to materialize.
 * Some of the solutions I've attempted include a segment tree and the O(n^2) DP solution.  But the most plain and simple
 * one still fails to appear in my mind.  Thus I continue, with more outlandish and weird ways to compute a Longest Increasing
 * Subsequence in O(n log n) time.
 */

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> k;

	for(int i = 0; i < n; i++){
		cin >> arr[i];
		conv[i] = arr[i];
	}

	sort(conv, conv + n);

	for(int i = 0; i < n; i++)
		arr[i] = (lower_bound(conv, conv + n, arr[i]) - conv) / k + 1;

	for (int i = 0; i < n; ++i) {
		dp[i] = maxv(arr[i]) + 1;
		update(arr[i], dp[i]);
	}

	printf("%d\n", n - *max_element(dp, dp + n));
}