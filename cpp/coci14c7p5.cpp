//============================================================================
// Name        : coci14c7p5.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const double PREC = 0.001;
const int MAX = 300001;
int n, k,
	arr[MAX];
double suffix[MAX];

bool hasAverage(double avg){
	// Initialize values
	double ctot = 0;
	for(int i = 1; i <= n; i++){
		ctot += arr[i] - avg;
		suffix[i] = ctot;
	}
	for(int i = n - 1; i > 0; i--)
		suffix[i] = max(suffix[i], suffix[i + 1]);

	// Actual calculations
	int end = n - k + 1;
	double diff = 0;
	for(int i = 1; i <= end; i++){
		if(suffix[i + k - 1] >= diff) return true;
		diff -= avg - arr[i];
	}

	return false;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> k;

	int maxv = 0;
	for(int i = 1; i <= n; i++)
		cin >> arr[i], maxv = max(maxv, arr[i]);

	double l = 1, r = maxv;
	while(l + PREC < r){
		double mid = (l + r) / 2.;

		if(hasAverage(mid))
			l = mid;
		else
			r = mid;
	}

//	printf("l=%f r=%f\n", l, r);
	printf("%.10f\n", l);
}