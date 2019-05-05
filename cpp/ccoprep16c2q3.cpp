//============================================================================
// Name        : ccoprep16c2q3.cpp
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

const int MAX = 200001;
int n, q, ba, bb, bt,
	pfx[MAX], toNext[MAX], steps[MAX], blockn[MAX];
/*
arr -> array of powers
toNext -> next item outside of current block (-1 if not possible)
steps -> # of steps to next block
 */

// Returns the left value of the block
inline int assignBlock(int blockX, int right) {
	int lastV = -1;
	for (int j = right; blockn[j] == blockX && j >= 0; j--) {
		int nextV = j + pfx[j];

		if (nextV >= n)
			toNext[j] = -1;
		else if (blockn[nextV] > blockX)
			toNext[j] = nextV;
		else
			toNext[j] = toNext[nextV];

		if (nextV >= n || blockn[nextV] > blockX)
			steps[j] = 1;
		else
			steps[j] = steps[nextV] + 1;

		lastV = j;
	}

	return lastV;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	scan(n);

	int sqn = sqrt(n), last = (n - 1) / sqn;
	for (int i = 0; i < n; i++) {
		scan(pfx[i]);
		blockn[i] = i / sqn;
	}

	int right = n - 1;
	for (int i = last; i >= 0; i--)
		right = assignBlock(i, right) - 1;

	scan(q);

	for (int i = 0; i < q; ++i) {
		scan(bt, ba);

		if (bt == 1) {
			int tot = 0;
			while (ba != -1) {
				tot += steps[ba];
				ba = toNext[ba];
			}
			printf("%d\n", tot);
		}
		else { // bt == 2
			scan(bb);
			pfx[ba] = bb;

			int block = blockn[ba], right = (upper_bound(blockn, blockn + n, block) - blockn) - 1;
			assignBlock(block, right);
		}
	}

	return 0;
}
