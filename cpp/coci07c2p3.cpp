//============================================================================
// Name        : coci07c2p3.cpp
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

const int MAX = 21;
int r, c;
char grid[MAX][MAX];
string best = "zzzzzzzzzzzzzzzzzzzzzzzzzzzz";

inline void insertStr(string s) {
	int sl = s.length();
	if (sl >= 2)
		best = min(best, s);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	scan(r, c);

	for (int i = 0; i < r; i++)
		scan(grid[i]);

	for (int i = 0; i < r; ++i) {
		string cur = "";
		for (int j = 0; j < c; ++j) {
			if (grid[i][j] == '#') {
				insertStr(cur);
				cur = "";
			}
			else
				cur += grid[i][j];
		}
		if (cur != "")
			insertStr(cur);
	}

	for (int i = 0; i < c; ++i) {
		string cur = "";
		for (int j = 0; j < r; ++j) {
			if (grid[j][i] == '#') {
				insertStr(cur);
				cur = "";
			}
			else
				cur += grid[j][i];
		}
		if (cur != "")
			insertStr(cur);
	}

	printf("%s\n", best.c_str());

	return 0;
}