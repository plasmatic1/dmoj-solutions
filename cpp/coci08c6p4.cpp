//============================================================================
// Name        : Cuskija.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 10000;
int n, buf, cnt[3];
queue<int> nums[3];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> buf;
		nums[buf % 3].push(buf);
		cnt[buf % 3]++;
	}

	if(cnt[0] == 0 && (cnt[1] == 0 || cnt[2] == 0)){
		int v = -1;
		if(cnt[1] == 0){
			v = 2;
		}
		else{
			v = 1;
		}

		for (int i = 0; i < cnt[v]; ++i) {
			printf("%d ", nums[v].front());
			nums[v].pop();
		}
		return 0;
	}

	if(cnt[1] + cnt[2] + 1 < cnt[0]){
		printf("impossible\n");
		return 0;
	}

	int minv = -1;
	if(cnt[1] < cnt[2]){
		minv = 1;
	}
	else{
		minv = 2;
	}

	bool enter = false;

	while(cnt[0] > 2){
		enter = true;
		if(cnt[minv] <= 0){
			minv = minv == 1 ? 2 : 1;

			if(cnt[minv] <= 0){
				printf("impossible\n");
				return 0;
			}
		}

		printf("%d %d ", nums[0].front(), nums[minv].front());
		nums[0].pop();
		nums[minv].pop();

		cnt[0]--;
		cnt[minv]--;
	}

	if(cnt[0] < 1){
		printf("impossible\n");
		return 0;
	}
	else if(cnt[0] < 2){
		if(enter){
			printf("impossible\n");
			return 0;
		}
	}
	else{
		printf("%d ", nums[0].front());
		nums[0].pop();
	}

	enter = false;
	for (int i = 0; i < cnt[1]; ++i) {
		printf("%d ", nums[1].front());
		nums[1].pop();
		enter = true;
	}

	if(!enter){
		cnt[2]--;
		printf("%d ", nums[2].front());
		nums[2].pop();
	}

	printf("%d ", nums[0].front());

	for (int i = 0; i < cnt[2]; ++i) {
		printf("%d ", nums[2].front());
		nums[2].pop();
	}
}
