//============================================================================
// Name        : UnitingTheEarthEmpire.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

//This aint passing shit but whatever

#include <bits/stdc++.h>
//#define DEBUG
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p;

int n, size = 0; //Size matters
ll buf, ans = 0;
deque<p> deq;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> buf;

	deq.emplace_back(buf, 1);
	for (int i = 1; i < n; ++i) {
		cin >> buf;

		while(!deq.empty() && deq.back().first < buf){
			ans += deq.back().second;
			deq.pop_back();
		}

		if(!deq.empty()){
			if(buf == deq.back().first){
				p top = deq.back();
				deq.pop_back();
				ans += top.second;
				deq.emplace_back(buf, top.second + 1);

				if(deq.size() > 1){
					ans++;
				}
			}
			else{
				deq.emplace_back(buf, 1);
				ans++;
			}
		}
		else{
			deq.emplace_back(buf, 1);
		}


#ifdef DEBUG
		printf("deq : [");
		for(p pp : deq){
			printf("(%d, %lld), ", pp.first, pp.second);
		}
		printf("]\n");
#endif
	}

	cout << ans << endl;
	return 0;
}
