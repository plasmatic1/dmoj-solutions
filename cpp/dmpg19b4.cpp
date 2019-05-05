//============================================================================
// Name        : dmpg19b4.cpp
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
const string ROWS[3][27] = {
		{"o.", "o.", "oo", "oo", "o.", "oo", "oo", "o.", ".o", ".o", "o.", "o.", "oo", "oo", "o.", "oo", "oo", "o.", ".o", ".o", "o.", "o.", ".o", "oo", "oo", "o."},
		{"..", "o.", "..", ".o", ".o", "o.", "oo", "oo", "o.", "oo", "..", "o.", "..", ".o", ".o", "o.", "oo", "oo", "o.", "oo", "..", "o.", "oo", "..", ".o", ".o"},
		{"..", "..", "..", "..", "..", "..", "..", "..", "..", "..", "o.", "o.", "o.", "o.", "o.", "o.", "o.", "o.", "o.", "o.", "oo", "oo", ".o", "oo", "oo", "oo"}
};
int n;
string s;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	getline(cin, s);
	n = s.length();

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < n; j++) {
			if (s[j] == ' ')
				printf("..");
			else
				printf("%s", ROWS[i][(int)(s[j] - 'A')].c_str());
		}
		printf("\n");
	}

	return 0;
}
