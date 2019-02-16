//============================================================================
// Name        : dmpg18s5.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 200001, SQM = sqrt(MAX) + 10;
int n, q, bt, ba, bb, bc,
	arr[MAX], blockm[MAX + 10],
	cnts[SQM][MAX + 10];

vector<p> *ppfacts;
int pfactssz;

inline void apply(int idx, int cur, int blocki, int change){
	if(idx == pfactssz){
		cnts[blocki][cur] += change;
		return;
	}

	int factor = ppfacts->operator[](idx).first, cnt = ppfacts->operator[](idx).second, cpow = 1;
	for(int i = 0; i <= cnt; i++){
		apply(idx + 1, cur * cpow, blocki, change);
		cpow *= factor;
	}
}

inline void change(int i, int v, int change){
	int sqv = sqrt(v);
	vector<p> pfacts;

	if(v % 2 == 0){
		int cnt = 0;
		while(v % 2 == 0){
			v >>= 1;
			cnt++;
		}
		pfacts.push_back(make_pair(2, cnt));
	}

	for(int i = 3; i <= sqv; (++i)++){
		if(v % i == 0){
			int cnt = 0;
			while(v % i == 0){
				v /= i;
				cnt++;
			}
			pfacts.push_back(make_pair(i, cnt));
		}
	}

	if(v > 1)
		pfacts.push_back(make_pair(v, 1));

	ppfacts = &pfacts;
	pfactssz = pfacts.size();
	apply(0, 1, blockm[i], change);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> q;

	int sqn = sqrt(n);
	for(int i = 1; i <= n; i++){
		cin >> arr[i];
		blockm[i] = i / sqn + 1;
		change(i, arr[i], 1);
	}
	blockm[0] = INT_MIN;
	blockm[n + 1] = INT_MAX;

	for (int i = 0; i < q; ++i) {
		cin >> bt >> ba >> bb;

		if(bt == 1){
			cin >> bc;

			int lhs = blockm[ba] + (blockm[ba] == blockm[ba - 1]),
					rhs = blockm[bb] - (blockm[bb] == blockm[bb + 1]), sum = 0;

			for(int j = lhs; j <= rhs; j++)
				sum += cnts[j][bc];
			for(int j = ba; blockm[j] < lhs; j++)
				sum += arr[j] % bc == 0;
			if(rhs + 1 >= lhs)
				for(int j = bb; blockm[j] > rhs; j--)
					sum += arr[j] % bc == 0;

			printf("%d\n", sum);
		}
		else{ // bt == 2
			change(ba, arr[ba], -1);
			change(ba, bb, 1);
			arr[ba] = bb;
		}
	}

	return 0;
}
