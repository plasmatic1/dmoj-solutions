//============================================================================
// Name        : valentines19j5.cpp
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
int n, buf,
	m[MAX], b[MAX], tree[MAX];
unordered_map<int, int> comp;
map<p, int> dups;
set<int> tcomp;
ll tot = 0;

void add(int x){
	for(; x <= n; x += x & -x)
		tree[x]++;
}

int sum(int x){
	int sum = 0;
	for(; x; x -= x & -x)
		sum += tree[x];
	return sum;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 0; i < n; ++i){
		cin >> m[i] >> b[i];
		tcomp.insert(m[i]);
	}

	int i = 1;
	for(int x : tcomp)
		comp[x] = i++;

	for (int i = 0; i < n; ++i) {
		int compm = comp[m[i]];
		p line = make_pair(m[i], b[i]);

		tot += sum(compm - 1) + sum(n) - sum(compm) + dups[line];

		add(compm);
		dups[line]++;
	}

	printf("%lld\n", tot);
}
