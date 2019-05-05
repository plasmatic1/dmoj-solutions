//============================================================================
// Name        : coci14c5p3.cpp
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

const int MAX = 1000001, MX = 100001;
int n, k,
	x[MAX], y[MAX];
vector<pair<int, int>> rows[MX], cols[MX];
unordered_map<int, vector<pair<int, int>>> diags[2];

inline void bestOf(vector<pair<int, int>> &vec, int &best, int maxId) {
	queue<int> qu;
	for (int i = 0, sz = vec.size(); i < sz; i++) {
		if (vec[i].second < maxId)
			qu.push(vec[i].first);
		while (!qu.empty() && qu.size() > (size_t)k)
			qu.pop();
		if (qu.size() == (size_t)k)
			best = min(best, qu.back() - qu.front());
	}
}


int sim (int maxId) {
	int best = 0x3f3f3f3f;

	for (int i = 0; i < MX; i++) {
		if (rows[i].size() >= (size_t)k)
			bestOf(rows[i], best, maxId);
		if (cols[i].size() >= (size_t)k)
			bestOf(cols[i], best, maxId);
	}
	for (int i = 0; i < 2; i++)
		for (auto it = diags[i].begin(); it != diags[i].end(); it++)
			if (it->second.size() >= (size_t)k)
				bestOf(it->second, best, maxId);

	return best;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	scan(n, k);

	for (int i = 0; i < n; i++) {
		scan(x[i], y[i]);
		rows[y[i]].push_back(make_pair(x[i], i));
		cols[x[i]].push_back(make_pair(y[i], i));
		diags[0][x[i] - y[i]].push_back(make_pair(x[i], i));
		diags[1][-x[i] - y[i]].push_back(make_pair(x[i], i));
	}

	for (int i = 0; i < MX; i++) {
		sort(rows[i].begin(), rows[i].end());
		sort(cols[i].begin(), cols[i].end());
	}
	for (int i = 0; i < 2; i++)
		for (auto it = diags[1].begin(); it != diags[1].end(); it++)
			sort(it->second.begin(), it->second.end());

	int l = -1, r = n;
	while(l + 1 < r) {
		int mid = (l + r) >> 1;
//		debug(l, r, mid, sim(mid));

		if (sim(mid) > mid)
			l = mid;
		else
			r = mid;
	}

	printf("%d\n", max(r, sim(r)));

	return 0;
}
