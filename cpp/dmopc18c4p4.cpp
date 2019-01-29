//============================================================================
// Name        : DrHenriAndLabData.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

struct qu{
	int i, l, r, k;

	qu(int i0, int l0, int r0, int k0) : i(i0), l(l0), r(r0), k(k0){}
	qu() : i(-1), l(-1), r(-1), k(-1){}

	friend bool operator<(const qu &a, const qu &b){
		return a.k < b.k;
	}
};

struct en{
	int i, x;

	en(int i0, int x0) : i(i0), x(x0){}
	en() : i(-1), x(-1){}

	friend bool operator<(const en &a, const en &b){
		return a.x < b.x;
	}
};

const int MAX = 200001;
int n, q, ba, bb, bc;
ll counttree[MAX], ans[MAX];
qu queries[MAX];
en entries[MAX];

void add(int x, ll v){
	for(; x <= n; x += x & -x){
		counttree[x] += v;
	}
}

ll sum(int x){
	ll summ = 0;

	for(; x > 0; x -= x & -x){
		summ += counttree[x];
	}

	return summ;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> q;

	for (int i = 1; i <= n; ++i) {
		cin >> ba;
		entries[i] = en(i, ba);
	}

	for (int i = 1; i <= q; ++i) {
		cin >> ba >> bb >> bc;
		queries[i] = qu(i, ba, bb, bc);
	}

	sort(entries + 1, entries + n + 1);
	sort(queries + 1, queries + q + 1);

//	printf("queries: ");
//			for (int i = 0; i < q + 1; ++i) {
//				printf("(k=%d), ", queries[i].k);
//			}
//			printf("\n");

	// First offline run

	for(int qptr = 1, eptr = 1; qptr <= q; ){
		while(queries[qptr].k > entries[eptr].x && eptr <= n){
			add(entries[eptr].i, entries[eptr].x);
			eptr++;
		}

		while((eptr > n || queries[qptr].k <= entries[eptr].x) && qptr <= q){
			ans[queries[qptr].i] -= sum(queries[qptr].r) - sum(queries[qptr].l - 1);
			qptr++;
		}
	}

//	printf("ans: ");
//	for (int i = 0; i < q + 1; ++i) {
//		printf("%d, ", ans[i]);
//	}
//	printf("\n");

	// Reset

	reverse(entries + 1, entries + n + 1);
	reverse(queries + 1, queries + q + 1);
	memset(counttree, 0, sizeof(counttree));

//	printf("queries: ");
//	for (int i = 0; i < q + 1; ++i) {
//		printf("(k=%d), ", queries[i].k);
//	}
//	printf("\n");

	// Second offline run

	for(int qptr = 1, eptr = 1; qptr <= q; ){
		while(queries[qptr].k <= entries[eptr].x && eptr <= n){
//			printf("adding k=%d eptr=%d v=%d\n", queries[qptr].k, entries[eptr].i, entries[eptr].x);

			add(entries[eptr].i, entries[eptr].x);
			eptr++;
		}

		while((eptr > n || queries[qptr].k > entries[eptr].x) && qptr <= q){
//			printf("answer to k=%d qu=%d is %lld\n", queries[qptr].k, queries[qptr].i, sum(queries[qptr].r) - sum(queries[qptr].l - 1));
			ans[queries[qptr].i] += sum(queries[qptr].r) - sum(queries[qptr].l - 1);
			qptr++;
		}
	}

	// Print

	for(int i = 1; i <= q; i++){
		printf("%lld\n", ans[i]);
	}
}
