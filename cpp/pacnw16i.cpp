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

struct p{
	int x, v;

	bool operator<(const p &o) const {
		return x < o.x;
	}
};

const int MAX = 1001;
int n, k;
ll tot = 0,
	dp[MAX];
p houses[MAX];

// Run from [left, right)
inline void run(int left, int right) {
	set<p> hs;
	for (int i = left; i < right; i++) {
		int &cnt = houses[i].v, divc = cnt / k;
		tot += (ll)(houses[i].x << 1) * divc;
		cnt %= k;

		if (cnt > 0)
			hs.insert(houses[i]);
	}
	
	while(!hs.empty()) {
		// for (p x : hs) {
		// 	printf("(x=%d v=%d), ", x.x, x.v);
		// }printf("\n");

		vector<p> toRemove, toInsert;
		ll cTot = 0;
		for (auto it = hs.rbegin(); it != hs.rend(); it++) {
			if (cTot + it->v <= k) {
				toRemove.push_back(*it);
				cTot += it->v;
			}
			else {
				p px = *it;
				px.v -= k - cTot;

				toRemove.push_back(*it);
				toInsert.push_back(px);

				break;
			}
		}

		tot += hs.rbegin()->x << 1;
		for (p x : toRemove)
			hs.erase(x); //, printf("remove x=%d v=%d\n", x.x, x.v);
		for (p x : toInsert)
			hs.insert(x);
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	scan(n, k);

	for (int i = 0; i < n; i++)
		scan(houses[i].x, houses[i].v);
	sort(houses, houses + n);

	int idx = -1;
	for (int i = 0; i < n; i++) {
		if (houses[i].x >= 0) {	
			idx = i;
			break;
		}
	}

	if(idx == -1)
		idx = n;
	else
		run(idx, n);
	
	for (int i = 0; i < idx; i++)
		houses[i].x *= -1;
	reverse(houses, houses + idx);
	run(0, idx);

	printf("%lld\n", tot);

    return 0;
}