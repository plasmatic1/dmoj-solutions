//============================================================================
// Name        : RogerSegmentTreeRecode.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
//#define DEBUG

using namespace std;

typedef long long ll;

const int MAX = 100001, MV = 65536, B_MAX = 16;

struct rg{
	int l, r, i;

	rg(int l0, int r0, int i0) : l(l0), r(r0), i(i0){}
	rg(): l(0), r(-1), i(-1){}

	friend bool operator<(const rg &a, const rg &b){
		return a.r > b.r; // Reversed because c++ priority queue is fucking weird
	}
};

struct p{
	int i, j;
};

int n, k, q, ba, bb, qptr = 0,
	sptable[B_MAX][MAX], sptable2[B_MAX][MAX],//1 = min, 2 = max
	counttree[MAX * B_MAX + 10], treeabs[MAX * B_MAX + 10];

priority_queue<rg> process;
p answers[MAX];

// Sparse Table

void build(){ // Builds sparse table `sptable` from array `arr`
	for (int i = 1; i < B_MAX; ++i) {
		int gap = 1 << (i - 1), maxv = n - (1 << i) + 1;

		for (int j = 1; j <= maxv; ++j) {
			sptable[i][j] = min(sptable[i - 1][j], sptable[i - 1][j + gap]);
			sptable2[i][j] = max(sptable2[i - 1][j], sptable2[i - 1][j + gap]);
		}
	}
}

int query(int a, int b){ // Querys the range from `a` to `b`
	// Find max bit
	int delta = b - a, maxbit = 1, // Max bit begins at 0 to account for `b - maxbit + 1` when `a == b`
			maxbitind = 0; // Row of the sparse table to use

	for (int i = B_MAX; i >= 0; --i) {
		int v = 1 << i;

		if(delta & v){
			maxbit = v;
			maxbitind = i;
			break;
		}
	}

	// Return Range
	return min(sptable[maxbitind][a],
			sptable[maxbitind][b - maxbit + 1]);
}

int query2(int a, int b){ // Querys the range from `a` to `b`
	// Find max bit
	int delta = b - a, maxbit = 1, // Max bit begins at 0 to account for `b - maxbit + 1` when `a == b`
			maxbitind = 0; // Row of the sparse table to use

	for (int i = B_MAX; i >= 0; --i) {
		int v = 1 << i;

		if(delta & v){
			maxbit = v;
			maxbitind = i;
			break;
		}
	}

	// Return Range
	return max(sptable2[maxbitind][a],
			sptable2[maxbitind][b - maxbit + 1]);
}

inline int qrange(int a, int b){
	return query2(a, b) - query(a, b);
}

// Segment Tree

//int cnt = 40;

int squerynml(int i, int bl, int br, int ql, int qr){
	if(ql > qr || ql < bl || qr > br){
		return 0;
	}

	if(bl == ql && br == qr){
		return counttree[i];
	}

	int mid = (bl + br) / 2;

//	printf("=i=%d bl=%d br=%d ql=%d qr=%d mid=%d\n", i, bl, br, ql, qr, mid);
//	assert(cnt--);

	return max(squerynml(i << 1, bl, mid, ql, min(qr, mid)),
			squerynml(i << 1 | 1, mid + 1, br, max(ql, mid + 1), qr));
}

int squery(int i, int bl, int br, int ql, int qr){
	if(ql > qr){
		return 0;
	}

	if(bl == br){
		return bl;
	}

	int mid = (bl + br) / 2;

	int lc = i << 1, rc = lc + 1,
			rq = squerynml(rc, mid + 1, br, max(ql, mid + 1), qr),
			lq = squerynml(lc, bl, mid, ql, min(qr, mid));

//	printf("i=%d bl=%d br=%d ql=%d qr=%d lc=%d rc=%d\n", i, bl, br, ql, qr, rq, lq);

	// Otherwise do a comparison based check
	if(rq > lq){ // Go to higher index only when higher
		return squery(rc, mid + 1, br, max(ql, mid + 1), qr);
	}
	else{ // Otherwise go to lower if equal or lower
		return squery(lc, bl, mid, ql, min(qr, mid));
	}
}

int squeryabs(int i, int bl, int br, int ql, int qr){
	if(ql > qr){
		return 0;
	}

	if(bl == ql && br == qr){
		return treeabs[i];
	}

	int mid = (bl + br) / 2;

	return max(squeryabs(i << 1, bl, mid, ql, min(qr, mid)),
			squeryabs(i << 1 | 1, mid + 1, br, max(ql, mid + 1), qr));
}

int update(int i, int bl, int br, int q, int v){
    if(q < bl || q > br){
		return counttree[i];
    }

	if(bl == q && br == q){
		return counttree[i] = v;
	}

	int mid = (bl + br) / 2;

	return counttree[i] = max(update(i << 1, bl, mid, q, v), update(i << 1 | 1, mid + 1, br, q, v));
}

int updateabs(int i, int bl, int br, int q, int v){
    if(q < bl || q > br){
		return treeabs[i];
    }

	if(bl == q && br == q){
		return treeabs[i] = v;
	}

	int mid = (bl + br) / 2;

	return treeabs[i] = max(updateabs(i << 1, bl, mid, q, v), updateabs(i << 1 | 1, mid + 1, br, q, v));
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	// Input

	cin >> n >> k;

	for (int i = 1; i <= n; ++i) {
		cin >> sptable[0][i];
		sptable2[0][i] = sptable[0][i];
	}

	// Sparse table

	build();

	// Queries

	cin >> q;

	for (int i = 0; i < q; ++i) {
		cin >> ba >> bb;
		process.emplace(ba, bb, i);
	}

	// Offline processing

	int fillout = 1; // Fillout -> Current index being filled

	for (int i = 1; i <= n; ++i) {
		// Filling in Segment Tree
		while(qrange(fillout, i) > k){
			update(1, 1, n, fillout, i - 1 - fillout);
			updateabs(1, 1, n, fillout, i - 1);

//			printf("update (back) fillout=%d i=%d\n", fillout, i - 1);

			fillout++;
		}

		update(1, 1, n, fillout, i - fillout);
		updateabs(1, 1, n, fillout, i);

//		printf("update fillout=%d i=%d\n", fillout, i);

		// Answering Queries
		while(process.top().r == i && !process.empty()){
			rg q = process.top();
			process.pop();

			int resultri = squery(1, 1, n, q.l, q.r), resultabs = squeryabs(1, 1, n, 1, q.l),
					resultr = squerynml(1, 1, n, resultri, resultri), // resultr = deltaresultr
					deltaresultabs = resultabs - q.l;

//			printf("i=%d, proc= %d,%d,%d\n", i, q.l, q.r, q.i);
//			printf("resultri=%d resultr=%d resultabs=%d\n", resultri, resultr, resultabs);

			if(resultr > deltaresultabs){
				answers[q.i] = {resultri, min(resultri + resultr, q.r)};
			}
			else{
				answers[q.i] = {q.l, min(resultabs, q.r)};
			}
		}
	}

	// Printing Output

	for (int i = 0; i < q; ++i) {
		printf("%d %d\n", answers[i].i, answers[i].j);
	}
}

/*
5 2
1 2 3 4 0
4
1 5
2 5
3 5
5 5

1 3
2 4
3 4
5 5

--

7 0
1 1 1 2 1 1 1
4
1 4
2 6
4 7
4 5

1 3
2 3
5 7
4 4
 */
