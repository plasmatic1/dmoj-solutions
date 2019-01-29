//============================================================================
// Name        : PizzaBag.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <algorithm>
#include <cstdio>
#include <deque>
#include <climits>

//#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
//char _;

using namespace std;

typedef pair<long long, long long> p; //(pos, v)

const int MAX = 100000 * 2;
long long n, k, a[MAX], buf;
deque<p> min_;

int main() {
	scanf("%lld %lld", &n, &k);

	for (int i = 0; i < n; ++i) {
		scanf("%lld", &buf);
		a[i] = buf;
	}

	copy(a, a + k, a + n);
	n += k;

	buf = 0;
	for (int i = 0; i < n; ++i) {
		buf += a[i];
		a[i] = buf;
	}

	long long max_ = INT_MIN;
	for (int i = 0; i < n; ++i) {
		if(i > k){
			int low = i - k;
			while(!min_.empty() && min_.front().first < low){
				min_.pop_front();
			}
		}

		while(!min_.empty() && min_.back().second > a[i]){
			min_.pop_back();
		}
		min_.push_back(p(i, a[i]));

		max_ = max(max_, a[i] - min_.front().second);
	}

	printf("%lld\n", max_);

	return 0;
}
