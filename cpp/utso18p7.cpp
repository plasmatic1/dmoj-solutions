//============================================================================
// Name        : utso18p7.cpp
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
const ll MOD = 1000000007;
int n, q, bs, bv, bt,
	sz[MAX], mul[MAX], pars[MAX], chNum[MAX];
bool blocked[MAX];
vector<int> matrix[MAX];
vector<ll> dis[MAX], chTot[MAX];
ll tot[MAX];

ll modPow(ll x, ll y) {
	ll ans = 1;
	for (ll bit = 1, cpow = x; bit <= y; bit <<= 1, cpow = (cpow * cpow) % MOD)
		if (y & bit)
			ans = (ans * cpow) % MOD;
	return ans;
}

inline ll divMod(ll x, ll y) { return (x * modPow(y, MOD - 2)) % MOD; }

int gsz(int cur, int par) {
	sz[cur] = 1;
	for (int adj : matrix[cur])
		if ((adj ^ par) && !blocked[adj])
			sz[cur] += gsz(adj, cur);
	return sz[cur];
}

int gcentroid(int cur, int par, int half) {
	for (int adj : matrix[cur])
		if ((adj ^ par) && !blocked[adj] && sz[adj] > half)
			return gcentroid(adj, cur, half);
	return cur;
}

void dfs(int cur, int par, ll cdis) {
	dis[cur].push_back(cdis);
	for (int adj : matrix[cur])
		if ((adj ^ par) && !blocked[adj])
			dfs(adj, cur, (cdis * mul[adj]) % MOD);
}

int decomp(int cur, int par) {
	gsz(cur, par);
	if (sz[cur] == 1) {
		dis[cur].push_back(mul[cur]);
		return cur;
	}

	int centroid = gcentroid(cur, par, sz[cur] >> 1);
	dfs(centroid, -1, mul[centroid]);

	blocked[centroid] = true;
	int ctr = 0;
	for (int adj : matrix[centroid]) {
		if (!blocked[adj]) {
			int adjCentroid = decomp(adj, centroid);
			pars[adjCentroid] = centroid;
			chNum[adjCentroid] = ctr++;
		}
	}
	chTot[centroid].resize(ctr);

	return centroid;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	scan(n, q);

	for (int i = 1; i <= n; i++)
		scan(mul[i]);

	for (int i = 1; i < n; ++i) {
		scan(bs, bv);
		matrix[bs].push_back(bv);
		matrix[bv].push_back(bs);
	}

	pars[decomp(1, -1)] = -1;

	for (int i = 0; i < q; ++i) {
		scan(bt, bs);

		if (bt == 1) {
			scan(bv);

			int cur = bs, lv = dis[bs].size() - 1, lastChNum = -1;
			ll lastAdd = 0;
			for (; lv >= 0; cur = pars[cur], lv--) {
				lastAdd = bv * divMod(dis[bs][lv], mul[cur]) % MOD;
				tot[cur] = (tot[cur] + lastAdd) % MOD;
				if (lastChNum != -1) {
					ll &val = chTot[cur][lastChNum];
					val = (val + lastAdd) % MOD;
				}

				lastChNum = chNum[cur];
			}
		}
		else { // bt == 2
			ll ctot = 0;
			int cur = bs, lv = dis[bs].size() - 1, lastChNum = -1;
			for (; lv >= 0; cur = pars[cur], lv--) {
				ll ans = tot[cur];
				if (lastChNum != -1)
					ans -= chTot[cur][lastChNum];
				ctot += (ans * dis[bs][lv]) % MOD;

				lastChNum = chNum[cur];
			}

			ctot %= MOD;
			if (ctot < 0)
				ctot += MOD;

			printf("%lld\n", divMod(ctot, mul[bs]));
		}
	}
}