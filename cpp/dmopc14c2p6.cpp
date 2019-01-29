//============================================================================
// Name        : SelectiveCutting.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

//Full rewrite of code

#include <bits/stdc++.h>
//#define DEBUG

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

struct query{
	int i, a, b, q;

	query(int i0, int a0, int b0, int q0) : i(i0), a(a0), b(b0), q(q0){}

	query() : i(-1), a(-1), b(-1), q(-1){}

	friend bool operator<(const query &qa, const query &qb){
		return qa.q > qb.q;
	}
};

bool cmp(const p &a, const p &b){
	return a.second	>  b.second;
}

const int MAX = 100001;

int n, q, buf, buf2, buf3, totaltree[MAX], answers[MAX], max_mass, q_ptr = 0;
p trees[MAX];
query queries[MAX];

void add(int x, int z){
	for(; x < MAX; x += x & -x){
		totaltree[x] += z;
	}
}

int sum(int x){
	if(x == 0){
		return 0;
	}

	int sum = 0;

	for(; x > 0; x -= x & -x){
		sum += totaltree[x];
	}

	return sum;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> buf;

		trees[i] = p(i, buf);
	}

	cin >> q;

	for (int i = 0; i < q; ++i) {
		cin >> buf >> buf2 >> buf3;

		queries[i] = query(i, buf, buf2, buf3);
	}

//	assert(false);

	sort(trees, trees + n, cmp);
	sort(queries, queries + q);

	max_mass = queries[0].q;

	//Skip over ones that are too large
	while(max_mass > trees[0].second && q_ptr < q){
		max_mass = queries[++q_ptr].q;
	}

	bool brk = true;
	for (int i = 0; i < n && q_ptr < q;) {
		brk = true;

		while(trees[i].second >= max_mass && i < n){
#ifdef DEBUG
			printf("Adding tree %d (%d)\n", trees[i].first, trees[i].second);
#endif
			add(trees[i].first + 1, trees[i].second);
			i++;

			brk = false;
		}

		while(max_mass >= trees[i - 1].second && q_ptr < q){
#ifdef DEBUG
			printf("Solving query %d\n", queries[q_ptr].i);
#endif
			answers[queries[q_ptr].i] = sum(queries[q_ptr].b + 1) - sum(queries[q_ptr].a);
			max_mass = queries[++q_ptr].q;
		}

		if(brk && max_mass < trees[i - 1].second && max_mass >= trees[i].second){
			answers[queries[q_ptr].i] = sum(queries[q_ptr].b + 1) - sum(queries[q_ptr].a);
			max_mass = queries[++q_ptr].q;
		}
	}

	//Max mass is below min tree value
	for(; q_ptr < q; q_ptr++){
		answers[queries[q_ptr].i] = sum(queries[q_ptr].b + 1) - sum(queries[q_ptr].a);
	}

	for (int i = 0; i < q; ++i) {
		printf("%d\n", answers[i]);
	}
}
