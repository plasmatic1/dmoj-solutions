//============================================================================
// Name        : RoyalGuards.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 100001;
int n, m, bx, by, lastx, lasty;
ll cnt = 0;

unordered_map<int, vector<int>> rows, cols;

inline void sortall(unordered_map<int, vector<int>> &mp){
	for (auto it = mp.begin(); it != mp.end(); ++it) {
		sort(it->second.begin(), it->second.end());
	}
}

inline int diff(vector<int> &vec, int a, int b){
	return (upper_bound(vec.begin(), vec.end(), b)) -
			(lower_bound(vec.begin(), vec.end(), a));
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> bx >> by;

		rows[by].push_back(bx);
		cols[bx].push_back(by);
	}

	sortall(rows);
	sortall(cols);

	cin >> m;

	cin >> lastx >> lasty;
	for (int i = 1; i < m; ++i) {
		cin >> bx >> by;

		if(bx == lastx){
			//this is vertical

			cnt += diff(cols[bx], min(lasty, by), max(lasty, by));
		}
		else{
			//by == lastx (this is horizontal)

			cnt += diff(rows[by], min(lastx, bx), max(lastx, bx));
		}

		lastx = bx;
		lasty = by;
	}

	printf("%lld\n", cnt);
}
