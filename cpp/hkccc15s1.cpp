//============================================================================
// Name        : CountNumberOfPairs.cpp
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

	p(int i0, int v0) : i(i0), v(v0){}
	p() : i(-1), v(-1){}

	friend bool operator<(const p &a, const p &b){
		return a.v < b.v;
	}
};

const int MAX = 100001;
int n, m, buf,
		tree[MAX];
ll tot = 0;
p arr[MAX], queries[MAX];

void add(int x, int z){
	for(; x <= n; x += x & -x){
		tree[x] += z;
	}
}

int sum(int x){
	int summ = 0;

	for(; x > 0; x -= x & -x){
		summ += tree[x];
	}

	return summ;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	for (int i = 1; i <= n; ++i) {
		cin >> buf;
		arr[i] = p(i, buf);
	}

	sort(arr + 1, arr + n + 1);
	copy(arr + 1, arr + n + 1, queries + 1);
	reverse(queries + 1, queries + n + 1);

	int aptr = 1;
	for(int i = 1; i <= n; i++){
		while(aptr <= n && queries[i].v + arr[aptr].v <= m){
			add(arr[aptr].i, 1);
			aptr++;
		}

		tot += (ll)sum(n) - (ll)sum(queries[i].i);
	}

	printf("%lld\n", tot % (1000000007));
}