//============================================================================
// Name        : Tourney.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct p{
	int i, skill;

	p(int i0, int skill0) : i(i0), skill(skill0){}
	p() : i(-1), skill(-1){}

	friend bool operator<(const p &a, const p &b){
		return a.skill < b.skill;
	}

	friend bool operator>(const p &a, const p &b){
		return a.skill > b.skill;
	}
};

const int MAX = (1 << 20) + 1;
int n0, n, m, bi, bs, buf;
char ins;
p totaltree[MAX * 2 + 1];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n0 >> m;
	n = 1 << n0;

	for (int i = 0; i < n; ++i) {
		cin >> buf;
		totaltree[n + i] = {i + 1, buf};
	}

	for (int i = n - 1; i > 0; --i) {
		totaltree[i] = max(totaltree[i * 2], totaltree[i * 2 + 1]);
	}

	for (int i = 0; i < m; ++i) {
		cin >> ins;

		if(ins == 'R'){
			cin >> bi >> bs;

			int ind = n + bi - 1;
			totaltree[ind] = {bi, bs};

			for (int i = ind / 2; i > 0; i >>= 1) {
				totaltree[i] = max(totaltree[i * 2], totaltree[i * 2 + 1]);
			}
		}
		else if(ins == 'W'){
			printf("%d\n", totaltree[1].i);
		}
		else{
			//ins == 'S'
			cin >> bi;

			int cnt = -1;
			for (int i = n + bi - 1; i > 0; i >>= 1) {
				cnt += totaltree[i].i == bi;
			}
			printf("%d\n", cnt);
		}
	}
}
