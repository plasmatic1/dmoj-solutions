//============================================================================
// Name        : Contagion.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
using namespace std;

#define ll long long

struct e{
	int a;
	ll b;

	e(int aa, ll bb) : a(aa), b(bb){}
	e() : a(0), b(0){}

	friend bool operator<(const e &a, const e &b){
		return a.b > b.b;
	}
};

const int MAXN = 3000, MAXQ = 1000000;

int n, src, q, a, b;
ll dist[MAXN], queries[MAXQ], maxh = -1;
e pts[MAXN];

vector<int> nextt;

bool in[MAXN];

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d %d", &a, &b);
		pts[i] = e(a, b);
	}

	scanf("%d", &src);
	scanf("%d", &q);

	for (int i = 0; i < q; ++i) {
		scanf("%lld", &queries[i]);
		maxh = max(maxh, queries[i]);
	}

	// Dijkstras

	memset(dist, 0x3f, sizeof(dist));

	dist[--src] = 0;
	nextt.push_back(src);
	in[src] = true;

	while(!nextt.empty()){
		int curr = -1, ind = -1;
		ll cdist = LLONG_MAX;

		for (int i = 0; i < nextt.size(); ++i) {
			if(dist[nextt[i]] < cdist){
				cdist = dist[nextt[i]];
				curr = nextt[i];
				ind = i;
			}
		}

		nextt.erase(nextt.begin() + ind);
		in[curr] = false;

		for(int i = 0; i < n; i++){
			if(curr == i){
				continue;
			}

			ll dx = pts[i].a - pts[curr].a, dy = pts[i].b - pts[curr].b,
					alt = cdist + (dx * dx + dy * dy);

			if(alt > maxh){
				continue;
			}

			if(alt < dist[i]){
				dist[i] = alt;

				if(!in[i]){
					nextt.push_back(i);
					in[i] = true;
				}
			}
		}
	}

	sort(dist, dist + n);

	for(int i = 0; i < q; i++){
		printf("%d\n", upper_bound(dist, dist + n, queries[i]) - dist);
	}

	return 0;
}
