#include <bits/stdc++.h>

// the irony is real >.<
// :blobsad: :blobcry: :blobsob:
// what an interesting time >.<
// what a day today >.<

using namespace std;

typedef long long ll;

struct qu{
	int i, c, l;

	bool operator<(const qu &o){
		return l < o.l;
	}
};

const int MAX = 2001, MV = 100001, MX = 10001;
int n, v, ba, bb, qptr = 0,
	coin[MAX], dp[MX], ans[MV];
qu queries[MV];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> v;

	for(int i = 1; i <= n; i++)
		cin >> coin[i];

	for (int i = 0; i < v; ++i) {
		cin >> ba >> bb;
		queries[i] = {i, ba, bb};
	}

	sort(queries, queries + v);

	memset(dp, 0x3f, sizeof dp);
	dp[0] = 0;
	for(int i = 1; i <= n; i++){
		for(int j = coin[i]; j < MX; j++)
			dp[j] = min(dp[j], dp[j - coin[i]] + 1);

		while(qptr < v && queries[qptr].l == i){
			int cans = dp[queries[qptr].c];
			ans[queries[qptr].i] = cans == 0x3f3f3f3f ? -1 : cans;
			qptr++;
		}
	}

	for(int i = 0; i < v; i++)
		printf("%d\n", ans[i]);
}