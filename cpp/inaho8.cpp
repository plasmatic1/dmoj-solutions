//============================================================================
// Name        : Inaho8.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;
const int MAX = 100001, MLOG = 18, INF = 0x3f3f3f3f;

struct cel{
	int sum, min, max, gcd, andv, orv, xorv, morek, lessk, minka, minkb;
	ll prod;

	cel() : sum(0), min(INF), max(-INF), gcd(0), andv(INT_MAX), orv(0), xorv(0), morek(0), lessk(0),
			minka(INF), minkb(-INF), prod(1){}
};

int n, q, k, ba, bb, bc, rt = 1,
	val[MAX], levels[MAX], pars[MLOG][MAX];
cel cres,
	table[MLOG][MAX];
vector<int> matrix[MAX];

int gcd(int a, int b){
	if(b == 0){
		return a;
	}
	return gcd(b, a % b);
}

inline void merge(cel &a, cel &b, cel &end){
	end.sum = a.sum + b.sum;
	end.prod = (a.prod * b.prod) % MOD;
	end.min = min(a.min, b.min);
	end.max = max(a.max, b.max);
	end.gcd = gcd(a.gcd, b.gcd);
	end.andv = a.andv & b.andv;
	end.orv = a.orv | b.orv;
	end.xorv = a.xorv ^ b.xorv;
	end.morek = a.morek + b.morek;
	end.lessk = a.lessk + b.lessk;
	end.minka = min(a.minka, b.minka);
	end.minkb = max(a.minkb, b.minkb);
}

void dfs(int cur, int par, int level){
	table[0][cur].sum = val[cur];
	table[0][cur].prod = val[cur];
	table[0][cur].min = val[cur];
	table[0][cur].max = val[cur];
	table[0][cur].gcd = val[cur];
	table[0][cur].andv = val[cur];
	table[0][cur].orv = val[cur];
	table[0][cur].xorv = val[cur];
	table[0][cur].morek = val[cur] > k;
	table[0][cur].lessk = val[cur] < k;
	table[0][cur].minka = val[cur] > k ? val[cur] : INF;
	table[0][cur].minkb = val[cur] < k ? val[cur] : -INF;

	pars[0][cur] = par;
	levels[cur] = level;

	for(int adj : matrix[cur]){
		if(adj != par)
			dfs(adj, cur, level + 1);
	}
}

inline void buildtable(){
	for(int i = 1; i < MLOG; i++){
		for (int j = 1; j <= n; ++j) {
			int par = pars[i - 1][j];

			if(par != -1){
				merge(table[i - 1][j], table[i - 1][par], table[i][j]);
				pars[i][j] = pars[i - 1][par];
			}
		}
	}
}

inline int query(int a, int b, cel &res){
	res = cel();

	if(a == b) return a;
	if(levels[a] > levels[b]) swap(a, b);

	int delta = levels[b] - levels[a];
	for(int i = MLOG - 1; i >= 0; i--){
		if(delta & (1 << i)){
			merge(res, table[i][b], res);
			b = pars[i][b];
		}
	}

	if(a == b) return a;

	cel resb;

	for(int i = MLOG - 1; i >= 0; i--){
		if(pars[i][a] != pars[i][b]){
			merge(res, table[i][a], res);
			merge(resb, table[i][b], resb);
			a = pars[i][a];
			b = pars[i][b];
		}
	}

	merge(res, table[0][a], res);
	merge(resb, table[0][b], resb);
	merge(res, resb, res);

	return pars[0][a];
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> q >> k;

	for (int i = 1; i <= n; ++i) {
		cin >> val[i];
	}

	for (int i = 1; i < n; ++i) {
		cin >> ba >> bb;

		matrix[ba].push_back(bb);
		matrix[bb].push_back(ba);
	}

	// Building sparse table

	memset(pars, -1, sizeof(pars));
	dfs(1, -1, 0);
	buildtable();

	// Queries

	for (int i = 0; i < q; ++i) {
		cin >> ba >> bb;

		if(ba == 1){
			rt = bb;
			continue;
		}

		cin >> bc;

		if(ba == 2){
			printf("%d\n", rt);
			continue;
		}

		int lca = query(bb, bc, cres);
		merge(cres, table[0][lca], cres);

		if(ba == 3) printf("%d\n", cres.sum);
		else if(ba == 4) printf("%lld\n", cres.prod);
		else if(ba == 5) printf("%d\n", cres.min);
		else if(ba == 6) printf("%d\n", cres.max);
		else if(ba == 7) printf("%d\n", cres.gcd);
		else if(ba == 8) printf("%d\n", cres.andv);
		else if(ba == 9) printf("%d\n", cres.orv);
		else if(ba == 10) printf("%d\n", cres.xorv);
		else if(ba == 11) printf("%d\n", cres.morek);
		else if(ba == 12) printf("%d\n", cres.lessk);
		else if(ba == 13) printf("%d\n", cres.minka != INF ? cres.minka : k);
		else printf("%d\n", cres.minkb != -INF ? cres.minkb : k);
	}
}
