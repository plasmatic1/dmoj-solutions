//============================================================================
// Name        : acc1p3.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct pi{
	ll a, d; // a = reward, d = deprec

	pi(ll a0, ll d0) : a(a0), d(d0){}
	pi() : a(-1), d(-1){}

	friend bool operator<(const pi &a, const pi &b){
		return a.a < b.a;
	}
};

const int MAX = 100000;
const ll MOD = 998244353;
ll t, ba, bb, mv = LLONG_MIN, tot = 0;
int n;
pi poutines[MAX];

ll fastpow(ll x, ll y){
	ll curr = 1, curr_pow = x, curr_mask = 1;

	while(curr_mask <= y){
		if(y & curr_mask){
			curr = (curr * curr_pow) % MOD;
		}

		curr_pow = (curr_pow * curr_pow) % MOD;
		curr_mask <<= 1;
	}

	return curr;
}

#define INVERSE(x) (fastpow((x), (MOD - 2)))

#define M_ADD(x, y) ((((x) % (MOD)) + ((y) % (MOD))) % (MOD))
#define M_SUB(x, y) ((((x) % (MOD)) - ((y) % (MOD))) % (MOD))
#define M_MUL(x, y) ((((x) % (MOD)) * ((y) % (MOD))) % (MOD))
#define M_DIV(x, y) ((((x) % (MOD)) * (INVERSE(y))) % (MOD))

ll sim(ll minv){
	ll total = 0;

	for(int i = 0; i < n; i++){
		if(poutines[i].a < minv){
			continue;
		}

		ll required = (poutines[i].a - minv) / poutines[i].d + 1;

		if(total + required < 0){ // Integer overflow
			return -1;
		}

		total += required;
	}

	return total;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> t;

	for (int i = 0; i < n; ++i) {
		cin >> ba >> bb;
		mv = max(mv, ba);

		poutines[i] = pi(ba, bb);
	}

	// Bsearch for min order value
	ll l = 0, r = mv + 1;

	while(l + 1 < r){
		ll mid = (l + r) / 2, simv = sim(mid);

		if(simv >= t || simv == -1){ // Cannot reach this low of a min value
			l = mid;
		}
		else{
			r = mid;
		}
	}

	ll ordtot = 0;

	// Get Total Count
	for(int i = 0; i < n; i++){
		if(poutines[i].a < l){
			continue;
		}

		ll required = (poutines[i].a - l) / poutines[i].d + 1;
		required = min(required, t - ordtot);

		ll cmin = poutines[i].a - ((required - 1) * poutines[i].d);
		ll nv = poutines[i].a - cmin;

		if(required <= 0){
			continue;
		}

		tot += M_DIV(M_MUL(nv, M_ADD(nv, poutines[i].d)), M_MUL(poutines[i].d, 2));
		tot %= MOD;
		tot += M_MUL(cmin, required);
		tot %= MOD;

		ordtot += required;
	}

	printf("%lld\n", tot);
}
