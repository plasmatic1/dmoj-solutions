//============================================================================
// Name        : Rocks.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 10001;
int n = 0, c,
		values[MAX], counttree[MAX];
char bi;
string ba, bb;
unordered_map<string, int> rockmap;

void add(int x, int z){
	for(; x < MAX; x += x & -x){
		counttree[x] += z;
	}
}

inline void setv(int x, int z){
	add(x, z - values[x]);
	values[x] = z;
}

int sum(int x){
	int summ = 0;

	for(; x > 0; x -= x & -x){
		summ += counttree[x];
	}

	return summ;
}

const int A = (int)('a') - 1;
inline int get_val(string str){
	int sum = 0;

	for(char ch : str){
		sum += (int)(ch) - A;
	}

	return sum;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> c;

	for (int i = 0; i < c; ++i) {
		cin >> bi;

		if(bi == 'A'){
			cin >> ba;

			if(rockmap.count(ba)){
				printf("Can't add %s\n", ba.c_str());
				continue;
			}

			rockmap[ba] = ++n;
			setv(n, get_val(ba));
		}
		else if(bi == 'S'){
			cin >> ba >> bb;

			int l = rockmap[ba], r = rockmap[bb];

			rockmap[ba] = r;
			rockmap[bb] = l;

			setv(r, get_val(ba));
			setv(l, get_val(bb));
		}
		else if(bi == 'M'){
			cin >> ba >> bb;

			int l = rockmap[ba], r = rockmap[bb];

			if(l > r){
				swap(l, r);
			}

			printf("%d\n", sum(r) - sum(l - 1));
		}
		else if(bi == 'R'){
			cin >> ba >> bb;

			auto ptr = rockmap.find(ba);
			int l = ptr->second;
			rockmap.erase(ptr);

			rockmap[bb] = l;
			setv(l, get_val(bb));
		}
		else{ //bi == N
			printf("%d\n", n);
		}
	}
}
