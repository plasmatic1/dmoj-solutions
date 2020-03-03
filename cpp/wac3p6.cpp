#pragma region
#include <bits/stdc++.h>
using namespace std;
// Common Type shorteners and int128
using ll = long long; using ull = unsigned long long; using ld = long double;
using pii = pair<int, int>; using pll = pair<ll, ll>;
template <typename T> using vec = vector<T>;
template <typename K, typename V> using umap = unordered_map<K, V>; template <typename K> using uset = unordered_set<K>;
using vi = vec<int>; using vl = vec<ll>; using vpi = vec<pii>; using vpl = vec<pll>;
#ifdef __SIZEOF_INT128__
using int128 = __int128_t; using uint128 = __uint128_t;
#endif
template<typename I> string intStr(I x) { string ret; while (x > 0) { ret += (x % 10) + '0'; x /= 10; } reverse(ret.begin(), ret.end()); return ret; } // Int to string
// Shorthand Macros
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
#define mpr make_pair
#define mtup make_tuple
#define pb push_back
#define popcount __builtin_popcount
#define clz __builtin_clz
#define ctz __builtin_ctz
#define finline __attribute__((always_inline))
// Shorthand Function Macros
#define sz(x) ((int)((x).size()))
#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for (__typeof(a) i = a; i < b; i++)
#define reprev(i, a, b) for (__typeof(a) i = a; i > b; i--)
#define repi(a, b) rep(i, a, b)
#define repj(a, b) rep(j, a, b)
#define repk(a, b) rep(k, a, b)
#define Cmplt(type) bool operator<(const type &o) const
#define Cmpgt(type) bool operator>(const type &o) const
#define Cmpfn(name, type) bool name(const type &a, const type &b)
#define Inop(type) istream& operator>>(istream& in, type &o)
#define Outop(type) ostream& operator<<(ostream& out, type o)
#define Pow2(x) (1LL << (x))
#define scn(type, ...) type __VA_ARGS__; scan(__VA_ARGS__) // scn -> Short for SCan New
// Shorthand Functions
template<typename T> inline void maxa(T& st, T v) { st = max(st, v); }
template<typename T> inline void mina(T& st, T v) { st = min(st, v); }
inline void setprec(ostream& out, int prec) { out << setprecision(prec) << fixed; }
// Out operators and printing for arrays and vectors
template <typename T> ostream& operator<<(ostream& out,vector<T> iter){out<<"[";for(auto t:iter){out<<t<<", ";}out<<"]";return out;}
template <typename T> string arrayStr(T *arr,int sz){string ret = "[";for(int i=0;i<sz;i++){ret+=to_string(arr[i])+", "; } return ret + "]";}
template <typename T> void printArray(T *arr,int sz){for(int i=0;i<sz;i++){cout<<arr[i]<<" "; } cout<<"\n";}
// I/O Operations
inline void scan(){}
template<typename F, typename... R> inline void scan(F &f,R&... r){cin>>f;scan(r...);}
template <typename F> inline void println(F t){cout<<t<<'\n';}
template<typename F, typename... R> inline void println(F f,R... r){cout<<f<<" ";println(r...);}
inline void print(){}
template<typename F, typename... R> inline void print(F f,R... r){cout<<f;print(r...);}
// Debugging
#define db(x) cout << (#x) << ": " << (x) << ", "
#define dblb(s) cout << "[" << (s) << "] "
#define dba(alias, x) cout << (alias) << ": " << (x) << ", "
template<typename F> inline string __generic_tostring(F f) { stringstream ss; ss << f; return ss.str(); }
template<typename F> inline string __join_comma(F f) {return __generic_tostring(f);}
template<typename F, typename... R> string __join_comma(F f, R... r) { return __generic_tostring(f) + ", " + __join_comma(r...); }
#define dbp(alias, ...) cout << (alias) << ": (" << __join_comma(__VA_ARGS__) << "), "
#define dbbin(x, n) cout << (#x) << ": " << bitset<n>(x) << ", "
#define dbarr(x, n) cout << (#x) << ": " << arrayStr((x), (n)) << ", "
#define dbln cout << endl;
#pragma endregion
#undef sz

struct Sub {
	int c, p, r;
};

Inop(Sub) {
	in >> o.c >> o.p >> o.r;
	return in;
}

