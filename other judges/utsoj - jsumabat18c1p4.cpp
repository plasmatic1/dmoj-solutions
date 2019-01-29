//============================================================================
// Name        : JsumabatContestP4.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

int n;
string buf;

inline bool isprime(int v){
	if(v < 2) return false;
	if(v == 2) return true;

	int sqv = sqrt(v);

	for(int i = 2; i <= sqv; i++){
		if(v % i == 0){
			return false;
		}
	}

	return true;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

//	for(int i = 0; i < 10; i++){
//		printf("i=%d isp=%d\n", i, isprime(i));
//	}

	for (int i = 0; i < n; ++i) {
		cin >> buf;

		int cnt = buf.length(), sum = 0;

		for(int j = 0; j < cnt; j++){
			sum += (int)(buf[j] - '0');
		}

		if(isprime(cnt) && isprime(sum)){
			printf("YES\n");
		}
		else{
			printf("NO\n");
		}
	}
}
