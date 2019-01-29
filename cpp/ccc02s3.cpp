//============================================================================
// Name        : Blindfold.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cstdio>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <set>

using namespace std;

typedef pair<int, int> p;

struct plessthan{
	bool operator()(const p &a, const p &b) const {
		if(a.first == b.first){
			return a.second < b.second;
		}
		return a.first < b.first;
	}
};

int main() {
	int r, c, q; //0 = none, 1 = wall, 2 = endpoint
	vector<p> starts;
	set<p, plessthan> ends;
	scanf("%d", &r);
	scanf("%d", &c);
	int grid[r][c];

//	printf("got width and height input\n");

	for(int i = 0; i < r; i++){
//		printf("on line %d\n", i);
		char line[c];
		scanf("%s", line);
//		printf("got line\n");
		for(int j = 0; j < c; j++){
			char cc = line[j];
//			printf("got char from line\n");
			if(cc == 'X'){
				grid[i][j] = 1;
			}
			else{
				grid[i][j] = 0;
				starts.push_back(p(j, i));
			}
			//false setting redundant
		}
	}

//	printf("accepted grid input\n");

	//left = 0, forward = 1, right = 2, 3 is back (only used in one case)
	scanf("%d", &q);
	int ds[q];
	for(int i = 0; i < q; i++){
		char d[1];
		scanf("%s", d);
		if(d[0] == 'F'){
			ds[i] = 1;
		}
		else if(d[0] == 'R'){
			ds[i] = 2;
		}
		else{
			ds[i] = 0;
		}
	}

//	printf("accepted all input\n");

	int x, y, d;
	for(p start : starts){
		for(int i = 0; i < 4; i++){
			d = i;
			x = start.first;
			y = start.second;
//			printf("on start %d, %d (dir %d)\n", x, y, d);
			for(int j = 0; j < q; j++){
				int a = ds[j];
//				printf("instruction %d, query is %d\n", j, a);
				if(a == 0){
					if(d > 0){
						d--;
					}
					else{
						d = 3;
					}
				}
				else if(a == 2){
					if(d < 3){
						d++;
					}
					else{
						d = 0;
					}
				}
				else{
					if(d == 0){
						x--;
					}
					else if(d == 1){
						y--;
					}
					else if(d == 2){
						x++;
					}
					else if(d == 3){
						y++;
					}

//					printf("grid patt for %d, %d: %d\n", x, y, grid[y][x]);

					if(x < 0 || x > (c - 1) || y < 0 || y > (r - 1) || grid[y][x] == 1){
//						printf("requirements not met! on query %d\n", j);
						break;
					}
				}

				if(j == (q - 1)){
//					printf("\t\t\t\tinserting %d, %d\n", x, y);
					ends.insert(p(x, y));
				}
			}
		}
	}

	for(p end : ends){
//		printf("There is end %d, %d\n", end.first, end.second);
		grid[end.second][end.first] = 2;
	}

	for(int i = 0; i < r; i++){
		string line;
		for(int j = 0; j < c; j++){
			int x = grid[i][j];
//			printf("(%d, %d) x is %d\n", i, j, x);
			if(x == 0){
				line += '.';
			}
			else if(x == 1){
				line += 'X';
			}
			else if(x == 2){
				line += '*';
			}
		}
		printf("%s\n", line.c_str());
	}

	return 0;
}
