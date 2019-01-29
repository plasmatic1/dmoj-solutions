//============================================================================
// Name        : Cancer2.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 200001;
int n, q, bv, bk, bi;
ll totals[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> q;

	for (int i = 0; i < q; ++i) {
		cin >> bi;

		if(bi == 2){
			cin >> bv;

			int sqv = sqrt(bv);
			ll total = 0;

			for(int i = 2; i <= sqv; i++){
				bool flag = false;

				while(bv % i == 0){
					bv /= i;
					flag = true;
				}

				if(flag){
					total += totals[i];
				}
			}

			if(bv > 1){
				total += totals[bv];
			}

			printf("%lld\n", total);
		}
		else{
			cin >> bk >> bv;

			totals[bk] += bv;
		}
	}
}
