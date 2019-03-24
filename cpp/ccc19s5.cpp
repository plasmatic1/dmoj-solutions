//============================================================================
// Name        : ccc19s5.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 3001;
int n, k,
	tree[MAX][MAX], arr[MAX][MAX];
ll tot = 0;

inline int maxv(int x, int y){
	int maxv = 0;
	y = n - y + 1;

	for(; x; x -= x & -x)
		for(int cy = y; cy; cy -= cy & -cy)
			maxv = max(maxv, tree[x][cy]);

	return maxv;
}

inline void setv(int x, int y, int v){
	y = n - y + 1;

	for(; x <= n; x += x & -x)
		for(int cy = y; cy <= n; cy += cy & -cy)
			tree[x][cy] = max(tree[x][cy], v);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> k;

	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= i; j++)
			cin >> arr[i][j];

	for(int i = n; i >= 1; i--){
		for(int j = i, y = 1; j <= n; j++, y++)
			setv(j, y, arr[j][y]);
		for(int j = i, y = 1; j <= n; j++, y++)
			if(j + k - 1 <= n)
				tot += maxv(j + k - 1, y);
	}

	printf("%lld\n", tot);
}