/*
POSITIONS ARE 1-INDEXED

SPLIT(idx) -> LHS: [1, idx], RHS: [idx+1, N]
INSERT(idx, x) -> Insert (x) after pos [idx]
*/
ll seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 gen(seed);
uniform_int_distribution<int> dis;
struct Node {
    int pri, sz, val; bool real; Node *l, *r, *par;
    Node(int val0) : pri(dis(gen)), sz(1), val(val0), real(true), l(nullptr), r(nullptr), par(nullptr) { }
};
struct ParentMaintainedImplicitTreap {
    Node* root;
    ParentMaintainedImplicitTreap() : root(nullptr) {}
    inline int sz(Node* &cur) { return cur ? cur->sz : 0; }
    void upd(Node* cur) {
        if (cur) {
            cur->sz = sz(cur->l) + sz(cur->r) + cur->real;
            if (cur->l) cur->l->par = cur;
            if (cur->r) cur->r->par = cur;
        }
    }
    void split(Node* cur, int key, Node* &l, Node* &r) {
        if (!cur) return void(l = r = nullptr);
        cur->par = nullptr;
        if (key < sz(cur->l) + cur->real) { split(cur->l, key, l, cur->l); r = cur; }
        else { split(cur->r, key - sz(cur->l) - cur->real, cur->r, r); l = cur; }
        upd(cur);
    }
    void merge(Node* &cur, Node* l, Node* r) {
        if (!l || !r) cur = l ? l : r;
        else if (l->pri > r->pri) { merge(l->r, l->r, r); cur = l; }
        else { merge(r->l, l, r->l); cur = r; }
        upd(cur);
    }
    void insert(Node* &cur, int key, Node* node) {
        Node* rhs;
        split(cur, key, cur, rhs);
        merge(cur, cur, node);
        merge(cur, cur, rhs);
    }
    void inOrder(Node* &cur, vec<int> &v) {
        if (!cur) return;
        inOrder(cur->l, v); v.pb(cur->val); inOrder(cur->r, v);
    }
    int index(Node* cur) {
        if (!cur) return -1;
        int ind = sz(cur->l) + cur->real;
        for (; cur->par; cur = cur->par)
            if (cur != cur->par->l)
                ind += sz(cur->par->l) + cur->real;
        return ind;
    }
	void invalidate(Node* cur) {
		cur->real = false;
		upd(cur);
		while (cur->par) {
			cur = cur->par;
			upd(cur);
		}
	}
};

const int MN = 2e5 + 1, MSUB = MN * 3;
int n, m, k;

// submissions stuff
int subId[4][MN]; // id of submission for X-th solved problem for user
Sub subs[MSUB];

// rankings
int probCnt[MN], subPc[MSUB], userCount[4]; // probCnt -> problem solve counts per user, subPc -> submission gets X solved problems for user, userCount -> No. solved for user
ParentMaintainedImplicitTreap ranks[4];
Node* curNode[MN]; // cur block in Implicit Sqrt for each node

// problems stuffs
int probPenalty[MN][3], probWaPenalty[MN][3];
inline int penalty(int c) {
	ll tot = 0;
	repi(0, m)
		tot += probPenalty[c][i] + 10 * probWaPenalty[c][i];
	return tot;
}

inline string problemScore(int user, int problem) {
	if (probPenalty[user][problem] == -1) return "-/-";
	return to_string(probPenalty[user][problem]) + "/" + to_string(probWaPenalty[user][problem]);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	scan(n, m, k);

	// loop through submissions
	repi(0, k) {
		scan(subs[i]);
		auto &sub = subs[i];

		// update some auxillary stuffs
		int pc = ++probCnt[sub.c];
		subPc[i] = pc;
		subId[pc][sub.c] = i;
		userCount[pc - 1]--;
		userCount[pc]++;

		// make previously inserted node in treap invalid
		if (pc > 1)
			ranks[pc - 1].invalidate(curNode[sub.c]);

		// calculate true index and insert node
		int trueRank = sub.r;
		repj(pc + 1, m + 1)
			trueRank -= userCount[j];
		curNode[sub.c] = new Node(sub.c);
		ranks[pc].insert(ranks[pc].root, trueRank - 1, curNode[sub.c]);
    }

	// set penalties
	memset(probPenalty, -1, sizeof probPenalty);
	repi(1, m + 1) {
		// set initial penalties for solving problems
		repj(0, k) {
			if (subPc[j] == i) {
				auto &sub = subs[j];
				probPenalty[sub.c][sub.p - 1] = j + 1;
			}
		}

		// === determine submission rankings
		vi csubs, users;
		ranks[i].inOrder(ranks[i].root, users);
		for (auto &c : users)
			csubs.pb(subId[i][c]);

		// === greedily set penalties 
		int sz = csubs.size();
		repi(1, sz) {
			auto &cur = subs[csubs[i]], &pre = subs[csubs[i - 1]];

			// C penalty has to be greater than P
			int reqTime = penalty(pre.c) - penalty(cur.c) + 1;
			if (reqTime > 0) {
				int times = (reqTime + 10 - 1) / 10;
				probWaPenalty[cur.c][cur.p - 1] += times;
			}
		}
	}

	// print ans
	vi order(n);
	iota(all(order), 1);
	sort(all(order), [&] (const int &a, const int &b) {
		if (probCnt[a] == probCnt[b]) {
			int pena = penalty(a), penb = penalty(b);
			if (pena == penb)
				return a < b;
			return pena < penb;
		}
		return probCnt[a] > probCnt[b];
	});
	repi(0, n) {
		int user = order[i];
		print(user, ' ');
		repj(0, m)
			print(problemScore(user, j), ' ');
		print('\n');
	}

	return 0;
}