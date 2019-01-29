//============================================================================
// Name        : PolynomialMadness.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MV = 150;
int n, d;
ll buf;

inline void synthetic(ll root, vector<ll> &begin, vector<ll> &end){
	int sz = begin.size() - 1;

	for (int i = 0; i < sz; ++i) {
		end.push_back(begin[i]);
		begin[i + 1] -= -root * begin[i];
	}
}

inline ll find_root(vector<ll> &begin){
	for (ll i = -150; i <= MV; ++i) {
		ll total = 0, cx = 1;

		for(int j = begin.size() - 1; j >= 0; j--){
			total += cx * begin[j];
			cx *= i;
		}

		if(total == 0L){
			return i;
		}
	}

	return -151;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> d;
		vector<ll> begin;

		for (int j = -1; j < d; ++j) {
			cin >> buf;
			begin.push_back(buf);
		}

		multiset<ll> roots;
		while(begin.size() > 1){
			ll root = find_root(begin);
			roots.insert(root);

			vector<ll> intermediate;
			synthetic(root, begin, intermediate);

			begin = intermediate;
		}

		for(ll root : roots){
			printf("%lld ", root);
		}
		printf("\n");
	}
}
