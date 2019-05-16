//============================================================================
// Name        : cco07p2.cpp
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

const int MAX = 100001;
constexpr int LOG = log2(10000000), SZ = LOG * 6;
int n,
	buf[6];
unordered_set<bitset<SZ>> flakes;

inline vector<bitset<SZ>> flakesOf() {
	vector<bitset<SZ>> ret;

	for (int i = 0; i < 6; ++i) {
		bitset<SZ> cur;
		for (int j = 0; j < 6; ++j)
			cur = (cur << LOG) | bitset<SZ>(buf[(i + j) % 6]);
		ret.push_back(cur);
	}

	return ret;
}

inline bool duplicate(vector<bitset<SZ>> &vec) {
	for (bitset<SZ> s : vec)
		if (flakes.find(s) != flakes.end())
			return true;
	return false;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	scan(n);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < 6; ++j)
			scan(buf[j]);

		auto a = flakesOf();
		reverse(buf, buf + 6);
		auto b = flakesOf();

		if (duplicate(a) || duplicate(b)) {
			printf("Twin snowflakes found.\n");
			return 0;
		}

		flakes.insert(a[0]);
	}

	printf("No two snowflakes are alike.\n");

	return 0;
}