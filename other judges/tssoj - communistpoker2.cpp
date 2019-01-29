//============================================================================
// Name        : CommunistPoker.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct pi{
	int i, amt;

	pi(int i0, int a0) : i(i0), amt(a0){}
	pi() : i(-1), amt(-1){}
};

const int MAX = 10001;
int n, k, ba, bb,
	need[MAX], money[MAX];
vector<int> matrix[MAX];
deque<pi> nextt;
bool vis[MAX];
ll moves = 0;

int dfs(int st){
	if(vis[st]){
		return need[st];
	}

	vis[st] = true;
	int total = -money[st];

	for(int adj : matrix[st]){
		total += max(0, dfs(adj));
	}

	return need[st] = total;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> k;

	for (int i = 1; i <= n; ++i) {
		cin >> money[i];
	}

	for (int i = 0; i < k; ++i) {
		cin >> ba >> bb;
		assert(ba < bb);

		matrix[ba].push_back(bb);
	}

	// Init DFS Array

	for (int i = 1; i <= n; ++i) {
		dfs(i);
	}

//	printf("need: ");
//	for (int i = 0; i < n + 1; ++i) {
//		printf("%d, ", need[i]);
//	}
//	printf("\n");

	// Counting moves

	for(int i = 1; i <= n; i++){
		int have = money[i], maxsend = 0;

		for(int adj : matrix[i]){
			maxsend = max(maxsend, need[adj]);
		}

		int tsend = maxsend * matrix[i].size();
//		printf("i=%d have=%d maxsend=%d tsend=%d\n", i, have, maxsend, tsend);

		if(tsend > have){
			printf("-1\n");
			return 0;
		}

		moves += maxsend;
		for(int adj : matrix[i]){
			need[adj] = 0;
			money[adj] += maxsend;
		}
	}

	printf("%lld\n", moves);
}
