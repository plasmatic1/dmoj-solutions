//============================================================================
// Name        : ToweringTowers.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
//#define DEBUG

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

int n, buf, last = -1;
deque<p> deq;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;
	deq.push_back(p(0, INT_MAX));

	for (int i = 0; i < n; ++i) {
		cin >> buf;

		while(!deq.empty() && buf >= deq.back().second){ //>=
			deq.pop_back();
		}

#ifdef DEBUG
		printf("deq: [");
		for(p pp : deq){
			printf("(%d, %d), ", pp.first, pp.second);
		}
		printf("]\n");
#endif

		printf("%d ", i - deq.back().first);

		deq.push_back(p(i, buf));
	}
}

//while(!deq.empty() && buf < deq.back().second){
//			last = deq.back().first;
//			deq.pop_back();
//		}
//
//		if(last != -1){
//			while(!deq.empty() && deq.back().first < last){
//				deq.pop_back();
//			}
//		}
//
//		if(i != 0){
//			printf("%d ", deq.size() + 1);
//		}
//		else{
//			printf("0 ");
//		}
//
//		if(i != 0){
//			deq.push_back(p(i, buf));
//		}
//		last = -1;
//
//#ifdef DEBUG
//		printf("deq: [");
//		for(p pp : deq){
//			printf("(%d, %d), ", pp.first, pp.second);
//		}
//		printf("]\n");
//#endif
