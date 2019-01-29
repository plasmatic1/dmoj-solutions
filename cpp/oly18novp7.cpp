//============================================================================
// Name        : CatchTheCat.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 300001;
int x, y,
	dists[MAX];
deque<int> nextt;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> x >> y;
	memset(dists, 0x3f, sizeof(dists));

	dists[x] = 0;
	nextt.push_back(x);

	while(!nextt.empty()){
		int curr = nextt.front(), nlevel = dists[curr] + 1;
		nextt.pop_front();

		for(int adj : {curr + 1, curr - 1, curr * 2}){
			if(adj < 0 || adj > 100000 || nlevel >= dists[adj]){
				continue;
			}

			dists[adj] = nlevel;
			nextt.push_back(adj);
		}
	}

	printf("%d\n", dists[y]);
}
