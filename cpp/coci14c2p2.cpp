//============================================================================
// Name        : Utrka.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <utility>

using namespace std;

typedef pair<string, int> p;

int main() {
	int n, n0;
	map<string, int> racers;

	scanf("%d\n", &n);
	n0 = n - 1;

	for(int i = 0; i < n; i++){
		string name;
		getline(cin, name);

		if(racers.find(name) == racers.end()){
			racers.insert(p(name, 0));
		}
		else{
			racers[name]--;
		}
	}

	for(int i = 0; i < n0; i++){
		string name;
		getline(cin, name);

		racers[name]++;
	}

	for(p np : racers){
		if(np.second < 1){
			printf("%s\n", np.first.c_str());
			break;
		}
	}
}
