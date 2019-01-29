//============================================================================
// Name        : ChooseYourOwnArithmatic.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 10;
int w, d, v, buf;
vector<int> arr;
bool hasonezero = false;

bool recurs(int target, int left, int val){
	if(val == target && hasonezero){
		return true;
	}

	if(left > 1){
		for(int i : arr){
			if(recurs(target, left - 1, val * i) || recurs(target, left - 1, val + i)){
				return true;
			}
		}

		return false;
	}
	else{
		for(int i : arr){
//			printf("val=%d, i=%d, pro=%d, sum=%d\n", val, i, val * i, val + i);

			if((val * i == target) || (val + i == target)){
				return true;
			}
		}

		return false;
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> w >> d;

	for (int i = 0; i < d; ++i) {
		cin >> buf;
		arr.push_back(buf);

		if(buf < 2){
			hasonezero = true;
		}
	}

	cin >> v;

	for (int i = 0; i < v; ++i) {
		cin >> buf;
		bool pass = false;

		for(int i : arr){
			if(recurs(buf, w, i)){
				pass = true;
				break;
			}
		}

		if(pass){
			printf("Y\n");
		}
		else{
			printf("N\n");
		}
	}
}
