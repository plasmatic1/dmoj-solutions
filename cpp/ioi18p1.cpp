//============================================================================
// Name        : ioi18p1.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

#ifndef ONLINE_JUDGE
int press(string s);
#endif

string guess_sequence(int n){
	string cur = "",
			ava[3];

	// Guessing first letter
	int ret = press("AB");
	if(ret){
		ret = press("A");
		if(ret)
			cur = "A", ava[0] = "B", ava[1] = "X", ava[2] = "Y";
		else
			cur = "B", ava[0] = "A", ava[1] = "X", ava[2] = "Y";
	}
	else{
		ret = press("X");
		if(ret)
			cur = "X", ava[0] = "A", ava[1] = "B", ava[2] = "Y";
		else
			cur = "Y", ava[0] = "A", ava[1] = "B", ava[2] = "X";
	}

	// Rest of it
	for (int i = 1; i < n - 1; ++i) {
		ret = press(cur + ava[0] + ava[0] + cur + ava[1] + ava[0] + cur + ava[1] + ava[1]) - i;

		if(ret == 1){
			ret = press(cur + ava[0] + ava[2]) - i;

			if(ret == 0) cur += ava[1] + ava[2];
			else if(ret == 1) cur += ava[0] + ava[1];
			else cur += ava[0] + ava[2];

			i++;
		}
		else if(ret == 2){
			ret = press(cur + ava[1] + ava[0]) - i;

			if(ret == 0) cur += ava[0] + ava[0];
			else if(ret == 1) cur += ava[1] + ava[1];
			else cur += ava[1] + ava[0];

			i++;
		}
		else cur += ava[2];
	}

	// Last letter if required
	int sz = cur.size();
	if(sz < n){
		ret = press(cur + ava[0]);
		if(ret > sz) cur += ava[0];
		else{
			ret = press(cur + ava[1]);
			if(ret > sz) cur += ava[1];
			else cur += ava[2];
		}
	}

	return cur;
}

#ifndef ONLINE_JUDGE
const int N = 20;
const string STR = "ABYXXBYXYBBYXBYXXYBB";
int presscnt = 0;

int press(string s){
	int sz = s.length(), ptr = 0, best = INT_MIN;
	assert(sz <= N << 2);
	for (int i = 0; i < sz; ++i) {
		if(s[i] == STR[ptr])
			ptr++;
		else
			ptr = 0;

		best = max(best, ptr);
		if(ptr == N) ptr = 0;
	}
	presscnt++;
	return best;
}

int main(){
	printf("%s\n", guess_sequence(N).c_str());
	printf("presscnt=%d\n", presscnt);
	return 0;
}
#endif