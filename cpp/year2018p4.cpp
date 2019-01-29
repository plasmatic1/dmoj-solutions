//============================================================================
// Name        : ThePolarExpress.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MD = 19, MS = 400;

ll l, r;
int digc, sumc = 0,
	ldigs[MD], rdigs[MD];
bool dp[3][MD][MS], sel[MS];

void recur(int state, int pos, int sum){
	if(dp[state][pos][sum]){
		return;
	}

//	printf("state=%d pos=%d sum=%d\n", state, pos, sum);

	dp[state][pos][sum] = true;

	if(pos + 1 == digc){
		return;
	}

	int ldb = state == 0 ? ldigs[pos + 1] + 1 : 0, rdb = state == 2 ? rdigs[pos + 1] - 1 : 9;

	if(state == 0){
		recur(0, pos + 1, sum + ldigs[pos + 1]);
	}
	else if(state == 2){
		recur(2, pos + 1, sum + rdigs[pos + 1]);
	}

	for(int i = ldb; i <= rdb; i++){
		recur(1, pos + 1, sum + i);
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> l >> r;

	// Setting up digits

	ll tl = l, tr = r; // Lunacy by the god himself moses xu
	while(max(tl, tr) > 0){
		ldigs[digc] = tl % 10;
		rdigs[digc++] = tr % 10;

		tl /= 10;
		tr /= 10;
	}

	reverse(ldigs, ldigs + digc);
	reverse(rdigs, rdigs + digc);

	while(ldigs[0] == rdigs[0] && digc > 1){
		copy(ldigs + 1, ldigs + digc, ldigs);
		copy(rdigs + 1, rdigs + digc--, rdigs);
	}

	// Recursions

	recur(0, 0, ldigs[0]);

	for(int i = ldigs[0] + 1; i < rdigs[0]; i++){
		recur(1, 0, i);
	}

	recur(2, 0, rdigs[0]);

	// Getting sums

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < MS; ++j) {
			if(dp[i][digc - 1][j] && !sel[j]){
//				printf("j is valid (%d)\n", j);

				sumc++;
				sel[j] = true;
			}
		}
	}

	printf("%d\n", sumc);
}
