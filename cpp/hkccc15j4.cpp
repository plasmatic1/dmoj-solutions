//============================================================================
// Name        : WhereToBuildMyHouse.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cstdio>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> p;

bool comp(p a, p b){
	return a.first < b.first;
}

int main() {
	int a, b, maxx = 0, curr = 0;
	vector<p> l;
	scanf("%d", &a);
	scanf("%d", &b);
	for (int i = 0; i < b; ++i) {
		int c, d;
		scanf("%d %d", &c, &d);
		l.push_back(p(c, d));
	}

//	int s = l.size() - 1;
	sort(l.begin(), l.end(), comp);

//	maxx = max(l[0].first, a - l[s].second);

	for(p e : l){
		if(e.first > curr){
			int delta = e.first - curr;
			if(delta > maxx){
				maxx = delta;
			}
		}
		if(curr < e.second){
			curr = e.second;
		}
	}

	printf("%d\n", maxx);
	return 0;
}
