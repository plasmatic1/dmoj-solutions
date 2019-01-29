//============================================================================
// Name        : TudorAndThePusheens.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 1000001;
int n, m, s, t, ba, bb,
	levels[MAX];

vector<int> matrix[MAX];
deque<int> nextt;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	for (int i = 0; i < m; ++i) {
		cin >> ba >> bb;

		matrix[ba].push_back(bb);
		matrix[bb].push_back(ba);
	}

	fill(levels, levels + n + 1, -1);

	cin >> s >> t;

	levels[s] = 0;
	nextt.push_back(s);

	while(!nextt.empty()){
		int curr = nextt.front(), level = levels[curr];
		nextt.pop_front();

		for(int adj : matrix[curr]){
			if(levels[adj] != -1){
				continue;
			}

			levels[adj] = level + 1;
			nextt.push_back(adj);
		}
	}

	printf("%d\n", m - levels[t]);
}
