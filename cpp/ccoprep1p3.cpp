//============================================================================
// Name        : ccoprep1p3.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MIN_PRI = 0, MAX_PRI = INT_MAX;
mt19937 twister;
uniform_int_distribution<> dis;

inline void init(){
	twister = mt19937(time(0));
	dis = uniform_int_distribution<>(MIN_PRI, MAX_PRI);
}

struct treap{
	treap* child[2] = {nullptr, nullptr};
	int pri, size, val;

	treap(int vval) : pri(dis(twister)), size(1), val(vval){}
};

#define lhs(node) ((node)->child[0]) // Left child
#define rhs(node) ((node)->child[1]) // Right child
#define size(node) ((node) != nullptr ? (node)->size : 0) // Get size of node
#define update(node) ((node)->size = 1 + size(lhs(node)) + size(rhs(node))) // Updates node size for current node

treap* rotate(treap *curr, treap *cpar, int type){ // Type: 0 -> Right, 1 -> Left
	treap *pivot = curr->child[0 ^ type], *bnode = pivot->child[1 ^ type];

	curr->child[0 ^ type] = bnode;
	pivot->child[1 ^ type] = curr;
	update(curr);
	update(pivot);

	return pivot;
}


treap* insert(treap* &curr, treap *cpar, int v){
	if(curr == nullptr) return curr = new treap(v);

	bool ismore = v > curr->val;
	curr->child[ismore] = insert(curr->child[ismore], curr, v);
	if(curr->child[ismore]->pri > curr->pri) curr = rotate(curr, cpar, ismore);

	update(curr);
	return curr;
}

treap* remove(treap* &curr, treap *cpar){
	if(lhs(curr) != nullptr && rhs(curr) != nullptr){
		bool rhsbest = lhs(curr)->pri > rhs(curr)->pri; // If the left side is the best, then do a right rotation, and vice versa
		curr = rotate(curr, cpar, rhsbest);
		curr->child[!rhsbest] = remove(curr->child[!rhsbest], curr);

		update(curr);
		return curr;
	}

	treap* ncurr = lhs(curr) != nullptr ? lhs(curr) : rhs(curr);
	delete curr;
	return ncurr;
}

treap* remove(treap* &curr, treap *cpar, int v){
	if(curr == nullptr) return curr;

	if(v == curr->val) return curr = remove(curr, cpar);
	else curr->child[v > curr->val] = remove(curr->child[v > curr->val], curr, v);

	update(curr);
	return curr;
}

int search(treap *curr, int idx, int v){
	if(curr == nullptr) return -1;

	if(v < curr->val) return search(lhs(curr), idx, v);
	else if(v > curr->val) return search(rhs(curr), idx + size(lhs(curr)) + 1, v);
	else{
		int ret = search(lhs(curr), idx, v);
		return ret == -1 ? idx + size(lhs(curr)) + 1 : ret;
	}
}

int kth(treap *curr, int idx){
	if(curr == nullptr) return -1;

	if(idx > size(lhs(curr)) + 1) return kth(rhs(curr), idx - size(lhs(curr)) - 1);
	else if(idx > size(lhs(curr))) return curr->val;
	else return kth(lhs(curr), idx);
}

void inorder(treap *curr){
	if(curr == nullptr) return;
	inorder(lhs(curr));
	printf("%d ", curr->val);
	inorder(rhs(curr));
}

//merges curr into other
void mergeinto(treap* &curr, treap* &other){
	if(curr == nullptr) return;
	mergeinto(lhs(curr), other);
	mergeinto(rhs(curr), other);
	insert(other, nullptr, curr->val);
}

void destroy(treap* &curr){
	if(lhs(curr) != nullptr) destroy(lhs(curr));
	if(rhs(curr) != nullptr) destroy(rhs(curr));
	delete curr;
}

const int MAX = 100001;
int n, m, q, ba, bb,
	dset[MAX], rnks[MAX];
treap* bbst[MAX];
char bt;

int rt(int v){
	return v == dset[v] ? v : dset[v] = rt(dset[v]);
}

inline void merge(int a, int b){
	a = rt(a), b = rt(b);
	if(a == b) return;

	// insert smaller into larger
	if(size(bbst[a]) < size(bbst[b])) swap(a, b);

	mergeinto(bbst[b], bbst[a]);
	dset[b] = a; // assign root
	destroy(bbst[b]);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	for(int i = 1; i <= n; i++) dset[i] = i;

	for (int i = 1; i <= n; ++i) {
		cin >> ba;
		rnks[ba] = i;
		insert(bbst[i], nullptr, ba);
	}

	for (int i = 0; i < m; ++i) {
		cin >> ba >> bb;
		merge(ba, bb);
	}

	cin >> q;

	for (int i = 0; i < q; ++i) {
		cin >> bt >> ba >> bb;

		if(bt == 'B'){
			merge(ba, bb);
		}
		else{
			treap* tree = bbst[rt(ba)];

			if(size(tree) < bb) printf("-1\n");
			else printf("%d\n", rnks[kth(tree, bb)]);
		}
	}
}
