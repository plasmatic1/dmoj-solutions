//============================================================================
// Name        : FreedomAppears.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

ll gcd(ll a, ll b){
	if(b == 0){
		return a;
	}
	return gcd(b, a % b);
}

struct slopes{
	ll x, y, z;

	slopes(ll x0, ll y0, ll z0) : x(x0), y(y0), z(z0){}
	slopes() : x(-1), y(-1), z(-1){}

	void div(ll v){
		x /= v;
		y /= v;
		z /= v;
	}

	friend bool operator<(const slopes &a, const slopes &b){
		if(a.x == b.x){
			if(a.y == b.y){
				return a.z < b.z;
			}
			return a.y < b.y;
		}
		return a.x < b.x;
	}

	friend bool operator==(const slopes &a, const slopes &b){
		return a.x == b.x && a.y == b.y && a.z == b.z;
	}
};

const int MAX = 100000;
int n, total;
ll sx, sy, sz, bx, by, bz;
set<slopes> slopeset;
//slopes asls[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> sx >> sy >> sz >> n;
	total = n;

	for (int i = 0; i < n; ++i) {
		cin >> bx >> by >> bz;

		ll dx = bx - sx, dy = by - sy, dz = bz - sz;

		slopes slp = {dx, dy, dz};
		ll gcdv = gcd(gcd(abs(dx), abs(dy)), abs(dz));
		slp.div(gcdv);

//		printf("gcdv=%d, slope %d, %d, %d\n", gcdv, slp.x, slp.y, slp.z);

		if(slopeset.count(slp)){
			total--;
		}
		else{
			slopeset.insert(slp);
		}
	}

	printf("%d\n", total);
}
