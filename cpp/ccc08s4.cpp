//============================================================================
// Name        : TwentyFour.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <algorithm>
#include <climits>
#include <cstdio>
#include <assert.h>
#include <vector>

using namespace std;

const int LOW = -9000000;

int a(const int &a, const int &b){
//	int sum = a + b;
//	return sum <= 24 ? sum : LOW;
	return a + b;
}

int b(const int &a, const int &b){
//	int dif = a - b;
//	return dif <= 24 ? dif : LOW;
	return a - b;
}

int c(const int &a, const int &b){
//	int pro = a * b;
//	return pro <= 24 ? pro : LOW;
	return a * b;
}

int d(const int &a, const int &b){
	if(b != 0 && a % b == 0){
//		int ans = a / b;
//		return ans <= 24 ? ans : LOW
		return a / b;
	}
	return LOW;
}

//int find_max(int arr[], int l){
//	int max = INT_MIN;
//	for (int i = 0; i < l; ++i) {
//		if(arr[i] > max && arr[i] > -10000 && arr[i] < 10000){
//			max = arr[i];
//		}
//	}
//
//	return max == INT_MIN ? LOW : max;
//}

int find_max(vector<int> arr, int l){
	int max = INT_MIN;
	for (int i = 0; i < l; ++i) {
		if(arr[i] > max && arr[i] > -10000 && arr[i] < 10000){
			max = arr[i];
		}
	}

	return max == INT_MIN ? LOW : max;
}

int find_max_final(int arr[], int l){
	int max = INT_MIN;
	for (int i = 0; i < l; ++i) {
		if(arr[i] > max && arr[i] > -10000 && arr[i] <= 24){
			max = arr[i];
		}
	}

	return max == INT_MIN ? LOW : max;
}

int max_(int curr, int len, int next[]){
	if(len > 1){
		int len_ = len - 1, next_[len_];
		copy(next + 1, next + len, next_);

//		assert(false);

//		int results[4] = {
//				max_(a(curr, next[0]), len_, next_),
//				max_(b(curr, next[0]), len_, next_),
//				max_(c(curr, next[0]), len_, next_),
//				max_(d(curr, next[0]), len_, next_)
//		};

		vector<int> results, next__;

//		for (int i = 0; i < len; ++i) {
//			for (int j = 0; j < len; ++j) {
//				if(i != j)
//					next__.push_back(next[i]);
//			}
//
//			copy(next__.begin(), next__.end(), next_);
//
//			results.push_back(max_(a(curr, next[i]), len_, next_));
//			results.push_back(max_(b(curr, next[i]), len_, next_));
//			results.push_back(max_(c(curr, next[i]), len_, next_));
//			results.push_back(max_(d(curr, next[i]), len_, next_));
//		}

		results.push_back(max_(a(curr, next[0]), len_, next_));
		results.push_back(max_(b(curr, next[0]), len_, next_));
		results.push_back(max_(c(curr, next[0]), len_, next_));
		results.push_back(max_(d(curr, next[0]), len_, next_));

		if(len > 2){
			int res1[4] = {
					a(curr, next[0]),
					b(curr, next[0]),
					c(curr, next[0]),
					d(curr, next[0])
			}, res2[4] = {
					a(next[1], next[2]),
					b(next[1], next[2]),
					c(next[1], next[2]),
					d(next[1], next[2])
			};

			for (int j = 0; j < 4; ++j) {
				for (int l = 0; l < 4; ++l) {
					int next__[1] = {res2[l]};
					results.push_back(max_(res1[j], 1, next__));
				}
			}
		}

//		printf("Results: curr (%d) len (%d), [%d, %d, %d, %d] (RES: %d)\n", curr, len, results[0], results[1], results[2], results[3], find_max(results, 4));

		return find_max(results, results.size());
	}

	int results[4] = {
		a(curr, next[0]),
		b(curr, next[0]),
		c(curr, next[0]),
		d(curr, next[0]),
	};

//	printf("Results: curr (%d) len (%d), [%d, %d, %d, %d] (RES: %d)\n", curr, len, results[0], results[1], results[2], results[3], find_max_final(results, 4));

	return find_max_final(results, 4);
}

int max__(int arr[], int n){
	int max___ = INT_MIN;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if(i == j)
				continue;
			for (int k = 0; k < n; ++k) {
				if(k == i || k == j)
					continue;
				for (int l = 0; l < n; ++l) {
					if(l == i || l == j || l == k)
						continue;

					int v[]{arr[j], arr[k], arr[l]};
					max___ = max(max___, max_(arr[i], 3, v));
					break;
				}
			}
		}
	}

	return max___;
}

int n;

int main() {
	scanf("%d", &n);

	for (int i = 0; i < n; ++i) {
		int a[4];
		scanf("%d\n%d\n%d\n%d", &a[0], &a[1], &a[2], &a[3]);

//		if(i < 2){
//			continue;
//		}

//		assert(false);

		printf("%d\n", max__(a, 4));
	}

	return 0;
}
