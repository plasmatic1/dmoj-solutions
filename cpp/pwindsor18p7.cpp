//============================================================================
// Name        : GoingBacktotheDefinitions.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 10001;
int n, arr[MAX];
//string final;

bool cmp(const int &a, const int &b){
	string sa = to_string(a), sb = to_string(b);
	int la = sa.length(), lb = sb.length();

	for (int i = 0; i < max(la, lb); ++i) {
		if((int)sa[i % la] > (int)sb[i % lb]){
			return true;
		}
		else if((int)sb[i % lb] > (int)sa[i % la]){
			return false;
		}
	}

	//identical

	return la > lb;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> arr[i];
	}

	sort(arr, arr + n, cmp);

	for (int i = 0; i < n; ++i) {
		printf("%d", arr[i]);
	}
	printf("\n");
}
