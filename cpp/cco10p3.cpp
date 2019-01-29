//============================================================================ //Saving this for later
// Name        : Wowow.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
//#define DEBUG

using namespace std;

typedef long long ll;

struct instruct{
	char ins;
	int fri, rnk;
};

#define getchar() (*_pbuf ? *_pbuf++ : (_buf[fread_unlocked(_pbuf = _buf, 1, 1048576, stdin)] = 0, *_pbuf++))
char _buf[1048577], *_pbuf = _buf;

inline int readint() {
	int c, o = 0;
	while ((c = getchar()) < '0');
	do {o = (o<<3)+(o<<1) + (c - '0');} while ((c = getchar()) >= '0');
	return o;
}

int n, fn = 0, bfriend, brank, rnk_ptr = 1,
		friends[1000001], rank_mp[1000001], totaltree[1000001], ranks[1000001];
char instru;
instruct instructs[1000001];

inline void add(int x, int z){
	for(; x <= 1000001; x += x & -x){
		totaltree[x] += z;
	}
}

inline int sum(int x){
	int sum = 0;

	for(; x > 0; x -= x & -x){
		sum = sum + totaltree[x];
	}

	return sum;
}

inline int index_of(int rank){
	return lower_bound(rank_mp, rank_mp + rnk_ptr, rank) - rank_mp;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	n = readint();

	rank_mp[0] = INT_MIN;

	for (int i = 0; i < n; ++i) {
		instru = getchar();

		if(instru == 'Q'){
			brank = readint();

			instructs[i] = {instru, -1, brank};
		}
		else{
			bfriend = readint();
			brank = readint();

			instructs[i] = {instru, bfriend, brank};
			rank_mp[rnk_ptr++] = brank;
		}
	}

	sort(rank_mp, rank_mp + rnk_ptr);

	for (int i = 0; i < n; ++i) {
		char ins = instructs[i].ins;
		int rnk = instructs[i].rnk, fri = instructs[i].fri;

		if(ins == 'N'){
			rnk = index_of(rnk);

			ranks[rnk] = fri;
			friends[fri] = rnk;

			add(rnk, 1);
			fn++;
		}
		else if(ins == 'M'){
			rnk = index_of(rnk);

			add(friends[fri], -1);

			friends[fri] = rnk;
			ranks[rnk] = fri;

			add(rnk, 1);
		}
		else{
			//instru == 'Q'

			rnk = fn - rnk;
			int skill = 0, total = 0;

			for (int i = 524288; i > 0; i >>= 1) {
				int alt = skill | i;
//				printf("i=%d,alt=%d,val at alt=%d\n", i, alt, tree[alt]);
				if(total + totaltree[alt] <= rnk){
					skill = alt;
					total += totaltree[alt];
				}
			}

			printf("%d\n", ranks[skill + 1]);
		}
	}
}
