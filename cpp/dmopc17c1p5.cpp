//============================================================================
// Name        : IntimidatingArrays.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct p{
	int i, x;
};

struct qu{
	int i, l, r;

	bool operator<(const qu &o) const {
		return l > o.l;
	}
};

const int MAX = 1000001;
int n, q, bl, br,
	arr[MAX], ans[MAX], tree[MAX];
qu queries[MAX];
deque<p> deq;

void add(int x, int v){
	for(; x <= n; x += x & -x)
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
	cin.tie(NULL);

	cin >> n >> q;

	for (int i = 1; i <= n; ++i)
		cin >> arr[i];

	for (int i = 0; i < q; ++i) {
		cin >> bl >> br;
		queries[i] = {i, bl, br};
	}

	sort(queries, queries + q);

	// Offline

	int qptr = 0;
	for(int i = n; i > 0; i--){
		while(!deq.empty() && arr[i] >= deq.back().x){
			add(deq.back().i, -1);
			deq.pop_back();
		}

		add(i, 1);
		deq.push_back({i, arr[i]});

		while(qptr < q && queries[qptr].l == i){
			ans[queries[qptr].i] = sum(queries[qptr].r);
			qptr++;
		}
	}

	for (int i = 0; i < q; ++i)
		printf("%d\n", ans[i]);
}
