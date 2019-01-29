//============================================================================
// Name        : SC2Multitasking.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 1000000;
int n;

const string ROWS[3] = {
		"qwertyuiop", "asdfghjkl", "zxcvbnm"
};

unordered_set<int> rowcodes[3];

string buf;
int rowc[3], cnt = 0;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	for (int i = 0; i < 3; ++i) {
		for(char ch : ROWS[i]){
			rowcodes[i].insert((int)ch);
		}
	}

	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> buf;
		fill(rowc, rowc + 3, 0);

		for(char c : buf){
			for (int j = 0; j < 3; ++j) {
				if(rowcodes[j].count((int)c)){
					rowc[j] = 1;
					break;
				}
			}
		}

		int bufcnt = 0;
		for (int j = 0; j < 3; ++j) {
			if(rowc[j]){
				bufcnt++;
			}
		}

		if(bufcnt == 1){
			cnt++;
		}
	}

	printf("%d\n", cnt);
}

