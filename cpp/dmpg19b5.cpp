//============================================================================
// Name        : dmpg19b5.cpp
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

struct t {
	int i, x, c;

	bool operator<(const t &o) const {
		return x < o.x;
	}
};

const int MAX = 200001;
int n, devnull;
t tria[MAX];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	scan(n);

	for (int i = 1; i <= n; i++) {
		tria[i].i = i;
		scan(tria[i].x, devnull, tria[i].c);
	}
	sort(tria + 1, tria + n + 1);

	int last = n - 2;
	for (int i = 1; i <= last; i++) {
		if (!(tria[i].c == tria[i + 1].c && tria[i + 1].c == tria[i + 2].c)) {
			printf("%d %d %d\n", tria[i].i, tria[i + 1].i, tria[i + 2].i);
			return 0;
		}
	}

	printf("-1\n");

	return 0;
}
