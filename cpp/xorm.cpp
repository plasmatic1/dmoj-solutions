//============================================================================
// Name        : xorm.cpp
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

struct trie{
	trie* child[2];
	int idx;

	trie(){
		child[0] = child[1] = nullptr;
		idx = INT_MAX;
	}
};

const int MAXBIT = 1 << 29;
int n, q, buf, cXor = 0;
trie* root;

void insert(trie* curr, int numIdx, int num, int bit){
	if(bit == 0){
		curr->idx = min(curr->idx, numIdx);
		return;
	}

	int idx = (bool)(num & bit);
	trie* &next = curr->child[idx];

	if(next == nullptr)
		next = new trie;
	insert(next, numIdx, num, bit >> 1);
}

int minSearch(trie* curr, int bit){
	if(bit == 0)
		return curr->idx;

	int lookFor = (bool)(cXor & bit);
	trie* next = curr->child[lookFor];

	if(next != nullptr)
		return minSearch(next, bit >> 1);
	return minSearch(curr->child[!lookFor], bit >> 1);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	scan(n, q);

	root = new trie;
	for (int i = 0; i < n; ++i) {
		scan(buf);
		insert(root, i, buf, MAXBIT);
	}

	for (int i = 0; i < q; ++i) {
		scan(buf);
		cXor ^= buf;

		printf("%d\n", minSearch(root, MAXBIT));
	}
}