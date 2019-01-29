//============================================================================
// Name        : SegmentTreeTest.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 100001, TMAX = 300001, VMAX = 700001; //IMAX = 500001;
int n, m, ba, bb, arr[MAX], mintree[TMAX], gcdtree[TMAX], vptr = 0;
char bi;
unordered_map<int, unordered_map<int, int>> totaltree;

void add(int val, int dist, int z){
	for(; dist <= n; dist += dist & -dist){
			totaltree[val][dist] += z;
	}
}

void invadd(int val, int dist, int z){
	for(; dist <= n; dist += dist & -dist){
		auto ele = totaltree[val].find(dist);

		if(ele == totaltree[val].end()){
			totaltree[val].emplace(dist, -z);
		}
		else if((ele->second -= z) == 0){
			totaltree[val].erase(ele);
		}
	}
}

int sum(int y, int x){
	int summ = 0;

	for(; x > 0; x -= x & -x){
		summ += totaltree[y][x];
	}

	return summ;
}

int gcd(int a, int b){
	if(b == 0){
		return a;
	}
	return gcd(b, a % b);
}

// Min Tree

int buildm(int i, int l, int r){
	if(l == r){
		return mintree[i] = arr[l];
	}

	int mid = (l + r) / 2;

	return mintree[i] = min(buildm(i << 1, l, mid), buildm(i << 1 | 1, mid + 1, r));
}

int querym(int i, int bl, int br, int ql, int qr){
	if(ql > qr){
		return INT_MAX;
	}

	if(bl == ql && br == qr){
		return mintree[i];
	}

	int mid = (bl + br) / 2;

	return min(querym(i << 1, bl, mid, ql, min(qr, mid)), querym(i << 1 | 1, mid + 1, br, max(ql, mid + 1), qr));
}

int updatem(int i, int bl, int br, int q, int v){
    if(q < bl || q > br){
		return mintree[i];
    }

	if(bl == q && br == q){
		return mintree[i] = v;
	}

	int mid = (bl + br) / 2;

	return mintree[i] = min(updatem(i << 1, bl, mid, q, v), updatem(i << 1 | 1, mid + 1, br, q, v));
}

// GCD Tree

int buildg(int i, int l, int r){
	if(l == r){
		return gcdtree[i] = arr[l];
	}

	int mid = (l + r) / 2;

	return gcdtree[i] = gcd(buildg(2 * i, l, mid), buildg(2 * i + 1, mid + 1, r));
}

int queryg(int i, int bl, int br, int ql, int qr){
	if(ql > qr){
		return 0;
	}

	if(bl == ql && br == qr){
		return gcdtree[i];
	}

	int mid = (bl + br) / 2;

	return gcd(queryg(i << 1, bl, mid, ql, min(qr, mid)), queryg(i << 1 | 1, mid + 1, br, max(ql, mid + 1), qr));
}

int updateg(int i, int bl, int br, int q, int v){
    if(q < bl || q > br){
		return gcdtree[i];
    }

	if(bl == q && br == q){
		return gcdtree[i] = v;
	}

	int mid = (bl + br) / 2;

	return gcdtree[i] = gcd(updateg(i << 1, bl, mid, q, v), updateg(i << 1 | 1, mid + 1, br, q, v));
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	//Taking input

	cin >> n >> m;

	for (int i = 1; i <= n; ++i) {
		cin >> arr[i];
	}

	buildg(1, 1, n);
	buildm(1, 1, n);

	for (int i = 1; i <= n; ++i) {
		add(arr[i], i, 1);
	}

	//Processing

	for (int i = 0; i < m; ++i) {
		cin >> bi >> ba >> bb;

		if(bi == 'C'){
			updateg(1, 1, n, ba, bb);
			updatem(1, 1, n, ba, bb);

			invadd(arr[ba], ba, 1);
			add(bb, ba, 1);

			arr[ba] = bb;
		}
		else if(bi == 'M'){
			printf("%d\n", querym(1, 1, n, ba, bb));
		}
		else if(bi == 'G'){
			printf("%d\n", queryg(1, 1, n, ba, bb));
		}
		else{
			//bi == Q
			int qr = queryg(1, 1, n, ba, bb);

			printf("%d\n", sum(qr, bb) - sum(qr, ba - 1));
		}
	}
}
