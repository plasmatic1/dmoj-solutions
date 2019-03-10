//============================================================================
// Name        : coci15c4p4.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 1000;
int k, q;
ll n, ba, bb, laycnt = 0,
	layers[MAX];

ll uplay(ll v, int layer){
	return layers[layer - 1] + (v - layers[layer]) / k;
}
// u p l e i :^)

int layerOf(ll v){
	return upper_bound(layers, layers + laycnt, v) - layers - 1;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> k >> q;

	if(k > 1){
		ll csum = 1, cpow = 1;
		for(int i = 0; csum <= n; i++){
			layers[i] = csum;
			laycnt++;
			csum += cpow;
			cpow *= k;
		}
		layers[laycnt++] = LLONG_MAX;
	}

	for (int i = 0; i < q; ++i) {
		cin >> ba >> bb;

		if(k == 1)
			printf("%lld\n", abs(bb - ba));
		else{
			if(ba > bb) swap(ba, bb);

			int laya = layerOf(ba), layb = layerOf(bb), tot = 0;

			while(layb > laya){
				tot++;
				bb = uplay(bb, layb);
				layb = layerOf(bb);
			}

			while(ba != bb){
				tot += 2;
				ba = uplay(ba, layerOf(ba));
				bb = uplay(bb, layerOf(bb));
			}

			printf("%d\n", tot);
		}
	}
}