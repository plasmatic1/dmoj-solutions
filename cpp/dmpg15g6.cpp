//============================================================================
// Name        : dmpg15g6.cpp
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

const int MAX = 200001, MSQ = sqrt(MAX) + 10;
int n, m, q, bl, br,
	arr[MAX], blockn[MAX], cnt[MAX], cntTree[MAX];
bool ans[MAX];
vector<qu> queries[MSQ];
// cnt[i] -> amount of pieces for flavour i
// cntTree[i] -> (Reversed BIT) amount of flavours with i pieces

inline int sum(int x) {
	x = n - x + 1;
	int sum = 0;
	for (; x; x -= x & -x)
		sum += cntTree[x];
	return sum;
}

inline void add(int x, int v) {
	x = n - x + 1;
	if(x == 0) return;
	for (; x <= n; x += x & -x)
		cntTree[x] += v;
}

inline void addFlavour(int flav) {
	add(cnt[flav], -1);
	add(++cnt[flav], 1);
}

inline void removeFlavour(int flav) {
	add(cnt[flav], -1);
	add(--cnt[flav], 1);
}

inline int ceilDiv(int x, int y) {
	if (x % y)
		return x / y + 1;
	return x / y;
}

inline bool query(int len) {
	return (sum(ceilDiv(len, 3)) >= 2) || (sum(ceilDiv(len << 1, 3)) >= 1);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	scan(n, m);

	int sqn = sqrt(n);
	for (int i = 1; i <= n; i++) {
		scan(arr[i]);
		blockn[i] = i / sqn;
	}

	scan(q);

	int endQ = blockn[n];
	for (int i = 0; i < q; i++) {
		scan(bl, br);
		queries[blockn[bl]].push_back({i, bl, br});
	}

	for (int i = 0; i <= endQ; i++)
		sort(queries[i].begin(), queries[i].end());

	for (int i = 0; i <= endQ; i++) {
		vector<qu> &qus = queries[i];
		int sz = qus.size();

		if(!sz)
			continue;

		for (int j = qus[0].l; j <= qus[0].r; j++)
			addFlavour(arr[j]); //, debug(i, j);
		ans[qus[0].i] = query(qus[0].r - qus[0].l + 1);

		for (int j = 1; j < sz; j++) {
			for (int k = qus[j - 1].r + 1; k <= qus[j].r; k++)
				addFlavour(arr[k]);
			if (qus[j].l <= qus[j - 1].l)
				for (int k = qus[j].l; k < qus[j - 1].l; k++)
					addFlavour(arr[k]);
			else
				for (int k = qus[j - 1].l; k < qus[j].l; k++)
					removeFlavour(arr[k]);

			ans[qus[j].i] = query(qus[j].r - qus[j].l + 1);
		}

		memset(cnt, 0, sizeof cnt);
		memset(cntTree, 0, sizeof cntTree);
	}

	for (int i = 0; i < q; i++)
		printf(ans[i] ? "YES\n" : "NO\n");
}