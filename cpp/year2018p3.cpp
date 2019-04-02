//============================================================================
// Name        : year2018p3.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
struct p{
	int i, v;
};

const int MAX = 200001, MV = 2000000001;
int n, m, k,
	arr[MAX];

inline ll sim(int target){
	ll req = 0;
	deque<p> deq;
	int curAdd = 0;

	for (int i = 0; i < n; ++i) {
		while(!deq.empty() && deq.front().i + m <= i){
			curAdd -= deq.front().v;
			deq.pop_front();
		}

		int diff = target - arr[i] - curAdd;

		if(diff > 0){
			req += diff;
			curAdd += diff;
			deq.push_back({i, diff});
		}
	}

	return req;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m >> k;

	for(int i = 0; i < n; i++)
		cin >> arr[i];

	int l = 0, r = MV;
	while(l + 1 < r){
		int mid = ((ll)l + r) >> 1;

		if(sim(mid) > k)
			r = mid;
		else
			l = mid;
	}

	printf("%d\n", l);
}
