//============================================================================
// Name        : dmopc18c5p4.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 200001;
int n, para = 0, parb = 0;
string a, b;
bool diffs[MAX];

#define YES printf("YES\n")
#define NO printf("NO\n")

inline int parity(string &s){
	int cnt = 0;
	for(int i = 0; i < n; i++)
		cnt += s[i] == 'F';
	return cnt % 2;
}

inline bool alldiff(string &s){
	for(int i = 1; i < n; i++){
		if(s[i] == s[i - 1])
			return false;
	}
	return true;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> a >> b;

	if(n == 1 || alldiff(a)){
		if(a == b)
			YES;
		else
			NO;

		return 0;
	}

	if(parity(a) != parity(b)){
		NO;
	}
	else{
		YES;
	}

//	for (int i = 0; i < n; ++i)
//		diffs[i] = a[i] != b[i];
//
//	printf("diffs: ");
//		for (int i = 0; i < n; ++i) {
//			printf("%d, ", diffs[i]);
//		}
//		printf("\n");
//
//	for (int i = 1; i < n; i++)
//		if(diffs[i - 1] && diffs[i])
//			diffs[i - 1] = diffs[i] = false;
//
//	int dcnt = 0;
//	for (int i = 0; i < n; ++i)
//		dcnt += diffs[i];
//
//	if(dcnt != 2){
//		NO;
//		return 0;
//	}
//
//	int first = -1, second = -1;
//	for (int i = 0; i < n; ++i) {
//		if(diffs[i]){
//			if(first == -1) first = i;
//			else if(second == -1) second = i;
//		}
//	}
//
//	if((second - first) % 2)
//		YES;
//	else
//		NO;
}
