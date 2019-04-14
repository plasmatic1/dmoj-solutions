//============================================================================
// Name        : coci09c1p4.cpp
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

const int MAX = 101;
int n, ba, bb, aMaxV = 0,
	freqa[MAX];
map<int, int> freqb;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	scan(n);

	for (int i = 0; i < n; ++i) {
		scan(ba, bb);
		aMaxV = max(aMaxV, ba);

		freqa[ba]++;
		freqb[bb]++;

		auto ptr = freqb.begin();
		int maxv = aMaxV + ptr->first, lastR = 1, currbIdx = 0;
		for (int j = MAX - 1; j > 0; j--){
			if(freqa[j]){
				int r = lastR + freqa[j] - 1;

//				debug(i, j, currbIdx, r);

				while(currbIdx < r){
					maxv = max(maxv, j + ptr->first);
					currbIdx += ptr->second;
					ptr++;
				}

				lastR = r + 1;
			}
		}

		printf("%d\n", maxv);
	}
}