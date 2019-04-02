//============================================================================
// Name        : oly19practice19.cpp
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
int n, k, buf,
	lowestIndex[MAX], highestIndex[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	scan(n, k);

	memset(lowestIndex, 0x3f, sizeof lowestIndex);
	memset(highestIndex, -1, sizeof highestIndex);

	lowestIndex[0] = -1;
	int cur = 0;
	for (int i = 0; i < n; ++i) {
		scan(buf);

		cur += buf;
		cur %= k;
		lowestIndex[cur] = min(lowestIndex[cur], i);
		highestIndex[cur] = max(highestIndex[cur], i);
	}

	int best = 0;
	for (int i = 0; i < k; ++i)
		best = max(best, highestIndex[i] - lowestIndex[i]);
	printf("%d\n", best);
}
