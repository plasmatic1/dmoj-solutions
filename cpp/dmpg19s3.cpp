//============================================================================
// Name        : dmpg18s3.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;
int n, amtLeft = -1, bufi;
string buf;

#define form unordered_map<int, ll>
inline void multiply(form &fm, int amt) {
	for (pair<int, ll> p : fm)
		fm[p.first] = (p.second * amt) % MOD;
}

inline void update(form &fm, form other) {
	for (pair<int, ll> p : other)
		fm[p.first] = (fm[p.first] + p.second) % MOD;
}

// Converts to number
inline int conv(string s) {
	if (s.length() > (size_t)1)
		return ((int)(s[0] - 'A') << 5) + ((int)(s[1] - 'a') + 1);
	return (int)(s[0] - 'A') << 5;
}

char ss[2], sx[3];
inline string unConv(int x) {
	char a = (x >> 5) + 'A', b = (x & 31) - 1 + 'a';
//	printf("%c %c\n", a, b);
	if ((x & 31) == 0) {
		ss[0] = a;
		return string(ss);
	}
	sx[0] = a, sx[1] = b;
	return string(sx);
}

form rec() {
	form curF;

	if (amtLeft == 0)
		return curF;

	while (buf != ")") {
		if (amtLeft <= 0) {
			break;
		}

		cin >> buf;
		int bufX = conv(buf);

		amtLeft--;
		if (buf == "(")
			update(curF, rec());
		else if (buf != ")") {
			cin >> bufi;
			curF[bufX] = (curF[bufX] + bufi) % MOD;
		}
	}

	if (buf == ")") {
		cin >> bufi;
		multiply(curF, bufi);
		buf = "@";
	}

	return curF;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n;

	amtLeft = n;

	vector<pair<string, ll>> ents;
	for (pair<int, ll> p : rec())
		ents.push_back(make_pair(unConv(p.first), p.second));
	sort(ents.begin(), ents.end());
	for (pair<string, ll> p : ents)
		printf("%s %lld\n", p.first.c_str(), p.second);
}