//============================================================================
// Name        : coci06c3p1.cpp
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

const int MAX = 9, TGSUM = 100, TGCNT = 7;
int arr[MAX];
deque<int> deq;
bool done = false;

void rec(int idx, int sum, int cnt){
	if(idx == MAX){
		if(sum == TGSUM && cnt == TGCNT && !done){
			for(int x : deq)
				printf("%d\n", x);
			done = true;
		}

		return;
	}

	deq.push_back(arr[idx]);
	rec(idx + 1, sum + arr[idx], cnt + 1);
	deq.pop_back();
	rec(idx + 1, sum, cnt);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	for (int i = 0; i < MAX; i++)
		scan(arr[i]);

	rec(0, 0, 0);
}