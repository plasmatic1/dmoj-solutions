// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

const int MAX = 100;
int n, buf, arr[MAX], farr[MAX];
bool taken[MAX];
//p farra[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	for (int sdajfosdijf = 0; sdajfosdijf < 5; ++sdajfosdijf) {
		cin >> n;

		memset(taken, false, sizeof(taken));

		vector<int> nums;

		for (int i = 0; i < n; ++i) {
			nums.push_back(i);
		}

		for (int i = 0; i < n; ++i) {
			cin >> arr[i];
		}
		// Find how many need to be larger

		bool pos = true;

		for (int i = 0; i < n; ++i) {
			int ahead = n - i - 1, minreq = ahead - arr[i];

			if(minreq > nums.size()){
				pos = false;
				break;
			}

			int val = nums[minreq];
			nums.erase(nums.begin() + minreq);

			farr[i] = val + 1;
		}

		if(!pos){
			printf("IMPOSSIBLE\n");
			continue;
		}

		for (int i = 0; i < n - 1; ++i) {
			printf("%d ", farr[i]);
		}
		printf("%d\n", farr[n - 1]);
	}
}
