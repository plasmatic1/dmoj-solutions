//============================================================================
// Name        : Poetry.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>
#include <locale>
using namespace std;

inline bool isAnyOf(char c){
	return (c == 'a' || c == 'o' || c == 'e' || c == 'i' || c == 'u');
}

int main() {
	int n;
	scanf("%d\n", &n);
	for(int i = 0; i < n; i++){
		string lines[4];
		for(int j = 0; j < 4; j++){
			string line;
			getline(cin, line);

			//by word
			int ces = 0, l = line.length();
			for(int k = 0; k < l; k++){
				if(line[k] == ' '){
					ces = k + 1;
				}
			}
			line = line.substr(ces, l - ces);
			l = line.length();
			ces = 0;
			transform(line.begin(), line.end(), line.begin(), ::tolower);
//			printf("got final word: %s\n", line.c_str());

			//by vowel
			for(int k = 0; k < l; k++){
				if(isAnyOf(line[k])){
					ces = k;
				}
			}
			line = line.substr(ces, l - ces);
//			printf("got ending: %s\n", line.c_str());

			lines[j] = line;
		}

		if(lines[0] == lines[1] && lines[1] == lines[2] && lines[2] == lines[3]){
			printf("perfect\n");
		}
		else if(lines[0] == lines[1] && lines[2] == lines[3]){
			printf("even\n");
		}
		else if(lines[0] == lines[2] && lines[1] == lines[3]){
			printf("cross\n");
		}
		else if(lines[0] == lines[3] && lines[1] == lines[2]){
			printf("shell\n");
		}
		else{
			printf("free\n");
		}
	}
	return 0;
}
