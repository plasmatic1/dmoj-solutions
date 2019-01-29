//============================================================================
// Name        : BoosterCushions.cpp
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
int m, n, k, ptr = 0,
	ppl[MAX];
ll total = 0;
vector<int> rows[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> m >> n >> k;

	for (int i = 0; i < k; ++i) {
		cin >> ppl[i];
	}

	sort(ppl, ppl + k, greater<int>());
	m = min(m, k);

	int fullrows = k / m, frp = fullrows * m, extracnt = k % m;
//	printf("%d %d %d\n", fullrows, frp, extracnt);

	for (int i = 0; i < frp; ) {
		for (int j = 0; j < fullrows; ++j, ++i) {
			rows[j].push_back(ppl[ptr++]);
		}

		if(extracnt > 0){
			extracnt--;
			rows[fullrows].push_back(ppl[ptr++]);
		}
	}

	int frc = (int)ceil(k / (double)m);
	for (int i = 0; i < frc; ++i) {
		int last = rows[i][0] - 1;

		//printf("on i=%d\b", i);

		for (int psn : rows[i]) {
			int newl = last - psn + 1;
			total += newl;
			last = newl + psn;

//			printf("going through person h %d, last of %d, newl of %d\n", psn, last, newl);
		}
	}

	printf("%lld\n", total);
}
