//============================================================================
// Name        : dmpg19s4.cpp
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

const int MAX = 100001;
int n, m, q,
	bestFor[MAX][26]; // Best word # for (i, j) word #i beginning with letter j
string ba, bb,
	strs[MAX];
unordered_map<string, int> ranks;
vector<string> sortStrs[26];
vector<int> matrix[MAX];

#define CHR(x) (int)((x) - 'A')

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	scan(n, m, q);

	for (int i = 0; i < n; i++) {
		scan(strs[i]);
		ranks[strs[i]] = i;
		sortStrs[CHR(strs[i][0])].push_back(strs[i]);
	}

	for (int i = 0; i < m; ++i) {
		scan(ba, bb);
		int ra = ranks[ba], rb = ranks[bb];
		matrix[ra].push_back(rb);
		matrix[rb].push_back(ra);
	}

	memset(bestFor, -1, sizeof bestFor);
	for (int i = 0; i < 26; ++i) {
		deque<int> nxt;
		int levels[n], fromNode[n];
		memset(levels, -1, sizeof levels);

		sort(sortStrs[i].begin(), sortStrs[i].end());
		for (string s : sortStrs[i]) {
			int rs = ranks[s];
			levels[rs] = 0;
			nxt.push_back(rs);
			bestFor[rs][i] = fromNode[rs] = rs;
		}

		while(!nxt.empty()) {
			int cur = nxt.front(), from = fromNode[cur], level = levels[cur];
			nxt.pop_front();

			for (int adj : matrix[cur]) {
				if (levels[adj] == -1) {
					levels[adj] = level + 1;
					fromNode[adj] = from;
					nxt.push_back(adj);

					bestFor[adj][i] = from;
				}
			}
		}
	}

//	for (int i = 0; i < 26; i++){
//		char c = i + 'A';
//		for (int j = 0; j < n; j++)
//			printf("ch=%c s=%s v=%d\n", c, strs[j].c_str(), bestFor[j][i]);
//	}

	for (int i = 0; i < q; ++i) {
		scan(ba, bb);
		int ra = ranks[ba], x = CHR(bb[0]);
		if (bestFor[ra][x] != -1)
			printf("%s\n", strs[bestFor[ra][x]].c_str());
		else
			printf("-1\n");
	}

	return 0;
}
