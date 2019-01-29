//============================================================================
// Name        : CountlessComputerCalculations.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

int q;
double by, bz;
const double PREC = 1e-14, MV = (double)((1 << 30) - 1 + (1 << 30));

double powtow(double x, int y){
	double curr = x;

	y--;
	while(y--){
//		printf("%f\n", curr);
		curr = pow(x, curr);
	}

	return curr;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> q;

	for (int i = 0; i < q; ++i) {
		cin >> by >> bz;

		double l = 1, r = MV;

		while(l + PREC < r){
			double h = (l + r) / 2;
//			printf("testing h=%f\n", h);

			if(powtow(h, by) < bz){
//				printf("going up\n");
				l = h;
			}
			else{
				r = h;
			}
		}

//		printf("%f %f\n", l, r);
		printf("%.12f\n", l);
	}
}
