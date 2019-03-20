//============================================================================
// Name        : dmopc18c6p4.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct p{
	int i;
	ll v;

	bool operator<(const p &o) const{
		return v < o.v;
	}
};

const int MAX = 200001;
int n, pv, m, ba, bb, besti;
ll best = LLONG_MAX,
    diffp[MAX], diffm[MAX], guardp[MAX], guardm[MAX], tot[MAX];
p phys[MAX], mag[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> pv >> m;

	for (int i = 0; i < n; ++i) {
		cin >> ba >> bb;
		phys[i] = {i, ba};
		mag[i] = {i, bb};
	}

	sort(phys, phys + n);
	sort(mag, mag + n);

	for (int i = 0; i < pv; ++i) {
		cin >> ba;

		p tmp = {-1, ba};
		int idx = lower_bound(phys, phys + n, tmp) - phys;
		diffp[0] += ba;
		diffp[idx] -= ba;
		guardp[0]++;
		guardp[idx]--;
	}

	for (int i = 0; i < m; ++i) {
		cin >> ba;

		p tmp = {-1, ba};
		int idx = lower_bound(mag, mag + n, tmp) - mag;
		diffm[0] += ba;
		diffm[idx] -= ba;
		guardm[0]++;
		guardm[idx]--;
	}

	for (int i = 1; i < n; ++i) {
		diffp[i] += diffp[i - 1];
		diffm[i] += diffm[i - 1];
		guardp[i] += guardp[i - 1];
		guardm[i] += guardm[i - 1];
	}

	for (int i = 0; i < n; ++i) {
		int target = phys[i].i;
		tot[target] += diffp[i] - (phys[i].v * guardp[i]);

		target = mag[i].i;
		tot[target] += diffm[i] - (mag[i].v * guardm[i]);
	}

	for (int i = 0; i < n; ++i) {
		if(tot[i] < best){
			best = tot[i];
			besti = i;
		}
	}

	printf("%d\n", besti + 1);
}