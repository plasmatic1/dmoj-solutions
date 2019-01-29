//============================================================================
// Name        : FireHose.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct p{
	int d, i;

	friend bool operator<(const p &a, const p &o){
		return a.d < o.d;
	}

	bool operator>(const p &o){
		return d > o.d;
	}
};

const int MAX = 1001, CIR = 1000000;
int h, k, buf, house[MAX], dist[MAX], shift[MAX];
p maxdis;

int sim(int hlen){
	int cnt = 1;

	int buf = 0;
	for (int i = 0; i < h; ++i) {
//		printf("on i=%d,s=%d\n", i, shift[i]);
		if(shift[i] > (buf + hlen)){
//			printf("lastbuf=%d,newb=%d\n", buf, shift[i]);
			buf = shift[i];
			cnt++;
		}
	}

	return cnt;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> h;

	for (int i = 0; i < h; ++i) {
		cin >> house[i];
	}

	sort(house, house + h);

	maxdis = {INT_MIN, INT_MIN};
	int h0 = h - 1;
	for (int i = 0; i < h0; ++i) {
		dist[i] = house[i + 1] - house[i];
		maxdis = max(maxdis, {dist[i], i});
	}

	dist[h0] = house[0] - house[h0] + CIR;
	maxdis = max(maxdis, {dist[h0], h0});

	cin >> k;

	//Remove the largest distance and creates a new shifted array for the other dists

	int minr=INT_MAX;
	for(int ii = 0; ii < h; ii++){
		maxdis.i = ii;
		for (int i = maxdis.i + 1; i < h; ++i) {
				shift[i - maxdis.i] = dist[i];
			}

			int offset = h - maxdis.i;
			for (int i = 0; i < maxdis.i; ++i) {
				shift[i + offset] = dist[i];
			}

			// Convert into pfx sum array

			for(int i = 1; i < h; i++){
				shift[i] += shift[i - 1];
			}

			int l = 0, r = shift[h0];

		//	printf("simwith500=%d\n", sim(10000));

			while(r > l + 1){
				int mid = (l + r) / 2;

				if(sim(mid) <= k){
					r = mid;
				}
				else{
					l = mid;
				}

		//		printf("found l=%d,r=%d,sv=%d\n", l, r, sim(mid));
			}

			minr=min(minr, r);
	}

	printf("%d\n", (minr + (minr % 2)) / 2);

	return 0;
}
