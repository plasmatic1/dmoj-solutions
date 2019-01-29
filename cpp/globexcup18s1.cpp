//============================================================================
// Name        : CodeCopiers.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 1000001;
int n, buf, cnt = 0,
	indegs[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> buf;

		if(buf != 0){
			indegs[buf]++;
		}
	}

//	printf("indegs: ");
//	for (int i = 0; i < n + 1; ++i) {
//		printf("%d, ", indegs[i]);
//	}
//	printf("\n");

	for (int i = 1; i <= n; ++i) {
		if(indegs[i] == 0){
			cnt++;
		}
	}

	printf("%d\n", cnt);
}
