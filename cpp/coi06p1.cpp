//============================================================================
// Name        : coi06p1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 500001;
int n, ctr = 1,
	arr[MAX], tree[MAX];
deque<int> deq;
ll tot = 0;
unordered_map<int, int> ranks;

void add(int x, int v){
	for(; x <= ctr; x += x & -x)
		tree[x] += v;
}

int sum(int x){
	int sum = 0;
	for(; x; x -= x & -x)
		sum += tree[x];
	return sum;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n;

	set<int> tmprank;
	for(int i = 0; i < n; i++)
		cin >> arr[i], tmprank.insert(arr[i]);

	for(int i : tmprank)
		ranks[i] = ctr++;
	ctr--;

	for(int i = n - 1; i; i--){
		while(!deq.empty() && deq.back() < arr[i]){
			add(ranks[deq.back()], -1);
			deq.pop_back();
		}

		add(ranks[arr[i]], 1);
		deq.push_back(arr[i]);

		int upsum = sum(ranks[arr[i - 1]]);
		if((size_t)upsum < deq.size())
			upsum++;

		tot += upsum + (upsum == 0);
	}

	printf("%lld\n", tot);
}