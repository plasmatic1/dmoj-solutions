//============================================================================
// Name        : coci14c5p1.cpp
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

const int MAX = 16, N = 8;
int best = -1000000,
	arr[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	for (int i = 0; i < N; i++)
		scan(arr[i]);
	copy(arr, arr + N, arr + N);
	for (int i = 1; i < MAX; i++)
		arr[i] += arr[i - 1];

	for (int i = 3; i < MAX; i++)
		best = max(best, arr[i] - (i > 3 ? arr[i - 4] : 0));
	printf("%d\n", best);
}