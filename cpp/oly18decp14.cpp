//============================================================================
// Name        : PrimeNetsAutocompleteApp.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct p{
	string s;
	int idx;

	friend bool operator<(const p &a, const p &b){
		return a.s < b.s;
	}
};

#define CODE(x) ((int)((x) - 'a'))

struct trie{
	vector<int> words;
	int count;
	trie *child[26];
};

int n, m, bufk;
string bufs;

void init(trie* &node){
	node = new trie;
	node->count = 0;

	for(int i = 0; i < 26; i++){
		node->child[i] = nullptr;
	}
}

void insert(trie* node, string& str, int stridx, int idx){
//	printf("inserting str=%s at idx=%d\n", str.c_str(), idx);

	if(node == nullptr){
		assert(0);
	}

	node->words.push_back(stridx);

	if(idx == str.length()){
		return;
	}

	int v = CODE(str[idx]);

	if(node->child[v] == nullptr){
		init(node->child[v]);
	}

	insert(node->child[v], str, stridx, idx + 1);
}

int search(trie* node, string& str, int k, int idx){
	if(idx == str.length()){
		if(k >= node->words.size()){
			return -1;
		}
		return node->words[k];
	}

	int v = CODE(str[idx]);

	if(node->child[v] == nullptr){
		return -1;
	}

	return search(node->child[v], str, k, idx + 1);
}

trie* root = nullptr;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	init(root);

	vector<p> vec;

	for (int i = 1; i <= n; ++i) {
		cin >> bufs;
		vec.push_back({bufs, i});
	}

	sort(vec.begin(), vec.end());

	for(p pp : vec){
		insert(root, pp.s, pp.idx, 0);
	}

	for (int i = 0; i < m; ++i) {
		cin >> bufk >> bufs;

		printf("%d\n", search(root, bufs, bufk - 1, 0));
	}
}
