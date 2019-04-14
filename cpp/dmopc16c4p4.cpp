//============================================================================
// Name        : dmopc16c4p4.cpp
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

const int MAX = 100001, SQM = sqrt(MAX) + 10;
int n, q, bl, br, cur = 0,
	arr[MAX], blockn[MAX], cnt[MAX], ans[MAX];

struct qu{
	int i, l, r;

	bool operator<(const qu &o) const {
		return r < o.r;
	}
};
vector<qu> queries[SQM];

inline void add(int x){
	if(cnt[x]){
		if(cnt[x] & 1)
			cur++;
		else
			cur--;
	}

	cnt[x]++;
}

inline void del(int x){
	if(cnt[x] > 1){
		if(cnt[x] & 1)
			cur++;
		else
			cur--;
	}

	cnt[x]--;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	scan(n);

	int sqn = sqrt(n), end = (n - 1) / sqn;
	for (int i = 0; i < n; i++){
		scan(arr[i]);
		blockn[i] = i / sqn;
	}

	scan(q);

	for (int i = 0; i < q; ++i) {
		scan(bl, br);
		bl--;
		br--;

		queries[blockn[bl]].push_back({i, bl, br});
	}
	for (int i = 0; i < end; ++i)
		sort(queries[i].begin(), queries[i].end());

	for (int i = 0; i < end; ++i) {
		vector<qu> &qus = queries[i];

		if(!qus.size())
			continue;

		for (int j = qus[0].l; j <= qus[0].r; j++)
			add(arr[j]);
		ans[qus[0].i] = cur;

#define curl qus[j].l
#define lastl qus[j - 1].l

		int sz = qus.size();
		for (int j = 1; j < sz; j++){
			for (int k = qus[j - 1].r + 1; k <= qus[j].r; k++)
				add(arr[k]);

			if(curl >= lastl){
				for (int k = lastl; k < curl; k++)
					del(arr[k]);
			}
			else{
				for (int k = curl; k < lastl; k++)
					add(arr[k]);
			}

			ans[qus[j].i] = cur;
		}

		memset(cnt, 0, sizeof cnt);
		cur = 0;
	}

	for (int i = 0; i < q; i++)
		printf("%d\n", ans[i]);
}