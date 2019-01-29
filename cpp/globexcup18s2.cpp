//============================================================================
// Name        : TestScores.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

struct test{
	int mark, inc;

	test(int m0, int i0) : mark(m0), inc(i0){}
	test() : mark(-1), inc(-1){}

	friend bool operator<(const test &a, const test &b){
		return a.inc < b.inc;
	}
};

const int MAX = 200001;
int n, m, k, ba, bb;
ll req, tot = 0, reqstudy = 0;
test tests[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m >> k;
	req = (ll)n * (ll)k;

	for (int i = 0; i < n; ++i) {
		cin >> ba >> bb;
		tests[i] = test(ba, bb);
		tot += (ll)ba;
	}

	sort(tests, tests + n);

	int ptr = 0;
	while(tot < req){
		ll dif = req - tot, attainable = m - tests[ptr].mark;

		if(dif > attainable){
			tot += (ll)attainable;
			reqstudy += (ll)attainable * (ll)tests[ptr].inc;
		}
		else{
			tot = req;
			reqstudy += (ll)dif * (ll)tests[ptr].inc;
		}

		ptr++;
	}

	printf("%lld\n", reqstudy);
}
