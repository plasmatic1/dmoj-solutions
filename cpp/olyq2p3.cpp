//============================================================================
// Name        : The.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// thank you eric :) dp[row][number of kings on board][mask of previous row]

const int MAX = 10, MAXK = 101, MAXM = 1 << MAX;
int n, kv, msub;
ll tsum = 0,
	dp[MAX + 1][MAXK][MAXM];
bool tmpk[MAX + 2], tmpl[MAX + 2];
size_t tmpsz;

inline void mapto(bool arr[MAX + 2], int mask){
	for(int i = 0; i < n; i++){
		if(mask & (1 << i)) arr[i + 1] = true;
	}
}

inline string bstr(int v){
	string fs = "";
	for(int mg = 1; mg < msub; mg <<= 1){
		fs += v & mg ? "1" : "0";
	}
	return fs;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> kv;
	msub = 1 << n;
	tmpsz = sizeof tmpk;

	memset(dp, 0, sizeof dp);
	dp[0][0][0] = 1;

	for (int i = 0; i < n; ++i) {
		for(int j = 0; j <= kv; j++){
			for(int k = 0; k < msub; k++){
				if(dp[i][j][k]){ // skip ones that have 0 possibilities
					memset(tmpk, false, tmpsz);
					mapto(tmpk, k);

					// loop through all possible next rows
					for(int l = 0; l < msub; l++){
						int bitc = __builtin_popcount(l);
						if(j + bitc > kv) continue;

						memset(tmpl, false, tmpsz);
						mapto(tmpl, l);
						bool pass = true;

						// check if row is valid
						for(int m = 1; m <= n; m++){
							if(tmpl[m]){
								if(tmpk[m - 1] || tmpk[m] || tmpk[m + 1] || tmpl[m - 1] || tmpl[m + 1]){
									pass = false;
									break;
								}
							}
						}

						if(pass)
							dp[i + 1][j + bitc][l] += dp[i][j][k];
					}
				}
			}
		}
	}

	for(int i = 0; i < msub; i++)
		tsum += dp[n][kv][i];

	printf("%lld\n", tsum);
}
