//============================================================================
// Name        : usaco19febbronze1.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

int arr[3];

int main(){
	freopen("herding.in", "r", stdin);
	freopen("herding.out", "w", stdout);

	for(int i = 0; i < 3; i++)
		cin >> arr[i];
	sort(arr, arr + 3);

	if(arr[1] == arr[0] + 1 && arr[2] == arr[1] + 1)
		printf("0\n");
	else if(arr[1] - arr[0] == 2 || arr[2] - arr[1] == 2)
		printf("1\n");
	else
		printf("2\n");

	int biggest = max(arr[1] - arr[0], arr[2] - arr[1]);
	printf("%d\n", biggest - 1);
}
