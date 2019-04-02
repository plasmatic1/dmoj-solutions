//============================================================================
// Name        : quiz2.cpp
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

const int MAX = 1000000;
int n, buf;

int rec(string prev, int cur, int last){
	if(cur == n){
		printf("%d=%s\n", n, prev.substr(0, prev.length() - 1).c_str());
		return 1;
	}

//	debug(prev, cur);

	int tot = 0;
	for(int i = last; i <= n - cur; i++){
		if(i == n) continue;
		tot += rec(prev + to_string(i) + "+", cur + i, i);
	}

	return tot;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	scan(n);

	printf("total=%d\n", rec("", 0, 1));
}
