//============================================================================
// Name        : ecoo17r3p2.cpp
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

struct node {
	int sz = 0;
	unordered_map<int, node*> ch;
};

const int MAX = 100001;
const ll MOD = 1000000007;
int n;
string strs[MAX];
node *rt = nullptr;

void del(node* &cur) {
	for (pair<int, node*> ch : cur->ch)
		del(ch.second);
	cur->ch.clear();
	delete cur;
}

void insert(node* cur, int idx, vector<int> &path, int pathSz) {
	if (idx == pathSz)
		return;

	cur->sz = max(cur->sz, path[idx]);

	auto ptr = cur->ch.find(path[idx]);
	if (ptr != cur->ch.end())
		insert(ptr->second, idx + 1, path, pathSz);
	else {
		cur->ch[path[idx]] = new node;
		insert(cur->ch[path[idx]], idx + 1, path, pathSz);
	}
}

ll count(node* cur) {
	ll tot = 0;
	for (pair<int, node*> ch : cur->ch)
		tot = (tot + count(ch.second)) % MOD;
	return (tot + cur->sz) % MOD;
}

inline void solve() {
	for (int i = 0; i < n; i++) {
		vector<int> vec;
		string &str = strs[i], cur = "";

		for (int j = 0, len = str.length(); j < len; j++) {
			if (str[j] == '.') {
				vec.push_back(stoi(cur));
				cur = "";
			}
			else
				cur += str[j];
		}
		vec.push_back(stoi(cur));

		insert(rt, 1, vec, vec.size());
	}

	printf("%lld\n", count(rt) + 1);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

#ifndef ONLINE_JUDGE
	int t = 2;
#else
	int t = 10;
#endif

	while (t--) {
		scan(n);

		for (int i = 0; i < n; i++)
			scan(strs[i]);

		rt = new node;
		solve();
		del(rt);
	}

	return 0;
}