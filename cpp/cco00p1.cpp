//============================================================================
// Name        : Subsets.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const char LOWER_MAX = 'z', LOWER_MIN = 'a', DIFF = 'a' - 'A', UPPER_MIN = 'A', UPPER_MAX = 26 + UPPER_MIN;

int n, buf;
string dev_null; //haha linux
char a, b;

map<char, vector<char>> sets, matrix;
//bool letterTotals[26][26]
bool visited[26], existing_sets[26], in_set[26];

//bool* dfs(char curr){
//	int letterIndex = curr - UPPER_MIN;
//
//	if(visited[letterIndex]){`
//		return letterTotals[letterIndex];
//	}
//	visited[letterIndex] = true;
//
//	for(char adj : matrix[curr]){
//		int adjLetterIndex = adj - UPPER_MIN;
//		if(visited[adjLetterIndex]){
//			continue;
//		}
//
//		//
//	}
//}

void bfs(char start){
	queue<char> next;
	fill(visited, visited + 26, false);
	fill(in_set, in_set + 26, false);

	next.push(start);

	for(char chh : sets[start]){
		in_set[(int)(chh - LOWER_MIN)] = true;
	}

	while(!next.empty()){
		char curr = next.front();
		next.pop();

//		printf("-- curr %c\n", curr);

		for(char adj : matrix[curr]){
			if(visited[(int)(adj - UPPER_MIN)]){
//				printf(" visited already %c\n", adj);
				continue;
			}
//			printf(" adj %c\n", adj);

			for(char ch : sets[adj]){
				in_set[(int)(ch - LOWER_MIN)] = true;
			}
			visited[(int)(adj - UPPER_MIN)] = true;
			next.push(adj);
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	fill(existing_sets, existing_sets + 26, false);

	//Init map 'sets'
	for(char c = 'A'; c <= 'Z'; c++){
		vector<char> v, w;
		sets[c] = v;
		matrix[c] = w;
	}

	for (int i = 0; i < n; ++i) {
		cin >> a >> dev_null >> b;

		if(b > UPPER_MAX){
			sets[a].push_back(b);
		}
		else{
			matrix[a].push_back(b);
			existing_sets[(int)(b - UPPER_MIN)] = true;
		}
		existing_sets[(int)(a - UPPER_MIN)] = true;
	}

	for(int i = 0; i < 26; i++){
		if(existing_sets[i]){
			bfs((char)(i + UPPER_MIN));
			bool first = true;

			printf("%c = {", i + UPPER_MIN);
			for (int j = 0; j < 26; ++j) {
				if(in_set[j]){
					if(first){
						printf("%c", j + LOWER_MIN);
						first = false;
					}
					else{
						printf(",%c", j + LOWER_MIN);
					}
				}
			}
			printf("}\n");
		}
	}
}
