//============================================================================
// Name        : coci17c1p3.cpp
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

const int MAX = 20001;
int n, tot = 0;
string s[MAX];
unordered_map<string, unordered_set<int>> cnt;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	scan(n);

	for (int i = 0; i < n; i++) {
		scan(s[i]);
		for (int j = 0, sz = s[i].length(); j < sz; j++)
			for (int k = 1; k <= sz - j; k++)
				cnt[s[i].substr(j, k)].insert(i);
	}

	for (int i = 0; i < n; i++)
		tot += cnt[s[i]].size();

	printf("%d\n", tot - n);

	return 0;
}
