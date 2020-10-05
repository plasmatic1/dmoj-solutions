//============================================================================
// Name        : graph2p1.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 1001;
int n, buf,
	dset[MAX];
vector<int> roots[MAX];

int rt(int v){
	return v == dset[v] ? v : dset[v] = rt(dset[v]);
}

void unite(int v, int w){
	v = rt(v), w = rt(w);
	if(v == w) return;
	if (v > w) swap(v, w);
	dset[w] = v;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	iota(dset, dset + n + 1, 0);

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> buf;
			if(buf) unite(i, j);
		}
	}

	for(int i = 1; i <= n; i++) roots[rt(i)].push_back(i);

	for(int i = 1; i <= n; i++){
// 		if(roots[i].size() > 0){
			for(int j : roots[i]) cout << j << ' ';
			cout << '\n';
// 		}
	}
}