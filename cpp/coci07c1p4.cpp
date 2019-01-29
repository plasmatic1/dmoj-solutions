//============================================================================
// Name        : Zapis.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

const int MAX = 201;
const ll MOD = 100000;

int n;
ll dp[MAX][MAX];
bool over = false,
		sett[MAX][MAX];
string s;

inline int amt(char a, char b){
	switch(a){
	case '(': return (b == ')' || b == '?');
	case '[': return (b == ']' || b == '?');
	case '{': return (b == '}' || b == '?');
	case '?': return (b == ')' || b == ']' || b == '}') ? 1 : (b == '?' ? 3 : 0);
	default: return 0;
	}
}

ll rec(int l, int r){
	if(l >= r) return 1;
	if(sett[l][r]) return dp[l][r];

	ll tot = 0;
	for(int i = l + 1; i <= r; i += 2){
		tot += (amt(s[l], s[i]) * rec(l + 1, i - 1) * rec(i + 1, r));
	}

	if(tot > MOD) over = true;

	sett[l][r] = true;
	return dp[l][r] = tot % MOD;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> s;

	if(n % 2){ // Sequence length is odd
		printf("0\n");
		return 0;
	}

//	printf("dp: [\n");
//	for(int i = 0; i < n; i++){
//		printf("%d : ", i);
//		for(int j = 0; j < n; j++){
//			printf("%lld, ", dp[i][j]);
//		}
//		printf("\n");
//	}
//	printf("]\n");

	ll v = rec(0, n - 1);

	if(over) printf("%05lld\n", v);
	else printf("%lld\n", v);

	return 0;
}
