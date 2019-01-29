//============================================================================
// Name        : CharacterAnalysis.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

string a, b;
unordered_map<char, int> amp, bmp;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> a >> b;

	for(char c : a){
		amp[c]++;
	}

	for(char c : b){
		bmp[c]++;
	}

	for(pair<char, int> p : amp){
		if(bmp[p.first] != p.second){
			printf("%c\n", p.first);
			return 0;
		}
	}

	for(pair<char, int> p : bmp){
		if(amp[p.first] != p.second){
			printf("%c\n", p.first);
			return 0;
		}
	}
}
