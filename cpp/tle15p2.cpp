//============================================================================
// Name        : Microwaves.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
//#define DEBUG
//39281

using namespace std;

typedef long long ll;
typedef pair<ll, ll> p;

const int MAX_M = 100, MAX_N = 100000;
int n, m, t, bt, bf;
multiset<ll> microwaves;
p ppl[MAX_N];

bool cmp(const p &a, const p &b){
	return a.first < b.first;
}

/*
2 3 4
1 1
2 1
3 1
 */

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m >> t;
	//[n]umber of microwaves, nu[m]ber of people in line, amount of time [T]T1103 will take to microwave his food

	for (int i = 0; i < m; ++i) {
		cin >> bt >> bf;
		ppl[i] = p(bt, bf);
	}

	sort(ppl, ppl + m, cmp);

	for (int i = 0; i < m; ++i) {
		/*
		 * Find the first available microwave for the [i]th person
		 * And add them to it, once none are available (size >= n, then stop and check)
		 */
		ll earliest;

#ifdef DEBUG
		printf(" -- On i=%d, p=(%d,%d)\n", i, ppl[i].first, ppl[i].second);
		printf("microwaves: [");
		for(int i : microwaves){
			printf("%d, ", i);
		}
		printf("]\n");
#endif

		ll micro;
		if(microwaves.empty()){
			micro = earliest = 0;

#ifdef DEBUG
			printf("Micro is empty, set n to 0\n");
#endif
		}
		else{
			auto it = microwaves.upper_bound(ppl[i].first);

			if(it == microwaves.begin()){
				//No free microwaves
				if(microwaves.size() >= n){
					micro = earliest = *microwaves.begin();
					microwaves.erase(it);
				}
				else{
					micro = 0;
					if(microwaves.size() + 1 >= n){
						earliest = min(ppl[i].second, *microwaves.begin());
					}
					else{
						earliest = 0;
					}
				}
			}
			else{
				while(it == microwaves.end() || (it != microwaves.begin() && *it > ppl[i].first)){
					it--;
				} //Look for the first value not greater than

				micro = *it;
				if(microwaves.size() >= n){
					earliest = *microwaves.begin();
				}
				else{
					earliest = 0;
				}

				microwaves.erase(it);
			}
		}

#ifdef DEBUG
			printf("Found microwave time %d\n", micro);
#endif

		ll next = max(micro, ppl[i].first) + ppl[i].second;
		microwaves.insert(next);

#ifdef DEBUG
		printf("Earliest open begin %d t(%d + %d) = %d\n", earliest, earliest, t, earliest + t);
#endif
		if(earliest + t <= ppl[i].first){
			printf("%d\n", earliest);
			return 0;
		}
	}

#ifdef DEBUG
	printf("Loop ended\n");
#endif

	if(microwaves.size() < n){
#ifdef DEBUG
		printf("%u < %d, got 0\n", microwaves.size(), n);
#endif
		printf("0\n");
		return 0;
	}

	printf("%lld\n", *microwaves.begin());

	return 0;
}
