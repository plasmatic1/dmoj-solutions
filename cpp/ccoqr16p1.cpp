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
typedef unordered_map<int, vector<int>> ptlist;

const int MAX = 100001;
int n,
	x[MAX], y[MAX];
ptlist byx, byy;
ll tot = 0;

void sort_all(ptlist &map){
	for(auto it = map.begin(); it != map.end(); it++)
		sort(it->second.begin(), it->second.end());
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> x[i] >> y[i];

		byx[x[i]].push_back(y[i]);
		byy[y[i]].push_back(x[i]);
	}

	sort_all(byx);
	sort_all(byy);

	for (int i = 0; i < n; ++i) {
		vector<int> &row = byy[y[i]], &col = byx[x[i]];
		int rowidx = lower_bound(row.begin(), row.end(), x[i]) - row.begin(), colidx = lower_bound(col.begin(), col.end(), y[i]) - col.begin();
		tot += (ll)rowidx * (row.size() - rowidx - 1) * colidx * (col.size() - colidx - 1);
	}

	printf("%lld\n", tot << 1);
}