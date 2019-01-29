//============================================================================
// Name        : RogerNumber.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MD = 12, MN = 10, STATE = 2;
int l, r, ldigc = 0, rdigc = 0,
	dp[MD][MN][STATE], ldigs[MD], rdigs[MD];
bool iszero[MD][MN][STATE];

int run(int* digs, int digc){
	if(digc == 0){
		return 0;
	}

	// DP Setup
	int total = 0;

	memset(dp, 0, sizeof(dp));
	memset(iszero, 0, sizeof(iszero));

	for (int i = 1; i < digs[0]; ++i) {
		dp[0][i][0] = 1;
	}

	iszero[0][0][0] = true;
	dp[0][digs[0]][1] = 1;

	// DP
	for (int i = 0; i < digc; ++i) {
		for (int j = 0; j < MN; ++j) {
			for (int k = 0; k < STATE; ++k) {
				if(dp[i][j][k]){
					int rb = k ? digs[i + 1] - 1 : 9;

					for (int l = 0; l <= rb; ++l) {
						if(abs(l - j) >= 2){
							dp[i + 1][l][0] += dp[i][j][k];
						}
					}

					if(k == 1){
						if(abs(digs[i + 1] - j) >= 2){
							dp[i + 1][digs[i + 1]][1] += dp[i][j][k];
						}
					}
				}
				if(iszero[i][j][k]){
					for (int l = 1; l < MN; ++l) {
						dp[i + 1][l][0]++;
					}

					iszero[i + 1][0][0] = true;
				}
			}
		}
	}

	// Adding Total
	for (int i = 0; i < MN; ++i) {
		for (int j = 0; j < STATE; ++j) {
			total += dp[digc - 1][i][j];
		}
	}

	return total;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> l >> r;
	l--;

	// Getting digit counts
	int tl = l;
	while(tl > 0){
		ldigs[ldigc++] = tl % 10;
		tl /= 10;
	}

	int tr = r;
	while(tr > 0){
		rdigs[rdigc++] = tr % 10;
		tr /= 10;
	}

	reverse(ldigs, ldigs + ldigc);
	reverse(rdigs, rdigs + rdigc);

	// Running DP
	printf("%d\n", run(rdigs, rdigc) - run(ldigs, ldigc));
}
