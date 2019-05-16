//============================================================================
// Name        : year2018p6.cpp
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

struct qu {
	int i, l, r;

	bool operator<(const qu &o) const {
		return r < o.r;
	}
};

const int MAX = 50001;
constexpr int SQM = sqrt(MAX << 1) + 5, LOG = log2(MAX) + 1;
int n, q, ba, bb, ordSz,
	val[MAX], dfn[MAX], ans[MAX], blockn[MAX << 1];
vector<int> ord,
	matrix[MAX];
multiset<int> vals, diffs;
vector<qu> qus[SQM];
bool added[MAX];

void dfs(int cur, int par) {
	ord.push_back(cur);
	for (int adj : matrix[cur])
		if (adj ^ par)
			dfs(adj, cur);
	ord.push_back(cur);
}

// LCA Stuff
int pars[LOG][MAX], levels[MAX];

void lcaDfs(int cur, int par, int lv) {
	levels[cur] = lv;
	pars[0][cur] = par;
	for (int adj : matrix[cur])
		if (adj ^ par)
			lcaDfs(adj, cur, lv + 1);
}

inline int lca(int a, int b) {
	if (levels[a] > levels[b])
		swap(a, b);

	int delta = levels[b] - levels[a];
	for (int i = LOG - 1; i >= 0; i--)
		if ((delta >> i) & 1)
			b = pars[i][b];

	if (a == b)
		return a;

	for (int i = LOG - 1; i >= 0; i--) {
		if (pars[i][a] != pars[i][b]) {
			a = pars[i][a];
			b = pars[i][b];
		}
	}

	return pars[0][a];
}

// Answer Queries
inline void ins(int x) {
	auto it = vals.insert(x);

	if (vals.size() > (size_t)1) {
		if (it == vals.begin())
			diffs.insert(*(++vals.begin()) - x);
		else if (it == --vals.end())
			diffs.insert(x - *(--it));
		else {
			auto nxt = it, pre = it; ++nxt; --pre;
			diffs.erase(diffs.find(*nxt - *pre));
			diffs.insert(*nxt - x);
			diffs.insert(x - *pre);
		}
	}
}

inline void del(int x) {
	auto it = vals.find(x), cpit = it;

	if (vals.size() > (size_t)1) {
		if (it == vals.begin())
			diffs.erase(diffs.find(*(++vals.begin()) - x));
		else if (it == --vals.end())
			diffs.erase(diffs.find(x - *(--cpit)));
		else {
			auto nxt = it, pre = it; ++nxt; --pre;
			diffs.erase(diffs.find(*nxt - x));
			diffs.erase(diffs.find(x - *pre));
			diffs.insert(*nxt - *pre);
		}
	}

	vals.erase(it);
}

inline void introduce(int node) {
	int x = val[node];

	if (added[node])
		del(x);
	else
		ins(x);

	added[node] ^= 1;
}

inline int minDiff() { return *diffs.begin(); }

inline int ansFor(int a, int b) { // Assumes that diffs and vals have been set up already
	int trueA = ord[a], trueB = ord[b], lcaOf = lca(trueA, trueB);

	if (lcaOf == trueA)
		return minDiff();

	ins(val[trueA]);
	ins(val[lcaOf]);
	int cAns = minDiff();
	del(val[trueA]);
	del(val[lcaOf]);

	return cAns;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	scan(n, q);

	for (int i = 1; i <= n; ++i)
		scan(val[i]);

	for (int i = 1; i < n; ++i) {
		scan(ba, bb);
		matrix[ba].push_back(bb);
		matrix[bb].push_back(ba);
	}

	// Dfn/Modified euler tour
	ord.push_back(-1);
	dfs(1, -1);
	ordSz = ord.size() - 1;

	memset(dfn, -1, sizeof dfn);
	for (int i = 1; i <= ordSz; i++)
		if (dfn[ord[i]] == -1)
			dfn[ord[i]] = i;

	int sqo = sqrt(ordSz);
	for (int i = 1; i <= ordSz; i++)
		blockn[i] = i / sqo;

	// Lca Building
	lcaDfs(1, -1, 0);

	for (int i = 1; i < LOG; ++i)
		for (int j = 1; j <= n; ++j)
			pars[i][j] = pars[i - 1][j] == -1 ? -1 : pars[i - 1][pars[i - 1][j]];

	// Query Processing
	for (int i = 0; i < q; ++i) {
		scan(ba, bb);
		ba = dfn[ba]; bb = dfn[bb];
		if (ba > bb)
			swap(ba, bb);

		qus[blockn[ba]].push_back({i, ba, bb});
	}

	int last = blockn[ordSz];
	for (int i = 0; i <= last; ++i) {
		vector<qu> &cqus = qus[i];
		if (!cqus.size())
			continue;

		sort(cqus.begin(), cqus.end());
		int sz = cqus.size();

		for (int j = cqus[0].l; j <= cqus[0].r; j++)
			introduce(ord[j]);
		ans[cqus[0].i] = ansFor(cqus[0].l, cqus[0].r);
		for (int j = 1; j < sz; ++j) {
			for (int k = cqus[j - 1].r + 1; k <= cqus[j].r; k++)
				introduce(ord[k]);
			if (cqus[j - 1].l < cqus[j].l)
				for (int k = cqus[j - 1].l; k < cqus[j].l; k++)
					introduce(ord[k]);
			else
				for (int k = cqus[j].l; k < cqus[j - 1].l; k++)
					introduce(ord[k]);
			ans[cqus[j].i] = ansFor(cqus[j].l, cqus[j].r);
		}

		diffs.clear();
		vals.clear();
		memset(added, 0, sizeof added);
	}

	// Print answers
	for (int i = 0; i < q; ++i)
		cout << ans[i] << "\n";
}
