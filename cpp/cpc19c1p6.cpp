//============================================================================
// Name        : cpc18c1p5.cpp
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

const int MAX = 100001, INF = 0x3f3f3f3f;
const size_t BSIZE = 1200, MBSIZE = BSIZE << 1;
int n, q, ba, bb, bc, lastAns = 0;
char bt;
vector<vector<int>> blocks;
vector<unordered_map<int, int>> cnts;

// Also transforms the idx into an index inside the block
inline int blockOf(int &idx) {
	int blk = INF;
	for (int j = 0; j < blocks.size(); j++) {
		idx -= blocks[j].size();
		if (idx < 0) {
			idx += blocks[j].size();
			blk = j;
			break;
		}
	}

	return blk;
}

inline void insertNew() {
	blocks.push_back(vector<int>());
	cnts.push_back(unordered_map<int, int>());
}

inline void split(int blk) {
	blocks.insert(blocks.begin() + blk + 1, vector<int>());
	cnts.insert(cnts.begin() + blk + 1, unordered_map<int, int>());
	vector<int> &nxt = blocks[blk + 1];
	unordered_map<int, int> &nxtCnt = cnts[blk + 1];

	nxt.insert(nxt.begin(), blocks[blk].begin() + BSIZE, blocks[blk].end());
	for (int i = BSIZE; i < blocks[blk].size(); i++) {
		nxtCnt[blocks[blk][i]]++;
		cnts[blk][blocks[blk][i]]--;
	}
	blocks[blk].resize(BSIZE);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	scan(n, q);

	insertNew();

	int cidx = 0;
	for (int i = 1; i <= n; ++i) {
		scan(ba);

		if (blocks[cidx].size() > BSIZE) {
			insertNew();
			cidx++;
		}

		blocks[cidx].push_back(ba);
		cnts[cidx][ba]++;
	}

	for (int i = 0; i < q; ++i) {
		scan(bt, ba);
		ba ^= lastAns;

		if (bt == 'I') {
			scan(bb);
			bb ^= lastAns;
			int blk = blockOf(ba);

			if (blk == INF) {
				blocks[blocks.size() - 1].push_back(bb);
				cnts[blocks.size() - 1][bb]++;
				blk = blocks.size() - 1;
			}
			else {
				blocks[blk].insert(blocks[blk].begin() + ba, bb);
				cnts[blk][bb]++;
			}

			if (blocks[blk].size() > MBSIZE)
				split(blk);
		}
		else if (bt == 'D') {
			ba--;
			int blk = blockOf(ba);

			cnts[blk][blocks[blk][ba]]--;
			blocks[blk].erase(blocks[blk].begin() + ba);
		}
		else { // bt == 'C'
			scan(bb, bc);
			bb ^= lastAns;
			bc ^= lastAns;
			ba--;
			bb--;

			lastAns = 0;
			int st = blockOf(ba), en = blockOf(bb);
//			debug(i, ba, bb, bc, st, en);
			if (st != en) {
				for (int j = ba; j < blocks[st].size(); ++j)
					lastAns += blocks[st][j] == bc;
				for (int j = 0; j <= bb; ++j)
					lastAns += blocks[en][j] == bc;
				for (int j = st + 1; j < en; ++j) {
					if (cnts[j].find(bc) != cnts[j].end())
						lastAns += cnts[j][bc];
				}
			}
			else
				for (int j = ba; j <= bb; ++j)
					lastAns += blocks[st][j] == bc;

			cout << lastAns << "\n";
//			lastAns = 0;
		}

//		if (n == 99967 && q == 99931) {
//			int ss=0;
//			for (auto b : blocks)
//				ss += b.size();
//			assert(ss<100000);
//		}

//		setbuf(stdout, 0);
//		cout << "blocks: [";
//		for (auto i : blocks) {
//			cout << "i: [";
//			for (auto ix : i)
//				cout << ix << " ";
//			cout << "]\n";
//		}
//		cout << "]\n";
	}

	return 0;
}