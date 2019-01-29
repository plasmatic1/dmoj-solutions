//============================================================================
// Name        : MollyAndFlyingDrones.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cstdio>
#include <stack>
#include <utility>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> p; //(index, value)

const int MAX = 1000002, MAX_V = MAX - 1;
int n, q, city[MAX];
ll buf, buf2, sub_count[MAX_V];//sub_count nice name xdd
stack<p> mono_stack;

int main() {
	scanf("%d %d", &n, &q);

	for (int i = 1; i <= n; ++i) {
		scanf("%lld", &buf);
		city[i] = buf;
	}
	city[0] = -1;
	city[n + 1] = -1;

	fill(sub_count, sub_count + MAX_V, 0);
	mono_stack.push(p(0, -1));

	for (int i = 1; i <= n; ++i) {
		p top = mono_stack.top();

//		printf("city[i]: %d\n", city[i]);
//		printf("top.second: %d\n", top.second);

		if(city[i] < top.second){
//			printf("less than\n");
			while(top.second > city[i]){
				mono_stack.pop();
				p top2 = mono_stack.top();

				//clarity
				buf = top.first - top2.first;
				buf2 = i - top.first;

//				printf("for top.second: %d\n", top.second);
//				printf("buf: %d\n", buf);
//				printf("buf2: %d\n", buf2);

				sub_count[top.second] += buf * buf2;

				top = top2;
			}
		}
		mono_stack.push(p(i, city[i]));
	}

//	printf("----\n");

	p top = mono_stack.top();
	while(top.second != -1){
		mono_stack.pop();
		p top2 = mono_stack.top();

		//clarity
		buf = top.first - top2.first;
		buf2 = n - top.first + 1;

//		printf("for top.second: %d\n", top.second);
//						printf("buf: %d\n", buf);
//						printf("buf2: %d\n", buf2);

		sub_count[top.second] += buf * buf2;

		top = top2;
	}

//	printf("sub_count: ");
//	for (int i = 0; i < 10; ++i) {
//		printf("%d, ", sub_count[i]);
//	}
//	printf("\n");

	//pfx sum array
	for (int i = 1; i < MAX_V; ++i) {
		sub_count[i] += sub_count[i - 1];
	}

	for (int i = 0; i < q; ++i) {
		scanf("%lld %lld", &buf, &buf2);
		printf("%lld\n", sub_count[buf2] - sub_count[buf - 1]);
	}

	return 0;
}
