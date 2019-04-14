//============================================================================
// Name        : stnbd4.cpp
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

struct qu{
	int i, l, r;

	bool operator<(const qu &o) const {
		return r < o.r;
	}
};

const int MAX = 100001, SQM = sqrt(MAX) + 10;
int n, q, bl, br, rnkSz = 0,
	blockn[MAX], arr[MAX], tree[MAX];
unordered_map<int, int> ranks;
vector<qu> queries[SQM];
ll invCnt = 0,
	ans[MAX];

inline int sum(int i){
	int sum = 0;
	for (; i; i -= i & -i)
		sum += tree[i];
	return sum;
}

inline void add(int i, int v){
	for (; i <= rnkSz; i += i & -i)
		tree[i] += v;
}

inline void pushBackNum(int v){
	invCnt += sum(rnkSz) - sum(v);
	add(v, 1);
}

inline void pushFrontNum(int v){
	invCnt += sum(v - 1);
	add(v, 1);
}

inline void popFrontNum(int v){
	invCnt -= sum(v - 1);
	add(v, -1);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	scan(n);

	set<int> tranks;
	int sqn = sqrt(n);
	for (int i = 1; i <= n; i++) {
		scan(arr[i]);
		blockn[i] = i / sqn;
		tranks.insert(arr[i]);
	}

	for (int x : tranks)
		ranks[x] = ++rnkSz;
	for (int i = 1; i <= n; i++)
		arr[i] = ranks[arr[i]];

	scan(q);

	int end = n / sqn + 1;
	for (int i = 0; i < q; ++i) {
		scan(bl, br);
		queries[blockn[bl]].push_back({i, bl, br});
	}

	for (int i = 0; i < end; i++)
		sort(queries[i].begin(), queries[i].end());

	for (int i = 0; i < end; ++i) {
		vector<qu> &qus = queries[i];
		int sz = qus.size();

		if(!sz)
			continue;

		for (int j = qus[0].l; j <= qus[0].r; j++)
			pushBackNum(arr[j]);
		ans[qus[0].i] = invCnt;

		for (int j = 1; j < sz; j++){
			int curL = qus[j].l, lastL = qus[j - 1].l;
			for (int k = qus[j - 1].r + 1; k <= qus[j].r; k++)
				pushBackNum(arr[k]);
			if(curL >= lastL)
				for (int k = lastL; k < curL; k++)
					popFrontNum(arr[k]);
			else
				for (int k = lastL - 1; k >= curL; k--)
					pushFrontNum(arr[k]);

			ans[qus[j].i] = invCnt;
		}

		memset(tree, 0, sizeof tree);
		invCnt = 0;
	}

	for (int i = 0; i < q; i++)
		printf("%lld\n", ans[i]);
}