//============================================================================
// Name        : Cameras.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 100001;
int n, k, r, buf, cnt = 0, totaltree[MAX];
bool iscam[MAX];

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

	cin >> n >> k >> r;

	for (int i = 0; i < k; ++i) {
		cin >> buf;
		add(buf, 1);
		iscam[buf] = true;
	}

	int md = n - r + 1, stretch = r - 1;
	for (int i = 1; i <= md; ++i) {
		int rbound = i + stretch, ccnt = sum(rbound) - sum(i - 1);
		if(ccnt < 2){
			if(iscam[rbound]){
				int rbound1 = rbound - 1;

				add(rbound1, 1);
				iscam[rbound1] = true;
			}
			else{
				add(rbound, 1);
				iscam[rbound] = true;
			}

			if(ccnt < 1){
				for (int j = rbound; j > rbound - 3; --j) {
//					printf("looking at j=%d, iscam=%d\n", j, iscam[j]);
					if(!iscam[j]){
						add(j, 1);
						iscam[j] = true;
						cnt++;
						break;
					}
				}
			}

			cnt++;
		}
	}

	printf("%d\n", cnt);
}
