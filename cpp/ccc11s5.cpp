//============================================================================
// Name        : ccc11s5.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct p{
	int v, w;
};

const int MAX = 25, MS = 1 << MAX;
int n, buf, st = 0;
bool vis[MS];
deque<p> nxt;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for(int i = 0; i < n; i++){
		cin >> buf;
		st <<= 1;
		st |= buf;
	}

	vis[st] = true;
	nxt.push_back({st, 0});

	while(!nxt.empty()){
		p cur = nxt.front();
		nxt.pop_front();

		if(cur.v == 0){
			printf("%d\n", cur.w);
			return 0;
		}

		for(int i = 0; i < n; i++){
			if(!((cur.v >> i) & 1)){
				int newm = cur.v | (1 << i), streak = 0;

				for(int j = 0; j < n; j++){
					if((newm >> j) & 1) streak++;
					else{
						if(streak >= 4){
							for(int k = j - streak; k < j; k++)
								newm &= ~(1 << k);
						}
						streak = 0;
					}
				}

				if(streak >= 4)
					for(int j = n - streak; j < n; j++)
						newm &= ~(1 << j);

				if(!vis[newm]){
					vis[newm] = true;
					nxt.push_back({newm, cur.w + 1});
				}
			}
		}
	}
}
