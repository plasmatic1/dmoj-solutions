//============================================================================
// Name        : TheZagonetkaMachine.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

int n, buf;
string s, r;
ll tot = 0;

inline bool issim(string &a, string &pfx){
	int pl = pfx.length();
	for (int i = 0; i < pl; ++i) {
		if(a[i] != pfx[i]){
			return false;
		}
	}
	return true;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> s;

	r = s;
	reverse(r.begin(), r.end());

	for (int i = 0; i < n; ++i) {
		for (int j = i; j < n; ++j) {
			int l = j - i + 1;
			string sub = s.substr(i, l), rs = sub;
			reverse(rs.begin(), rs.end());
//			printf("%s\n", sub.c_str());

			if(issim(s, sub) && issim(r, rs)){
				tot++;
//				printf("substr i=%d j=%d '%s' works\n", i, j, sub.c_str());
			}
		}
	}

	printf("%lld\n", tot);
}
