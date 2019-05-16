//============================================================================
// Name        : coci17c2p2.cpp
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

#define CHR(x) ((int)((x) - 'a'))

const int MAX = 100001;
int n, k;
string strs[MAX];
queue<int> choice[26];
vector<pair<string, int>> sorted[26];
char bc;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	scan(n, k);

	for (int i = 0; i < n; i++) {
		scan(strs[i]);
		sorted[CHR(strs[i][0])].push_back(make_pair(strs[i], i));
	}

	for (int i = 0; i < 26; i++) {
		sort(sorted[i].begin(), sorted[i].end());
		for (auto p : sorted[i])
			choice[CHR(p.first[0])].push(p.second);
	}

	for (int i = 0; i < k; ++i) {
		scan(bc);
		queue<int> &qu = choice[CHR(bc)];
		printf("%s\n", strs[qu.front()].c_str());
		int buf = qu.front(); qu.pop();
		qu.push(buf);
	}

	return 0;
}