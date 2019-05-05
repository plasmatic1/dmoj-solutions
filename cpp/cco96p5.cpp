//============================================================================
// Name        : cco96p5.cpp
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

#define CHR(x) ((int)((x) - 'A'))

const int MAX = 27, R = CHR('R');
int n, m,
	par[MAX], levels[MAX];
string ba, bb;
vector<int> matrix[MAX];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	scan(n, m);

	for (int i = 0; i < n; i++) {
		scan(ba, bb);
		int a = CHR(ba[0]), b = CHR(bb[0]);
		matrix[a].push_back(b);
		matrix[b].push_back(a);
	}

	for (int i = 0; i < m; ++i) {
		scan(ba, bb);
		int a = CHR(ba[0]), b = CHR(bb[0]);

		deque<int> nxt;
		memset(levels, -1, sizeof levels);
		memset(par, -1, sizeof par);
		levels[b] = 0;
		nxt.push_back(b);

		while (!nxt.empty()) {
			int cur = nxt.front(), level = levels[cur];
			nxt.pop_front();

			for (int adj : matrix[cur]) {
				if (levels[adj] == -1) {
					par[adj] = cur;
					levels[adj] = level + 1;
					nxt.push_back(adj);
				}
			}
		}

		while(a != -1) {
			putchar(a + 'A');
			a = par[a];
		}
		putchar('\n');
	}

	return 0;
}
