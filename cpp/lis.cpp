//============================================================================
// Name        : LongestIncreasingSubsequence.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 1000001;

struct ed{
	int v, w;

	ed(int v0, int w0) : v(v0), w(w0){}
	ed() : v(-1), w(-1){}

	friend bool operator<(const ed &a, const ed &b){
		return a.w < b.w;
	}

	friend bool operator==(const ed &a, const ed &b){
		return a.w == b.w;
	}
};

int n, buf, maxsz = 0,
	sizes[MAX];
set<ed> nums;

const int INF = 0x3f3f3f3f;

inline void insert(int i, int sz){
	if(sizes[sz] == INF){
		maxsz = max(maxsz, sz);

		sizes[sz] = i;
		nums.emplace(sz, i);
	}
	else if(i < sizes[sz]){
		maxsz = max(maxsz, sz);

		nums.erase(nums.find(ed(sz, sizes[sz])));
		sizes[sz] = i;
		nums.emplace(sz, i);
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;
	memset(sizes, 0x3f, sizeof(sizes));

	nums.emplace(0, INT_MIN);

	for (int i = 1; i <= n; ++i) {
		cin >> buf;
		auto szptr = nums.lower_bound(ed(-1, buf));

//		printf("for i=%d buf=%d got s-v=%d, s-w=%d\n", i, buf, szptr->v, szptr->w);

//		if(szptr == nums.begin()){
//			insert(buf, 1);
//		}
//		else{
			insert(buf, (--szptr)->v + 1);
//		}
	}

	printf("%d\n", maxsz);
}
