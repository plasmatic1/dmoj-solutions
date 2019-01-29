//============================================================================
// Name        : Gates.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pp;

const int MAX = 100000;

int g, p, buf, curr = 1, ltime = INT_MAX, total = 0;
pp gates[MAX];

bool cmp(const pp &a, const pp &b){
	if(a.second == b.second){
		return a.first < b.first;
	}
	return a.second < b.second;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> g >> p;

	for (int i = 0; i < p; ++i) {
		cin >> buf;
		gates[i] = pp(i, buf);
	}

	sort(gates, gates + p, cmp);

	for (int i = 0; i < p; ++i) {
		if(gates[i].first < ltime && curr <= gates[i].second){
			curr++;
			total++;
		}
		else{
			ltime = min(ltime, gates[i].first);
		}
//		printf("curr i: %d, curr gate: (%d, %d), total: %d. ltime: %d\n", curr, gates[i].first, gates[i].second, total, ltime);
	}

	cout << total << endl;
}
