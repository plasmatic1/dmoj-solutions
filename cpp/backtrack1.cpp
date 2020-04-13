//============================================================================
// Name        : backtrack1.cpp
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

const int MAX = 64;
int n, half, tot = 0;
ll dpOdd[MAX], dpEven[MAX];

ll recOdd(int cur){
	if(cur << 1 == n)
		return 0;
	if(dpOdd[cur] != -1)
		return dpOdd[cur];

	ll tot = 1;
	for(int i = 1; i <= half - cur; i++)
		tot += recOdd(cur + i);

	return dpOdd[cur] = tot;
}

ll recEven(int cur){
	if(cur == half)
		return 1;
	if(dpEven[cur] != -1)
		return dpEven[cur];

	ll tot = 0;
	for(int i = 1; i <= half - cur; i++)
		tot += recEven(cur + i);
	return dpEven[cur] = tot;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	scan(n);
	half = n >> 1;

	memset(dpOdd, -1, sizeof dpOdd);
	memset(dpEven, -1, sizeof dpEven);
	tot = recOdd(0);
	if(n % 2 == 0)
		tot += recEven(0);

	printf("%lld\n", tot);
}