//============================================================================
// Name        : ccc15s5.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAX = 3010, MM = 101;
int n, m,
    arr[MAX], ins[MM],
    dp[MAX][MM][MM][2];

int rec(int i, int l, int r, bool took){
    if(dp[i][l][r][took] != -1) return dp[i][l][r][took];

    int &dpv = dp[i][l][r][took];

    if(i > n){
    	if(l <= r){
    		if(took) return dpv = rec(i, l + 1, r, false);
    		return dpv = rec(i, l, r - 1, true) + ins[r];
    	}
    	return 0;
    }

    dpv = rec(i + 1, l, r, false);

    if(took){
        if(l <= r)
        	dpv = max(dpv, rec(i + 1, l + 1, r, true) + arr[i]);
    }
    else{
        dpv = max(dpv, rec(i + 1, l, r, true) + arr[i]);

        if(l <= r)
        	dpv = max(dpv, rec(i, l, r - 1, true) + ins[r]);
    }

    return dpv;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;

    for (int i = 1; i <= n; ++i)
        cin >> arr[i];

    cin >> m;

    for (int i = 1; i <= m; ++i)
        cin >> ins[i];

    sort(ins + 1, ins + m + 1);
    memset(dp, -1, sizeof dp);

    printf("%d\n", rec(1, 1, m, false));

    return 0;
}
