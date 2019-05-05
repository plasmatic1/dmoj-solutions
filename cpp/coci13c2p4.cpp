//============================================================================
// Name        : coci13c2p4.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Scan and Debug
void scan(){}
template<typename F, typename... R> void scan(F &f,R&... r){cin>>f;scan(r...);}
int di_; string dnms_, co_ = ",";
void debug_(){cout<<endl;}
template<typename F, typename... R> void debug_(F f, R... r){while(dnms_[di_] != ',')cout<<dnms_[di_++];di_++;cout<<": "<<f<<",";debug_(r...);}
#define debug(...) dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__)

struct p {
	int v, w;
};

const int MAX = 1501;
int n, buf,
	adj[MAX][MAX], dp[MAX][MAX];

int rec(int left, int right) {
	if (right == n || left == n) return 0;
	int &ret = dp[left][right];
	if (ret != -1) return ret;

	int nextNode = max(left, right) + 1;
	return ret = min(rec(nextNode, right) + adj[nextNode][left], rec(left, nextNode) + adj[right][nextNode]);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	scan(n);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scan(adj[i][j]);

	memset(dp, -1, sizeof dp);
	printf("%d\n", rec(0, 0));
}
