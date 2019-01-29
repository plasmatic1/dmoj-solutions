//============================================================================
// Name        : StupendousBowties.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct p{
	int x, y;
};

const int MAX = 100001;

int n, bx, by;
ll total = 0;
unordered_map<int, vector<int>> rows, cols;
p pts[MAX];

void sortmp(unordered_map<int, vector<int>> &mp){
	for(auto it = mp.begin(); it != mp.end(); it++){
		sort(it->second.begin(), it->second.end());
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> bx >> by;

		rows[by].push_back(bx);
		cols[bx].push_back(by);
		pts[i] = {bx, by};
	}

	// Sorting

	sortmp(rows);
	sortmp(cols);

	// Binary Search

	for (int i = 0; i < n; ++i) {
		auto ptrr = lower_bound(rows[pts[i].y].begin(), rows[pts[i].y].end(), pts[i].x),
				ptrc = lower_bound(cols[pts[i].x].begin(), cols[pts[i].x].end(), pts[i].y);

		total += (ll)(ptrr - rows[pts[i].y].begin()) * (ll)(rows[pts[i].y].end() - ptrr - 1) *
				(ll)(ptrc - cols[pts[i].x].begin()) * (ll)(cols[pts[i].x].end() - ptrc - 1);
	}

	// Output

	printf("%lld\n", total * 2L);
}
