//============================================================================
// Name        : cpc18c1p3.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
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
template<typename F, typename... R> void debug_(F &f, R&... r){while(dnms_[di_] != ',')cout<<dnms_[di_++];di_++;cout<<": "<<f<<",";debug_(r...);}
#define debug(...) dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__)

const int MAX = 1000001;
int n,
	dp[MAX];
string a, b;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	scan(n, a, b);
	a = " " + a;
	b = " " + b;

	for (int i = 1; i <= n; ++i) {
		dp[i] = 0x3f3f3f3f;

		if(a[i] == b[i])
			dp[i] = min(dp[i], dp[i - 1]);
		if(a[i] == '0' && b[i] == '1')
		    dp[i] = min(dp[i], dp[i - 1] + 1);

		for(int diff = 3; diff <= 4; diff++){
			bool needClear = false;
			int aDiffFull = 0, bDiffZero = 0, bDiffFull = 0;
			for(int j = max(1, i - diff + 1); j <= i; j++){
				if(a[j] == '1' && b[j] != '1')
					needClear = true;
				aDiffFull += a[j] == '0';
				bDiffFull += b[j] == '0';
				bDiffZero += b[j] == '1';
			}

			if(i < diff){
				aDiffFull += diff - i;
				bDiffFull += diff - i;
			}

			if(needClear)
				dp[i] = min(dp[i], dp[max(0, i - diff)] + aDiffFull + 1 + bDiffZero);
			else
				dp[i] = min(dp[i], dp[max(0, i - diff)] + aDiffFull - bDiffFull);
		}
	}

	if(dp[n] == 0x3f3f3f3f)
		printf("-1\n");
	else
		printf("%d\n", dp[n]);
}