//============================================================================
// Name        : PinballRankingRecode.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct ranking{
	int pts, ord;

	ranking(int pts0, int ord0) : pts(pts0), ord(ord0){}
	ranking() : pts(-1), ord(-1){}

	friend bool operator<(const ranking &a, const ranking &b){
		if(a.pts == b.pts){
			return a.ord > b.ord;
		}
		return a.pts > b.pts;
	}
};

const int MAX = 100001;
int n, buf, totaltree[MAX];
double summ = 0;
ranking rankings[MAX];

void add(int x, int z){
	for(; x <= n; x += x & -x){
		totaltree[x] += z;
	}
}

int sum(int x){
	int sum = 0;

	for(; x > 0; x -= x & -x){
		sum += totaltree[x];
	}

	return sum;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> buf;
		rankings[i] = ranking(buf, i + 1);
	}
	sort(rankings, rankings + n);

	for (int i = 0; i < n; ++i) {
		add(rankings[i].ord, 1);
		summ += sum(rankings[i].ord);
//		printf("for ranking pts=%d ord=%d, rank=%d\n", rankings[i].pts, rankings[i].ord, sum(rankings[i].ord));
	}

	printf("%.2f\n", summ / n);
}
