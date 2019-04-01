//============================================================================
// Name        : dmpg18s3.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 2001;
int n, m;
bitset<MAX> gridBit[MAX];
string buf;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> m;

	for (int i = 0; i < n; ++i) {
		cin >> buf;
		string fixBuf;

		for(int j = 0; j < m; j++)
			fixBuf += buf[j] == '#' ? "1" : "0";
		gridBit[i] = bitset<MAX>(fixBuf);
	}

	for (int i = 0; i < n; ++i) {
		for(int j = i + 1; j < n; ++j){
			if((gridBit[i] & gridBit[j]).count() >= 2){
				printf("no\n");
				return 0;
			}
		}
	}

	printf("yes\n");
}

