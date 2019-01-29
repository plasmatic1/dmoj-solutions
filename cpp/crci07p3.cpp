//============================================================================
// Name        : Kuhar.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
//#define DEBUG

using namespace std;

typedef long long ll;

struct pack{
	int p, s;
};

const int MAX = 100, MAXV = 100000;
int n, m, bps, bss, bpl, bsl,
	reqs[MAX], availab[MAX];
pack small[MAX], large[MAX];

int ceildiv(int a, int b){
	return (int)ceil(a/(double)b);
}

int getcost(int creq, int largec, int i){
	if(largec == 0){
		return ceildiv(creq, small[i].s) * small[i].p;
	}

	int smallc = ceildiv(creq - (largec * large[i].s), small[i].s);

	if(smallc < 0){
		return largec * large[i].p;
	}

#ifdef DEBUG
	printf("creq=%d, largec=%d, smallc=%d\n", creq, largec, smallc);
#endif

	return largec * large[i].p + smallc * small[i].p;
}

bool test(int servings){
	int cm = m;

	for (int i = 0; i < n; ++i) {
		int creq = reqs[i] * servings - availab[i], cost = INT_MAX, largec = ceildiv(creq, large[i].s);

		while(largec >= 0){
			cost = min(cost, getcost(creq, largec, i));
			largec--;
		}

#ifdef DEBUG
		printf("ingredient %d has cost %d\n", i, cost);
#endif

		cm -= cost;

		if(cm < 0){
			return false;
		}
	}

	return true;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	// Input

	cin >> n >> m;

	for (int i = 0; i < n; ++i) {
		cin >> reqs[i] >> availab[i] >> bss >> bps >> bsl >> bpl;
		small[i] = {bps, bss};
		large[i] = {bpl, bsl};
	}

	int l = 0, r = MAXV;

	while(l + 1 < r){
		int mid = (l + r) / 2, tv = test(mid);

#ifdef DEBUG
		printf("l=%d, r=%d, mid=%d, foudn val=%d\n", l, r, mid, tv);
#endif

		if(tv){
			l = mid;
		}
		else{
			r = mid;
		}
	}

	printf("%d\n", l);
}
