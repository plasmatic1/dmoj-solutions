//============================================================================
// Name        : ccc10s5.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAX = 201, MX = 2501;
int n = 0, x, sl,
		nutris[MAX], dp[MAX][MX];
string s;
vector<int> topo,
	matrix[MAX];

int build(int l, int r){
	if(s[l] == '('){
		l++;
		r--;
	}
	while(s[l] == ' ') l++;
	while(s[r] == ' ') r--;

	int num = ++n;

	int bc = 0, splitidx = -1;
	for(int i = l; i <= r; i++){
		if(s[i] == '(') bc++;
		if(s[i] == ')') bc--;
		if(s[i] == ' ' && bc == 0) splitidx = i;
	}

	if(splitidx == -1){ // it's a fucking leaf
		nutris[num] = 0;
		for(int i = l; i <= r; i++){
			nutris[num] *= 10;
			nutris[num] += (int)(s[i] - '0');
		}
	}
	else{
		int lhs = build(l, splitidx - 1), rhs = build(splitidx + 1, r);

		matrix[num].push_back(lhs);
		matrix[num].push_back(rhs);
	}

	return num;
}

void toposort(int cur){
	for(int par : matrix[cur]) toposort(par);
	topo.push_back(cur);
}

void prnt(int cur, int amt){
	for(int i = 0; i < amt; i++) printf("--");
	printf("%d", cur);
	if(nutris[cur] != -1) printf(", lval: %d", nutris[cur]);
	printf("\n");

	for(int adj : matrix[cur]) prnt(adj, amt + 1);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	getline(cin, s);
	cin >> x;
	sl = s.length();

	memset(nutris, -1, sizeof nutris);
	build(0, sl - 1);
	toposort(1);

	// debugging input
//	prnt(1, 0);
//	for(int i : topo) printf("%d, ", i);
//	printf("\n");

	if(n == 1){
		printf("%d\n", nutris[1] + x);
		return 0;
	}

	for(int i : topo){
		if(i == 1){
			int a = matrix[1][0], b = matrix[1][1];

			for(int j = 0; j <= x; j++){
				int best = INT_MIN;

				for(int k = 0; k <= j; k++)
					best = max(best, dp[a][k] + dp[b][j - k]);

				dp[1][j] = best;
			}
		}
		else if(nutris[i] != -1){ // leaf node
			for(int j = 0; j <= x; j++){
				int best = INT_MIN;

				for(int k = 0; k <= j; k++){ // amount of nutri for growth
					int trunk = j - k + 1;
					best = max(best, min(nutris[i] + k, trunk * trunk));
				}

				dp[i][j] = best;
			}
		}
		else{ // not leaf
			int a = matrix[i][0], b = matrix[i][1],
					tmp[x + 1];
			memset(tmp, 0, sizeof tmp);

			for(int j = 0; j <= x; j++){
				int best = INT_MIN;
				for(int k = 0; k <= j; k++)
					best = max(best, dp[a][k] + dp[b][j - k]);

				tmp[j] = best;

				best = INT_MIN;
				for(int k = 0; k <= j; k++){
					int trunk = j - k + 1;
					best = max(best, min(tmp[k], trunk * trunk));
				}

				dp[i][j] = best;
			}
		}
	}

	printf("%d\n", dp[1][x]);

	return 0;
}
