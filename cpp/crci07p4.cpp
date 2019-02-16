//============================================================================
// Name        : crci07p4.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

struct p{
    int x, c;

    p(int a, int b) : x(a), c(b){}
    p() : x(-1), c(-1){}
};

typedef long long ll;
const int MAX = 1001, MC = 5001, INF = 0x3f3f3f3f;
int n, sidx = 0, c = 0,
    skip[MAX], str[MAX], dp[MAX][MC];
p par[MAX][MC];
string a;

#define CH(x) ((int)(a[x] - '0'))

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    // Parsing input
    cin >> a;
    n = a.length();
    for(; a[sidx] != '='; sidx++) str[sidx] = CH(sidx);
    for(int i = sidx + 1; i < n; i++){
        c *= 10;
        c += CH(i);
    }
    n = sidx;

    memset(skip, -1, sizeof skip);
    int last0 = -1;
    for(int i = 0; i < n; i++){
        if(str[i] == 0 && last0 == -1) last0 = i;
        else if(str[i] != 0 && last0 != -1){
            for(int j = last0; j < i; j++) skip[j] = i;
            last0 = -1;
        }
    }
    if(last0 != -1)
        for(int i = last0; i < n; i++) skip[i] = n;

    // DP
    memset(dp, 0x3f, sizeof dp);
    dp[0][0] = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j <= c; j++){
            if(dp[i][j] != INF){
                int beg = skip[i] == -1 ? i : skip[i], curr = 0;
                while(beg < n && curr <= c){
                	curr *= 10;
                	curr += str[beg];

                	int next = j + curr;
                	if(next > c) break;

                	if(dp[beg + 1][next] > dp[i][j] + 1){
                		dp[beg + 1][next] = dp[i][j] + 1;
                		par[beg + 1][next] = {i, j};
                	}

                	beg++;
                }

                int next = j + curr;
                if(next <= c && dp[n][next] > dp[i][j] + 1){
                	dp[n][next] = dp[i][j] + 1;
                	par[n][next] = {i, j};
                }
            }
        }
    }

    // Going backwards
    string end = "";
    int x = n, y = c;
    while(x != 0 && y != 0){
    	p pa = par[x][y];

    	for(int i = x - 1; i >= pa.x; i--)
    		end += a[i];
    	if(pa.x != 0 || pa.c != 0) end += "+";

    	x = pa.x;
    	y = pa.c;
    }
    reverse(end.begin(), end.end());

    printf("%s=%d\n", end.c_str(), c);

    return 0;
}
