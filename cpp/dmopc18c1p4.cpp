//============================================================================
// Name        : P4Sorting.cpp
// Author      : Daxi the Taxi
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

	p(int i0, ll v0) : i(i0), v(v0){}
	p() : i(-1), v(-1){}

	friend bool operator<(const p &a, const p &b){
		return a.v < b.v;
	}
};

const int MAX = 200001;
int n, x, bl = 0, br = 0,
		ans[MAX];
ll k, m, best = -1, pfx[MAX];
p cnts[MAX];

#ifndef ONLINE_JUDGE
#define dprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define dprintf(...) ;
#endif

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> m >> k >> x;

	for (int i = 0; i < n; ++i) {
		cin >> cnts[i].v;
		cnts[i].i = i;
	}

	sort(cnts, cnts + n);

	for (int i = 0; i < n; ++i) {
		pfx[i] = cnts[i].v;
	}

	for (int i = 1; i < n; ++i) {
		pfx[i] += pfx[i - 1];
	}

	// Range Calculations

	if(x == 1){ // Edge Case
		if(k <= cnts[n - 1].v){
			int counter = 1;

			ans[cnts[n - 1].i] = counter++;

			for (int i = 0; i < n - 1; ++i) {
				ans[cnts[i].i] = counter++;
			}

			for (int i = 0; i < n; ++i) {
				printf("%d ", ans[i]);
			}
			printf("\n");
		}
		else{
			printf("-1\n");
		}

		return 0;
	}

	int x0 = x - 2;
	for (int i = 0; i < n - x0; ++i) {
		ll csum = pfx[i + x0] - (i > 0 ? pfx[i - 1] : 0);

		if(csum > best && csum < k){
			best = csum;
			bl = i;
			br = i + x0;
		}
	}

	// Get best after range is determined

	int besti = -1;

	for (int i = n - 1; i >= 0; --i) {
		if(i < bl || i > br){
			besti = i;
			break;
		}
	}

	dprintf("bl=%d br=%d besti=%d\n", bl, br, besti);

	if(best == -1 || best + cnts[besti].v < k){
		printf("-1\n");
		return 0;
	}

	// Print

	int counter = 1;
	for (int i = bl; i <= br; ++i) {
		ans[cnts[i].i] = counter++;;
	}

	ans[cnts[besti].i] = counter++;

	for (int i = 0; i < n; ++i) {
		if((i < bl || i > br) && i != besti){
			ans[cnts[i].i] = counter++;
		}
	}

	for (int i = 0; i < n; ++i) {
		printf("%d ", ans[i]);
	}
	printf("\n");
}
