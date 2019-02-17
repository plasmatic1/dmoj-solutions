//============================================================================
// Name        : valentines19s2.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 100001;
int n, q, ba, bb, bt;
unordered_set<int> sadrow, sadcol;
set<p> sadpts;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> q;

	for (int i = 0; i < q; ++i) {
		cin >> bt >> ba >> bb;

		if(bt == 1){
			if(sadrow.count(ba))
				sadrow.erase(ba);
			else sadrow.insert(ba);

			if(sadcol.count(bb))
				sadcol.erase(bb);
			else sadcol.insert(bb);

			p pt = make_pair(ba, bb);
			if(sadpts.count(pt))
				sadpts.erase(pt);
			else sadpts.insert(pt);
		}
		else{
			int tot = sadrow.count(ba) + sadcol.count(bb) + sadpts.count(make_pair(ba, bb));
			printf("%d\n", tot % 2);
		}
	}
}
