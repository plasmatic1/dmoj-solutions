//============================================================================
// Name        : HopScotch2.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, ll> p;

const int MAX = 8388608 + 2;
int n, k, furthest, curr = n, jump_cnt = 0, jumps[MAX], parent[MAX];
ll ans = 0, sq[MAX], dist[MAX], buf;
deque<p> deq;

int main() {
	scanf("%d %d", &n, &k);
	deq.push_back(p(0, 0L));

	for (int i = 1; i <= n; ++i) {
		scanf("%lld", &buf);
//		printf(" -- on i %d, buf is %d\n", i, buf);

		while(i > deq.front().first + k){
			deq.pop_front();
		}

		ll distt = deq.front().second + buf;
		int parentt = deq.front().first;

//		printf(" - second check, dist is %d\n", distt);

		while(distt <= deq.back().second){
			deq.pop_back();
		}

		deq.push_back(p(i, distt));
		dist[i] = distt;
		parent[i] = parentt;

//		printf("deq: [");
//		for(p pp : deq){
//			printf("(%d, %lld), ", pp.first, pp.second);
//		}
//		printf("]\n");
	}

	while(deq.front().first + k <= n){
		deq.pop_front();
	}

	p end = deq.front();
	parent[n + 1] = end.first;
	curr = n + 1;

	while(1){
		curr = parent[curr];
		jumps[jump_cnt] = curr;
		jump_cnt++;

		if(parent[curr] == 0){
			break;
		}
	}

	reverse(jumps, jumps + jump_cnt);

	printf("%lld\n", end.second);
	int jump_cnt0 = jump_cnt - 1;

	for (int i = 0; i < jump_cnt0; ++i) {
		printf("%d ", jumps[i]);
	}
	printf("%d\n", jumps[jump_cnt0]);

	return 0;
}
