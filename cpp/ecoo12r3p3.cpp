//============================================================================
// Name        : ecoo12r3p3.cpp
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

typedef pair<int, int> p;
#define ans first
#define end second

const int MAX = 1000000;
int n;
string s;

// Shorthand for returning pair with eval(x)
#define WITH(expr) make_pair(expr, ret2.end + 1);
p eval(int start){
	if(s[start] >= '0' && s[start] <= '9')
		return make_pair((int)(s[start] - '0'), start);
	else
		start++;

	char op = s[start];
	p ret = eval(start + 2), ret2 = eval(ret.end + 2);

	switch(op){
	case '+': return WITH(ret.ans + ret2.ans);
	case '-': return WITH(ret.ans - ret2.ans);
	case '*': return WITH(ret.ans * ret2.ans);
	case 'q': return WITH(ret.ans / ret2.ans);
	default: return WITH(ret.ans % ret2.ans); // 'r'
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	for (int i = 0; i < 10; ++i) {
		getline(cin, s);
		n = s.length();

		printf("%d\n", eval(0).ans);
	}
}