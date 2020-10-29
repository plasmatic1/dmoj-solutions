#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Defines and one-liners
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
template <typename T> inline T& back(vector<T> &vec) { return *(vec.end() - 1); }
template <typename T> inline void pop(vector<T> &vec) { return vec.erase(vec.end() - 1); }

// Scan, Debug, and other nonsense
template <typename T> ostream& operator<<(ostream& out,vector<T> iter){out<<"[";for(auto t:iter){out<<t<<", ";}out<<"]";return out;}
template <typename T> void printArray(ostream& out,T* arr,int sz){out<<"[";for(int i=0;i<sz;i++){out<<arr[i]<<", "; } out<<"]";}
#define OUT_OPERATOR(type, propa, propb) ostream& operator<<(ostream& out,type obj){out<<"("<<#propa<<"="<<obj. propa<<", "<<#propb<<"="<<obj. propb<<")";return out;}

void scan(){}
template<typename F, typename... R> void scan(F &f,R&... r){cin>>f;scan(r...);}
int di_; string dnms_, co_ = ",";
void debug_(){cout<<endl;}
template<typename F, typename... R> void debug_(F f,R... r){while(dnms_[di_] != ',')cout<<dnms_[di_++];di_++;cout<<": "<<f<<",";debug_(r...);}
#define debug(...) dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__)

ll gcdF(ll a, ll b) { return b ? gcdF(b, a % b) : a; }
#define mergeVals(a, b) gcdF(a, b)

mt19937 gen(time(NULL));
uniform_int_distribution<int> dis;
template <typename T>
struct Node {
	// val -> Index of node, aux -> Value of node, auxTot -> value of node and children
	T val; int pri; Node<T> *l, *r; ll aux, auxTot;
	Node(T val0, ll aux0) : val(val0), pri(dis(gen)), l(nullptr), r(nullptr), aux(aux0), auxTot(aux0) {}
};
template <typename T>
struct SMTreap {
	Node<T>* root;
	SMTreap() : root(nullptr) {}
	Node<T>*& which(Node<T>* &cur, bool cond) { return cond ? cur->r : cur->l; }
	ll auxTot(Node<T>* &cur) { return cur ? cur->auxTot : 0LL; }
	void upd(Node<T>* &cur) {
		if (!cur) return;
		cur->auxTot = mergeVals(cur->aux, mergeVals(auxTot(cur->l), auxTot(cur->r)));
	}
	void split(Node<T>* cur, T val, Node<T>* &l, Node<T>* &r) {
		if (!cur) l = r = nullptr;
		else if (cur->val > val) { split(cur->l, val, l, cur->l); r = cur; }
		else { split(cur->r, val, cur->r, r); l = cur; }
		upd(cur);
	}
	void merge(Node<T>* &cur, Node<T>* l, Node<T>* r) {
		if (!l || !r) cur = l ? l : r;
		else if (l->pri > r->pri) { merge(l->r, l->r, r); cur = l; }
		else { merge(r->l, l, r->l); cur = r; }
		upd(cur);
	}
	void insert(Node<T>* &cur, Node<T>* node) {
		if (!cur) cur = node;
		else if (cur->pri > node->pri) { split(cur, node->val, node->l, node->r); cur = node; }
		else insert(which(cur, node->val >= cur->val), node);
		upd(cur);
	}
	Node<T>* search(Node<T>* &cur, T val) {
		if (!cur) return nullptr;
		else if (cur->val == val) { return cur; };
		return search(which(cur, val >= cur->val), val);
	}
	void updateNodesOnPath(Node<T>* &cur, T val) {
		if (!cur) return;
		if (cur->val != val) updateNodesOnPath(which(cur, val >= cur->val), val);
		upd(cur);
	}
	ll query(T ql, T qr) {
		Node<T> *a, *b, *c;
		split(root, ql - 1, a, b);
		split(b, qr, b, c);
		ll ret = auxTot(b);
		merge(b, b, c);
		merge(root, a, b);
		return ret;
	}
	void inOrder(Node<T>* &cur) {
		if (!cur) return;
		inOrder(cur->l); cout << cur->val << ": " << cur->aux << ", "; inOrder(cur->r);
	}
};
namespace seqOp {
	void update(SMTreap<int> &bst, int id, ll val) {
		auto ptr = bst.search(bst.root, id);
		if (ptr) {
			ptr->aux = val;
			bst.updateNodesOnPath(bst.root, id);
		}
		else
			bst.insert(bst.root, new Node<int>(id, val));
	}
}

struct SegNode {
	SMTreap<int> bst; SegNode *l, *r;
	SegNode(int n) : l(nullptr), r(nullptr) {
	}  
};
struct SegmentTree {
	int vertN, vertL, vertR; SegNode* root = nullptr;
	// vertN -> Vertical height (# of cols), vertL -> Current vertical left query, vertR -> Current vertical right query
	// vertL -> Vertical coordinate of query box, q (param) -> Horizontal coordinate
	ll update(SegNode* &cur, int l, int r, int q, ll v) {
		if (!cur) cur = new SegNode(vertN);
		// debug(l, r, q, v);

		if (q < l || q > r) {
			auto ptr = cur->bst.search(cur->bst.root, vertL);
			return ptr ? ptr->aux : 0LL;
		}
		if (q == l && q == r) {
			seqOp::update(cur->bst, vertL, v);
			return v;
		}

		int mid = (l + r) >> 1;
		ll ret = mergeVals(update(cur->l, l, mid, q, v), update(cur->r, mid + 1, r, q, v));
		seqOp::update(cur->bst, vertL, ret);
		return ret;
	}
	ll query(SegNode* &cur, int l, int r, int ql, int qr) {
		if (!cur || (ql > r || qr < l)) return 0LL;
		if (l >= ql && r <= qr) return /*debug(l, r, ql, qr),  */cur->bst.query(vertL, vertR);

		int mid = (l + r) >> 1;
		return mergeVals(query(cur->l, l, mid, ql, qr), query(cur->r, mid + 1, r, ql, qr));
	}
};

int R, C;
SegmentTree seg;

void init(int R0, int C0) {
	R = R0; C = C0;
	seg.vertN = C;
}

void update(int P, int Q, long long K) {
	P++; Q++;

	seg.vertL = Q;
	seg.update(seg.root, 1, R, P, K);
}

long long calculate(int P, int Q, int U, int V) {
	P++; Q++; U++; V++;

	seg.vertL = Q;
	seg.vertR = V;
	return seg.query(seg.root, 1, R, P, U);
}


int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N, M, Q;
	cin >> N >> M >> Q;
	init(N, M);
	while (Q--) {
	    int T; cin >> T;
	    if (T == 1) {
	        int P, Q; ll K;
	        cin >> P >> Q >> K;
	        update(P, Q, K);
	    }
	    else {
	        int P, Q, U, V;
	        cin >> P >> Q >> U >> V;
	        cout << calculate(P, Q, U, V) << '\n';
	    }
	}

	return 0;
}