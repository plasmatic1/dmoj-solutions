//============================================================================
	// Name        : TreePlanting.cpp
	// Author      : Daxi the Taxi
	// Version     :
	// Copyright   : ALL YOUR CODE IS BELONG TO US
	// Description : Hello World in C++, Ansi-style
	//============================================================================

	#include <bits/stdc++.h>

	using namespace std;

	typedef long long ll;
	typedef pair<int, int> p;

	const int MAX = 3000, DC = MAX + 2;
	int n, ins, br, bc, bx;
	int diags[DC][MAX + 1], tsum = 0;

	void add(int tree[], int x, int z){
		for(; x <= DC; x += x & -x){
			tree[x] += z;
		}
	}

	int sum(int tree[], int x){
		int sum = 0;

		for(; x > 0; x -= x & -x){
			sum = (sum + tree[x]) % 1000000007;
		}

		return sum;
	}

	int main(){
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);

		cin >> n;

		for (int i = 0; i < n; ++i) {
			cin >> ins >> br >> bc >> bx;

	#ifdef DEBUG
			printf("Instruction i=%d, ins=%d, br=%d, bc=%d, bx=%d\n", i, ins, br, bc, bx);
	#endif

			int diagi = br + bc - 1;

			if(ins == 1){
				add(diags[diagi], bc, bx);
			}
			else{
				//ins == 2
				int v = sum(diags[diagi], bc + bx) - sum(diags[diagi], bc - 1);
				tsum = (tsum + v) % 1000000007;

	#ifdef DEBUG
				printf("%d\n", v);
	#endif
			}
		}

		printf("%d\n", tsum);
	}
