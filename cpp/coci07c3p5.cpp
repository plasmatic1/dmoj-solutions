//============================================================================
// Name        : Cudak.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int STATE = 3, MD = 16, MS = 140;
ll l, r, cnt = 0,
	par[MD][MS][STATE], dp[MD][MS][STATE];
int s, digc = 0,
	ldigs[MD], rdigs[MD];
vector<int> extradigs;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> l >> r >> s;

	// Getting Digits

	ll tl = l, tr = r;
	while(max(tl, tr) > 0){
		ldigs[digc] = tl % 10L;
		rdigs[digc++] = tr % 10L;

		tl /= 10;
		tr /= 10;
	}

	reverse(ldigs, ldigs + digc);
	reverse(rdigs, rdigs + digc);

	// Reducing numbers

	while(ldigs[0] == rdigs[0] && digc > 1){
		s -= ldigs[0];
		extradigs.push_back(ldigs[0]);

		copy(ldigs + 1, ldigs + digc, ldigs);
		copy(rdigs + 1, rdigs + digc--, rdigs);
	}

	// Init DP

	for (int i = 0; i < MD; ++i) {
		for (int j = 0; j < MS; ++j) {
			for (int k = 0; k < STATE; ++k) {
				par[i][j][k] = LLONG_MAX;
			}
		}
	}

	par[0][ldigs[0]][0] = ldigs[0];
	dp[0][ldigs[0]][0] = 1;

	for (int i = ldigs[0] + 1; i < rdigs[0]; ++i) {
		par[0][i][1] = i;
		dp[0][i][1] = 1;
	}

	par[0][rdigs[0]][2] = rdigs[0];
	dp[0][rdigs[0]][2] = 1;

	// DP

	for (int i = 0; i < digc; ++i) {
		for (int j = 0; j < MS; ++j) {
			for (int k = 0; k < STATE; ++k) {
				if(dp[i][j][k] != 0){
					ll newbase = (par[i][j][k] << 1) + (par[i][j][k] << 3);
					int lv = k == 0 ? ldigs[i + 1] + 1 : 0, rv = k == 2 ? rdigs[i + 1] - 1 : 9;

					if(k == 0){
						dp[i + 1][j + ldigs[i + 1]][0] += dp[i][j][k];
						par[i + 1][j + ldigs[i + 1]][0] = min(par[i + 1][j + ldigs[i + 1]][0],
								newbase + ldigs[i + 1]);
					}
					else if(k == 2){
						dp[i + 1][j + rdigs[i + 1]][2] += dp[i][j][k];
						par[i + 1][j + rdigs[i + 1]][2] = min(par[i + 1][j + rdigs[i + 1]][2],
								newbase + rdigs[i + 1]);
					}

					for (int l = lv; l <= rv; ++l) {
						dp[i + 1][j + l][1] += dp[i][j][k];
						par[i + 1][j + l][1] = min(par[i + 1][j + l][1], newbase + l);
					}
				}
			}
		}
	}

	// Calculating total and Getting minimum

	ll minv = LLONG_MAX, fullmin = 0;
	for (int i = 0; i < 3; ++i) {
		cnt += dp[digc - 1][s][i];
		minv = min(minv, par[digc - 1][s][i]);
	}

//	printf("ogminv=%lld\n", minv);

	// Constructing full value

	vector<int> minvdigs;

	if(minv == 0){
		minvdigs.push_back(0);
	}

	while(minv > 0){
		minvdigs.push_back(minv % 10);
		minv /= 10;
	}

	reverse(minvdigs.begin(), minvdigs.end());
	extradigs.insert(extradigs.end(), minvdigs.begin(), minvdigs.end());

	for(int dig : extradigs){
		fullmin = (fullmin << 1) + (fullmin << 3);
		fullmin += dig;
	}

	printf("%lld\n%lld\n", cnt, fullmin);
}
