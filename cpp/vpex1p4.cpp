#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

struct Ed {
	int v; ll w;
};

const int LG = 18, MN = 1e5 + 1;
int N, Q, 
	tb[LG][MN], lv[MN];
ll dis[MN];
vector<Ed> g[MN];
void dfsLca(int c, int p, int clv, ll cdis) {
	lv[c] = clv;
	dis[c] = cdis;
	tb[0][c] = p;
	for (auto to : g[c])
		if (to.v ^ p) 
			dfsLca(to.v, c, clv + 1, cdis + to.w);
}
void initSp() {
	memset(tb, -1, sizeof tb);
	dfsLca(1, -1, 0, 0);
	for (int i = 1; i < LG; i++) {
		for (int j = 1; j <= N; j++) {
			int pp = tb[i - 1][j];
			tb[i][j] = pp == -1 ? -1 : tb[i - 1][pp];
		}
	}
}
int lca(int a, int b) {
	if (a == b) return a;
	if (lv[a] > lv[b]) swap(a, b);
	int delta = lv[b] - lv[a];
	for (int i = 0; i < LG; i++)
		if ((delta >> i) & 1)
			b = tb[i][b];
	if (a == b) return a;
	for (int i = LG - 1; i >= 0; i--) {
		if (tb[i][a] != tb[i][b]) {
			a = tb[i][a];
			b = tb[i][b];
		}
	}
	return tb[0][a];
}
ll qdis(int a, int b) {
	return dis[a] + dis[b] - 2 * dis[lca(a, b)];
}

const int MQ = 1e6 + 1;
ll dp[MQ][2];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> Q;
	for (int i = 1; i < N; i++) {
		int a, b, w;
		cin >> a >> b >> w;
		g[a].push_back({b, w});
		g[b].push_back({a, w});
	}
	initSp();
	int prea = 1, preb = 1;
	for (int i = 1; i <= Q; i++) {
		int a[2];
		cin >> a[0] >> a[1];

		ll bdis = qdis(a[0], a[1]);
		for (int j = 0; j < 2; j++) {
			dp[i][j] = min(dp[i - 1][0] + qdis(prea, a[j ^ 1]) + bdis, dp[i - 1][1] + qdis(preb, a[j ^ 1]) + bdis);
		}

		// printf("i=%d a=%d b=%d dpa=%lld dpb=%lld\n", i, a[0], a[1], dp[i][0], dp[i][1]);
		// printf("bdis=%lld\n", bdis);

		prea = a[0]; preb = a[1];
	}

	ll ans = min(dp[Q][0], dp[Q][1]);
	cout << ans << endl;

	return 0;
}