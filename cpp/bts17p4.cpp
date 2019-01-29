//============================================================================
// Name        : WetMud.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <algorithm>
#include <cstdio>
#include <utility>
#include <vector>
#include <assert.h>

using namespace std;
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;

typedef pair<int, int> p;

bool comp(const p &a, const p &b){
	if(a.second < b.second){
		return true;
	}
	else if(a.second > b.second){
		return false;
	}
	return a.first > b.first;
}

int n, m, j, mud[1000000];

int main() {
	scanf("%d %d %d", &n, &m, &j);

	fill(mud, mud + n + 1, -1);

	for (int i = 0; i < m; ++i) {
		int a, b;
		scanf("%d %d", &a, &b);

//		a--;
//		printf("pos %d, min %d\n", a, b);

		mud[a] = b;
	}

	mud[n + 1] = 0;

//	assert(false);

	int pos = 0, mins = 0;
	while(pos <= n){
		vector<p> q;
		for(int i = pos + j; i > pos; i--){
			if(mud[i] != -1){
				q.push_back(p(i, mud[i]));
			}
		}
		sort(q.begin(), q.end(), comp);

//		printf("pos: %d, mins: %d, q's: [", pos, mins);
//		for(p pp : q){
//			printf("(%d, %d), ", pp.first, pp.second);
//		}
//		printf("]

		if(q.size() == 0){
			break;
		}

		mins = max(mins, q[0].second);
		pos = q[0].first;
	}

	if(pos < n){
		printf("-1\n");
		return 0;
	}
	printf("%d\n", mins);

	return 0;
}
