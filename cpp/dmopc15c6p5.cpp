//============================================================================
// Name        : AClassicProblem.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct pi{
	int i, v;

	pi(int i0, int v0) : i(i0), v(v0){}
	pi() : i(-1), v(-1){}
};

const int MAX = 3000001;
int n, k,
	arr[MAX];
ll ans;
deque<pi> minq, maxq;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> k;

	for (int i = 1; i <= n; ++i) {
		cin >> arr[i];
	}

	// 2 Pointer

	minq.emplace_back(1, arr[1]);
	maxq.emplace_back(1, arr[1]);

	for(int l = 1, r = 1; r <= n; ){
		if(maxq.front().v - minq.front().v <= k){
			ans += r - l + 1;
			r++;

			while(!minq.empty() && minq.back().v >= arr[r]){
				minq.pop_back();
			}

			while(!maxq.empty() && maxq.back().v <= arr[r]){
				maxq.pop_back();
			}

			minq.emplace_back(r, arr[r]);
			maxq.emplace_back(r, arr[r]);
		}
		else{
			l++;

			while(!minq.empty() && minq.front().i < l){
				minq.pop_front();
			}

			while(!maxq.empty() && maxq.front().i < l){
				maxq.pop_front();
			}
		}
	}

	printf("%lld\n", ans);
}
