//============================================================================
// Name        : coci17c1p5.cpp
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

struct nd { int i, v; };
struct qu {
	int i; char t; int x, a;

	bool operator<(const qu &o) const {
		if (x == o.x)
			return i < o.i;
		return x < o.x;
	}
};

const int MAX = 200001, INF = 0x3f3f3f3f;
int n, q, bx, ba,
	ans[MAX], tree[MAX << 2];
char typeOf[MAX];
qu qus[MAX];

int update(int i, int l, int r, int q, int v) {
	if (l == q && r == q) return tree[i] = v;
	if (l > q || r < q) return tree[i];

	int mid = (l + r) >> 1;
	return tree[i] = min(update(i << 1, l, mid, q, v), update(i << 1 | 1, mid + 1, r, q, v));
}

int query(int i, int l, int r, int ql, int qr) {
	if (l >= ql && r <= qr) return tree[i];
	if (l > qr || r < ql) return INF;

	int mid = (l + r) >> 1;
	return min(query(i << 1, l, mid, ql, qr), query(i << 1 | 1, mid + 1, r, ql, qr));
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	scan(n, q);
	memset(tree, 0x3f, sizeof tree);

	for (int i = 0; i < q; ++i) {
		scan(typeOf[i], bx, ba);
		qus[i] = {i, typeOf[i], bx, ba};
	}
	sort(qus, qus + q);

	for (int i = 0; i < q; ++i) {
		if (qus[i].t == 'M')
			update(1, 1, n, qus[i].a, qus[i].i);
		else { // Query type d
			int l = qus[i].a - 1, r = n + 1;
			while (l + 1 < r) {
				int mid = (l + r) >> 1;

//				int tans = query(1, 1, n, qus[i].a, mid); debug(l, r, mid , tans);

				if (query(1, 1, n, qus[i].a, mid) < qus[i].i)
					r = mid;
				else
					l = mid;
			}

//			debug(i, qus[i].i, l, r);
			ans[qus[i].i] = r;
		}
	}

	for (int i = 0; i < q; ++i)
		if (typeOf[i] == 'D')
			cout << (ans[i] > n ? -1 : ans[i]) << "\n";
}