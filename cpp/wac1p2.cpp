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

const int MAX = 100001;
int n, m, k, ba, bb, extra = 0,
	dset[MAX];

int rt(int x) {
	return dset[x] == x ? x : dset[x] = rt(dset[x]);
}

inline void merge(int x, int y) {
	dset[rt(x)] = rt(y);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	scan(n, m, k);

	for (int i = 1; i <= n; i++)
		dset[i] = i;

	for (int i = 0; i < m; ++i) {
		scan(ba, bb);

		if (rt(ba) == rt(bb))
			extra++;
		else
			merge(ba, bb);
	}

	unordered_set<int> x;
	for (int i = 1; i <= n; i++)
		x.insert(rt(i));
	int needed = x.size() - 1;
	printf("%d\n", max(0, needed - min(extra, k)));

	return 0;
}