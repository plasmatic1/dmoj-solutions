//============================================================================
// Name        : EbolaOutbreak.cpp
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

int n, m, bc, bp, cnt = 0;

bool infected[MAX];
vector<int> classes[MAX], people[MAX]; // Which people are in which classes; which classes is each person in
deque<int> nextt;
unordered_set<int> matrix[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	for (int i = 0; i < m; ++i) {
		cin >> bc;

		for (int j = 0; j < bc; ++j) {
			cin >> bp;

			classes[i].push_back(bp);
			people[bp].push_back(i);

			if(bp == 1){
				infected[i] = true;
				nextt.push_back(i);
			}
		}
	}

	// Building adj matrix

	for (int i = 0; i < m; ++i) {
		for(int psn : classes[i]){
			for(int pclass : people[psn]){
				matrix[i].insert(pclass);
			}
		}
	}

	// BFS

	while(!nextt.empty()){
		int curr = nextt.front();
		nextt.pop_front();

		for(int adj : matrix[curr]){
			if(infected[adj]){
				continue;
			}

			infected[adj] = true;
			nextt.push_back(adj);
		}
	}

	// Building output

	set<int> ppl;
	ppl.insert(1);

	for (int i = 0; i < m; ++i) {
		if(infected[i]){
			for(int psn : classes[i]){
				ppl.insert(psn);
			}
		}
	}

	// Printing

	printf("%d\n", ppl.size());

	for(int person : ppl){
		printf("%d ", person);
	}
	printf("\n");
}
