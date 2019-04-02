//============================================================================
// Name        : test.cpp
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

const int MK = 50001, MT = 11;
int n, q, m, bk, bt;
ll cnt[MK][MT];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	scan(n, q, m);
	m *= 10;

	for (int i = 0; i < n; ++i) {
		scan(bk);
		int mk = bk % m, org = bk;
		unordered_set<int> digs;
		while(bk > 0){
			digs.insert(bk % 10);
			bk /= 10;
		}

		for(int x : digs)
			cnt[mk][x] += org;
	}

	for (int i = 0; i < q; ++i) {
		scan(bk, bt);
		cout << cnt[bk][bt] << "\n";
	}
}