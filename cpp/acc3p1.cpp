//============================================================================
// Name        : DiverseArrays.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

//Always want diversity

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 1000001;
int n, k, ccnt = 1,
	arr[MAX], diffcnt[MAX];
ll tcount = 0;
int exists[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> k;

	for (int i = 1; i <= n; ++i) {
		cin >> arr[i];
	}

	// Do calc

	exists[arr[1]]++;

	for(int l = 1, r = 1; r <= n;){
//		printf("l=%d r=%d cnt=%d\n", l, r, ccnt);

		if(ccnt >= k){
			tcount += n - r + 1;

			if(--exists[arr[l++]] == 0){
				ccnt--;
			}
		}
		else{
			if(exists[arr[++r]]++ == 0){
				ccnt++;
			}
		}
	}

	// Output

	printf("%lld\n", tcount);
}
