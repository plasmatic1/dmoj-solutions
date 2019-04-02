//============================================================================
// Name        : quiz5.cpp
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

const int MAX = 1e5;
int n, a[MAX];
bool cmp2(const int &a, const int &b){
	int aa=a%10,bb=b%10;
	if(aa==bb)return a>b;
    return aa< bb;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	scan(n);
	for(int i=0;i<n;i++)
	    scan(a[i]);
	sort(a,a+n,cmp2);
	for(int i= 0;i<n;i++)
	    cout<<a[i]<<" ";
	cout<<endl;
}