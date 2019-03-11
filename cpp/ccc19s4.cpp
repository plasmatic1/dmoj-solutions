//============================================================================
// Name        : ccc19s4.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct p{
	int i;
	ll v;
};

const int MAX = 1000001, MLOG = 21;
int n, k,
	day[MAX], sparse[MLOG][MAX];
ll arr[MAX], dp[MAX];
deque<p> withRMQ;
deque<int> withoutRMQ;

inline void build(){
	for(int i = 1; i < MLOG; i++){
		int jmp = 1 << (i - 1), end = n - jmp;
		for(int j = 1; j <= end; j++)
			sparse[i][j] = max(sparse[i - 1][j], sparse[i - 1][j + jmp]);
	}
}

inline int qmax(int l, int r){
	int delta = r - l + 1, bit = 31 - __builtin_clz(delta);
	return max(sparse[bit][l], sparse[bit][r - (1 << bit) + 1]);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> k;

	int counter = 0, cday = 0;
	for(int i = 1; i <= n; i++){
		cin >> arr[i];
		sparse[0][i] = arr[i];

		if(counter == 0) cday++;
		day[i] = cday;
		counter = (counter + 1) % k;
	}

	build();

	cday = 0;
	int cmax = 0;
	for(int i = 1; i <= n; i++){
		if(day[i] > cday){
			for(int j = max(0, i - k); j < i; j++){
				ll withRMQAlt = dp[j] + qmax(j + 1, i);
				while(!withRMQ.empty() && withRMQ.back().v < withRMQAlt)
					withRMQ.pop_back();
				while(!withoutRMQ.empty() && dp[withoutRMQ.back()] < dp[j])
					withoutRMQ.pop_back();

				withRMQ.push_back({j, withRMQAlt});
				withoutRMQ.push_back(j);
			}

			cday++;
			cmax = 0;
		}

		cmax = max(cmax, (int)arr[i]);

		while(withRMQ.front().i < i - k)
			withRMQ.pop_front();
		while(withoutRMQ.front() < i - k)
			withoutRMQ.pop_front();

		dp[i] = max(withRMQ.front().v, dp[withoutRMQ.front()] + cmax);
	}

	printf("%lld\n", dp[n]);
}
