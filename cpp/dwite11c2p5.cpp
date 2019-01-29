//============================================================================
// Name        : PortalsCheck.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <assert.h>

using namespace std;

struct disjoint{
	int size, a[99999], sizes[99999];
	disjoint(int size_) : size(size_){
		for(int i = 0; i < size; i++){
			a[i] = i;
		}
		fill(sizes, sizes + size, 0);
	}
	int root(int x){
		if(a[x] == x){
			return x;
		}
//		printf("finding root of %d, current %d\n", x, a[x]);
		return root(a[x]);
	}
	void unite(int x, int y){
		int rx = root(x), ry = root(y);
		int sx = sizes[rx], sy = sizes[ry];
		if(sx > sy){
			a[ry] = rx;
		}
		else if(sx < sy){
			a[rx] = ry;
		}
		else{
			a[ry] = rx;
			sizes[rx]++;
		}
	}
	void reset(){
		for(int i = 0; i < size; i++){
			a[i] = i;
		}
	}
	bool sim(int x, int y){
		return root(x) == root(y);
	}
};

int cnt = 0;
disjoint set(99999);
map<string, int> master;

int codeFor(string str){
	if(master.find(str) == master.end()){
		master[str] = cnt;
		return cnt++;
	}
	return master[str];
}

int main() {
	cin.sync_with_stdio(0);
	cin.tie(0);

	for (int ajsifjdsifjaidf = 0; ajsifjdsifjaidf < 5; ++ajsifjdsifjaidf) {
		int n;
		cin >> n;
//		printf("n=%d\n", n);

		for(int i = 0; i < n; i++){
			string a, b, c;
			cin >> a >> b >> c;

			int ca = codeFor(b), cb = codeFor(c);

			if (a == "p"){
//				assert(false);
				set.unite(ca, cb);
			}
			else{
//				printf("query\n");
				bool b = set.sim(ca, cb);
//				assert(false);
				if(b){
					printf("connected\n");
				}
				else{
					printf("not connected\n");
				}
			}
		}

		master.clear();
		set.reset();
		cnt = 0;
	}
	return 0;
}
