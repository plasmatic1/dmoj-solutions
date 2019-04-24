//============================================================================
// Name        : coci06c5p6.cpp
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

const int MAX = 200001, P = 31, MOD = 1000000007;
int n;
string s;
ll pows[MAX], invPows[MAX], hashes[MAX];

#define CHR(x) (int)((x) - 'a')

// Fast power
inline ll modPow(ll x, ll y) {
	ll ans = 1;
	for (ll bit = 1, cpow = x; bit <= y; bit <<= 1, cpow = (cpow * cpow) % MOD)
		if (y & bit)
			ans = (ans * cpow) % MOD;
	return ans;
}

// hashes substr [l, r]
inline ll hashSubstr(int l, int r) {
	return (hashes[r] - hashes[l - 1] * pows[r - l + 1]) * invPows[r - l];
}

inline bool equal(int fst, int snd, int sz) {
	for (int i = sz - 1; i >= 0; i--)
		if (s[fst + i] != s[snd + i])
			return false;
	return true;
}

inline bool sim(int sz) {
	if (sz == 0)
		return true;

	int end = n - sz + 1;
	unordered_set<ll> hashVals;
	for (int i = 1; i <= end; i++) {
		hashVals.insert(hashSubstr(i, i + sz - 1));
		if (hashVals.size() < (size_t)i)
			return true;
	}

	return false;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	scan(n, s);
	s = " " + s;

	pows[0] = invPows[0] = 1;
	for (int i = 1; i <= n; i++) {
		hashes[i] = hashes[i - 1] * P + CHR(s[i]); //, debug(i, hashes[i]);
		pows[i] = pows[i - 1] * P;
		invPows[i] = modPow(pows[i], MOD - 2);
	}

	int l = -1, r = n;
	while (l + 1 < r) {
		int mid = (l + r) >> 1;

		if (sim(mid))
			l = mid;
		else
			r = mid;
	}

	printf("%d\n", l);
}