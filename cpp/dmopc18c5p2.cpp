//============================================================================
// Name        : dmopc18c5p2.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 1001;
const double PREC = 0.00000001;
int n, m;
double pix[MAX][MAX];

inline double average(double c){
	double sum = 0;

	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			double end = pix[i][j] * c;
			sum += end > 1. ? 1 : end;
		}
	}

	return sum / (double)(n * m);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			cin >> pix[i][j];

	double l = 0, r = 500.;
	while(l + PREC < r){
		double mid = (l + r) / 2.;

		if(average(mid) > 0.48 + PREC)
			r = mid;
		else
			l = mid;
	}

	if(abs(l - 1) < 0.00001)
		printf("correctly exposed\n");
	else if(l > 1)
		printf("underexposed\n%.6f\n", l);
	else
		printf("overexposed\n%.6f\n", l);
}
