//============================================================================
// Name        : BarkingDogs.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct p{
	int a, b, l;

	p(int a0, int b0, int l0) : a(a0), b(b0), l(l0){};

	friend bool operator<(const p &a, const p &b){
		return a.b > b.b;
	}
};

const int MAX = 1001;
int d, f, t, buf, buf2,
	dogs[MAX], dist[MAX], cooldown[MAX], counts[MAX];

vector<int> matrix[MAX];
priority_queue<p> nextt;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> d;

	for (int i = 1; i <= d; ++i) {
		cin >> dogs[i];
	}

	cin >> f;

	for (int i = 0; i < f; ++i) {
		cin >> buf >> buf2;
		matrix[buf].push_back(buf2);
	}

	cin >> t;

	nextt.emplace(1, 0, 0);
	counts[1]++;

	fill(dist, dist + d, INT_MIN);
	dist[1] = 0;

	while(!nextt.empty()){
		p curr = nextt.top();
		int level = dist[curr.a];
		nextt.pop();

		for(int adj : matrix[curr.a]){
			int newtime = level + dogs[adj];

			if(newtime > t || level <= dist[adj]){
				continue;
			}//

			dist[adj] = newtime;
			counts[adj]++;
			nextt.emplace(adj, newtime, curr.l + 1);
		}
	}

	for (int i = 1; i <= d; ++i) {
		printf("%d\n", counts[i]);
	}
}
