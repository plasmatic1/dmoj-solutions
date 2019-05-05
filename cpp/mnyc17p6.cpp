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

const int MAX = 100001, SQ = 1000;
const bitset<SQ> ZERO(0ULL);
int n, q, bt, ba, bb,
	arr[MAX];
bitset<SQ> tree[MAX << 2];
unordered_map<int, int> idxOf, cnt;
queue<int> ava;

inline int getIdx(int v) {
	auto ptr = idxOf.find(v);
	if (ptr == idxOf.end()) {
		int idx = ava.front(); ava.pop();
		return idxOf[v] = idx;
	}
	return ptr->second;
}

bitset<SQ> query(int i, int l, int r, int ql, int qr) {
	if (l >= ql && r <= qr) return tree[i];
	if (l > qr || r < ql) return ZERO;

	int mid = (l + r) >> 1;
	return query(i << 1, l, mid, ql, qr) | query(i << 1 | 1, mid + 1, r, ql, qr);
}

bitset<SQ>& update(int i, int l, int r, int q, int id) {
	if (l == q && r == q) return tree[i].flip(id);
	if (l > q || r < q) return tree[i];

	int mid = (l + r) >> 1;
	return tree[i] = update(i << 1, l, mid, q, id) | update(i << 1 | 1, mid + 1, r, q, id);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	scan(n, q);

	for (int i = 0; i < SQ; i++)
		ava.push(i);

	for (int i = 1; i <= n; i++) {
		scan(arr[i]);
		update(1, 1, n, i, getIdx(arr[i]));
		cnt[arr[i]]++;
	}

	for (int i = 0; i < q; ++i) {
		scan(bt, ba, bb);

		if (bt == 1) {
			// Remove old
			cnt[arr[ba]]--;
			auto ptr = cnt.find(arr[ba]);
			update(1, 1, n, ba, getIdx(arr[ba]));

			if (ptr->second == 0) {
				ava.push(idxOf[arr[ba]]);
				cnt.erase(ptr);
				idxOf.erase(arr[ba]);
			}

			// Add new
			arr[ba] = bb;
			cnt[arr[ba]]++;
			update(1, 1, n, ba, getIdx(arr[ba]));
		}
		else // bt == 2
			printf("%d\n", (int)query(1, 1, n, ba, bb).count());
	}
}