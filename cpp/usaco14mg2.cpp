//============================================================================
// Name        : usaco14mg2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Scan and Debug
void scan(){}
template<typename F, typename... R> void scan(F &f,R&... r){cin>>f;scan(r...);}
int di_; string dnms_, co_ = ",";
void debug_(){cout<<endl;}
template<typename F, typename... R> void debug_(F f, R... r){while(dnms_[di_] != ',')cout<<dnms_[di_++];di_++;cout<<": "<<f<<",";debug_(r...);}
#define debug(...) dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__)

const int MAX = 100001;
const double PREC = 1e-6;
int n,
	arr[MAX];
double tot,
	pfx[MAX];

bool sim(double avg) {
	for (int i = 1; i < n - 1; i++) // pfx[i] = arr[1..i] - i * avg
		pfx[i] = pfx[i - 1] + arr[i] - avg;
	for (int i = n - 3; i > 0; i--) // convert to suffix max array
		pfx[i] = max(pfx[i], pfx[i + 1]);

	double cTot = tot - n * avg, cur = 0;
	for (int i = 1; i < n - 1; i++) {
		if (cTot - pfx[i] + cur <= 0)
			return true;
		cur -= avg - arr[i];
	}
	return false;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	scan(n);

	for (int i = 0; i < n; i++) {
		scan(arr[i]);
		tot += arr[i];
	}

	double l = 0, r = 1e5;
	while(l + PREC < r) {
		double mid = (l + r) / 2.;

		if (sim(mid))
			r = mid;
		else
			l = mid;
	}

	printf("%.3f\n", l);
}