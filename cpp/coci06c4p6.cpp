//============================================================================
// Name        : coci06c4p6.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
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
template<typename F, typename... R> void debug_(F &f, R&... r){while(dnms_[di_] != ',')cout<<dnms_[di_++];di_++;cout<<": "<<f<<",";debug_(r...);}
#define debug(...) dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__)

struct qu {
	char t;
	int a, b;
};

const int MAX = 200001;
int q, rankSz, ba, bb, curStud = 1,
	A[MAX], B[MAX], tree[MAX << 2];
qu qus[MAX];
vector<int> ranks_;
char bt;
set<pair<int, int>> vals[MAX]; // first -> understanding (A-val), second -> student ID
// first check by b, then by c

inline int rankOf(int x) {
	return lower_bound(ranks_.begin(), ranks_.end(), x) - ranks_.begin() + 1;
}

int query (int i, int l, int r, int ql, int qr) {
	if (l > qr || r < ql || l > r) return INT_MIN;
	if (l >= ql && r <= qr) return tree[i];

	int mid = (l + r) >> 1;
	return max(query(i << 1, l, mid, ql, qr), query(i << 1 | 1, mid + 1, r, ql, qr));
}

int update (int i, int l, int r, int q, int v) {
	if (l == q && r == q) return tree[i] = v;
	if (l > q || r < q) return tree[i];

	int mid = (l + r) >> 1;
	return tree[i] = max(update(i << 1, l, mid, q, v), update(i << 1 | 1, mid + 1, r, q, v));
}

#define SET_MAX(set_) (--set_.end()) // std::set max value

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	scan(q);

	for (int i = 0; i < q; i++) {
		scan(qus[i].t, qus[i].a);

		if (qus[i].t == 'D') {
			scan(qus[i].b);
			ranks_.push_back(qus[i].b);
		}
	}
	sort(ranks_.begin(), ranks_.end());
	ranks_.resize(unique(ranks_.begin(), ranks_.end()) - ranks_.begin());
	rankSz = ranks_.size();

	for (int i = 0; i < q; i++) {
		if (qus[i].t == 'D') {
			int rankB = rankOf(qus[i].b);
			vals[rankB].insert(make_pair(qus[i].a, curStud));
			update(1, 1, rankSz, rankB, SET_MAX(vals[rankB])->first);

			A[curStud] = qus[i].a;
			B[curStud] = qus[i].b;
			curStud++;
		}
		else {
			int rankB = rankOf(B[qus[i].a]), a = A[qus[i].a];
//			debug(rankB, a);

			auto ptr = vals[rankB].upper_bound(make_pair(a, qus[i].a)); // B value is same but A is greater
			if (ptr != vals[rankB].end()) {
				printf("%d\n", ptr->second);
				continue;
			}

			if (query(1, 1, rankSz, rankB + 1, rankSz) < a) // Cannot find one where B value is greater
				printf("NE\n");
			else { // B value greater, A greater or equal
				int l = rankB, r = rankSz;
				while (l + 1 < r) {
					int mid = (l + r) >> 1;
//					debug(l, r, mid);

					if (query(1, 1, rankSz, rankB + 1, mid) >= a)
						r = mid;
					else
						l = mid;
				}

//				printf("l=%d r=%d\n", l, r);
				printf("%d\n", vals[r].lower_bound(make_pair(a, -1))->second);
			}
		}
	}
}