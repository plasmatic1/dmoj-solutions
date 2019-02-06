//============================================================================
// Name        : partial.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 100001;
int n, curr = 0, nextt = 1;
ll t;
string bs;
bool tape[2][MAX];

inline void printtape(){
	for (int i = 0; i < n; ++i)
		printf("%d", tape[curr][i]);
	printf("\n");
}

inline void setb(string &s){
	for(int i = 0; i < n; i++) tape[curr][i] = s[i] == '1';
}

inline ll pmod(ll i, ll m){
	if(i >= 0) return i % m;
	return m - (-i % m);
}

inline void runfor(ll k){
	nextt = !curr;

	for(int i = 0; i < n; i++){
		ll l = pmod((ll)i - k, n) % n, r = ((ll)i + k) % n;
		tape[nextt][i] = tape[curr][l] ^ tape[curr][r];
	}

	curr = nextt;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> t >> bs;

	setb(bs);

	for(int i = 55; i >= 0; i--)
		if((t >> i) & 1) runfor(1LL << i);

	printtape();
}