//============================================================================
// Name        : SourCandy.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 100002;
int counttree[MAX];
int n, mv,
	arr[MAX], lblarr[MAX], sorted[MAX];

// Fenwick Tree

inline void add(int x, int z){ // Adds value `z` to index `x`
	for(; x <= mv; x += x & -x){
		counttree[x] += z;
	}
}

inline int sum(int x){ // Querys index `x`
	int sum = 0;

	for(; x > 0; x -= x & -x){
		sum += counttree[x];
	}

	return sum;
}

// Labeling

unordered_map<int, int> labelmp;

int lblmaparr[MAX], dp[MAX];
bool frozen[MAX];

struct pi{
	int v, i;

	friend bool operator<(const pi &a, const pi &b){
		return a.v < b.v;
	}

	friend bool operator>(const pi &a, const pi &b){
		return a.v > b.v;
	}
};

vector<pi> smaller, larger;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;
	mv = n + 1;

	for (int i = 1; i <= n; ++i) {
		cin >> arr[i];
	}

	for (int i = 1; i <= n; ++i) {
		cin >> sorted[i];

		labelmp[sorted[i]] = i;
	}

	// Make labels

	for (int i = 1; i <= n; ++i) {
		lblarr[i] = labelmp[arr[i]];
	}

	// Mapping labels to arr[value] = index
	for (int i = 1; i <= n; ++i) {
		lblmaparr[lblarr[i]] = i;
	}

	// Getting longest sequence

	int maxl = INT_MIN, maxli = -1, currlen = 0, end = n + 1;
	lblmaparr[end] = -2;
	for (int i = 1; i <= end; ++i) {
		if(lblmaparr[i] > lblmaparr[i - 1]){
			currlen++;
		}
		else{
			if(currlen > maxl){
				maxl = currlen;
				maxli = i - 1;
			}

			currlen = 1;
		}
	}

	// Setting longest sequence
	for (int i = 0; i < maxl; ++i) {
		frozen[lblmaparr[maxli - i]] = true;
	}

	int minval = maxli - maxl + 1;

	// -- Getting Output

	// First Line
	printf("%d\n", n - maxl);

	// Splitting it into groups
	for (int i = 1; i <= n; ++i) {
		if(!frozen[i]){
			if(lblarr[i] < minval){
				smaller.push_back({lblarr[i], i});
			}
			else{
				larger.push_back({lblarr[i], i});
			}
		}
	}

	sort(smaller.begin(), smaller.end(), greater<pi>());
	sort(larger.begin(), larger.end());

	for(int i = 1; i <= n; i++){
		add(i + 1, 1);
	}

	// Instructions
	for (pi pii : smaller) {
		int trueind = sum(pii.i + 1);

		printf("F %d\n", trueind);
		add(pii.i + 1, -1);
		add(1, 1);
	}

	for (pi pii : larger) {
		int trueind = sum(pii.i + 1);

		printf("B %d\n", trueind);
		add(pii.i + 1, -1);
	}
}
