//============================================================================
// Name        : AirSuperiority.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 201;
int n, q, ba, bb, bc, bd, be, bf, ci = 0,
	vals[MAX];
char bi;

struct tp{
	int x, y, z, v;

	tp(int x0, int y0, int z0, int v0) : x(x0), y(y0), z(z0), v(v0){}
	tp() : x(-1), y(-1), z(-1), v(-1){}

	friend bool operator<(const tp &a, const tp &b){
		if(a.x == b.x){
			if(a.y == b.y){
				return a.z < b.z;
			}

			return a.y < b.y;
		}

		return a.x < b.x;
	}
};

set<tp> pts;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> q;

	for (int i = 0; i < q; ++i) {
		cin >> bi >> ba >> bb >> bc >> bd;

		if(bi == 'U'){
			tp tpv = tp(ba, bb, bc, ci);
			auto ptr = pts.find(tpv);

			if(ptr != pts.end()){
				vals[ptr->v] = bd;
			}
			else{
				pts.insert(tpv);

				vals[ci++] = bd;
			}
		}
		else{ // bi == 'S'
			cin >> be >> bf;

			int sumv = 0;
			for(tp pt : pts){
				if(ba <= pt.x && pt.x <= bd && bb <= pt.y && pt.y <= be && bc <= pt.z && pt.z <= bf){
					sumv += vals[pt.v];
				}
			}

			printf("%d\n", sumv);
		}
	}
}
