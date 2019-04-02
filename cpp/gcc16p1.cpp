//============================================================================
// Name        : gcc16p1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 100001, MV = 400001;
int n, a, c, tot = 0,
	lBad[MAX], rBad[MAX], lGood[MAX], rGood[MAX], pfxBad[MV], pfxGood[MV];
unordered_map<int, int> ranks;
vector<int> sortRanks;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> a >> c;

	set<int> tmpranks;

	for(int i = 0; i < a; i++){
		cin >> lGood[i] >> rGood[i];
		rGood[i]++;

		tmpranks.insert(lGood[i]);
		tmpranks.insert(rGood[i]);
	}

	for(int i = 0; i < c; i++){
		cin >> lBad[i] >> rBad[i];
		rBad[i]++;

		tmpranks.insert(lBad[i]);
		tmpranks.insert(rBad[i]);
	}

	sortRanks = vector<int>(tmpranks.begin(), tmpranks.end());
	int ctr = -1;
	for(int x : tmpranks)
		ranks[x] = ++ctr;

	for (int i = 0; i < a; ++i) {
		pfxGood[ranks[lGood[i]]]++;
		pfxGood[ranks[rGood[i]]]--;
	}

	for (int i = 0; i < c; ++i) {
		pfxBad[ranks[lBad[i]]]++;
		pfxBad[ranks[rBad[i]]]--;
	}

	int sz = sortRanks.size();

	for (int i = 1; i < sz; i++) {
		pfxGood[i] += pfxGood[i - 1];
		pfxBad[i] += pfxBad[i - 1];
	}

	for (int i = 0; i < sz - 1; i++){
		if(pfxGood[i] && !pfxBad[i])
			tot += sortRanks[i + 1] - sortRanks[i];
	}

	printf("%d\n", tot);
}
