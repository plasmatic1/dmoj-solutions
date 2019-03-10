//============================================================================
// Name        : ccc19s3.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int INV = 0x3f3f3f3f, FILL_ORDER[9][2] = {{1, 1}, {0, 1}, {1, 2}, {2, 1}, {1, 0}, {0, 0}, {0, 2}, {2, 2}, {2, 0}};
int totunset = 0, fillptr = 0,
		grid[3][3];
string buf;

inline void fix(int &a, int &b, int &c){
	int unset = (a == INV) + (b == INV) + (c == INV);
	if(unset == 1){
		if(a == INV)
			a = b - (c - b);
		else if(b == INV)
			b = a + (c - a) / 2;
		else // c == inv
			c = b + (b - a);
	}
}

inline void fixGrid(){
	for (int i = 0; i < 3; ++i) {
		fix(grid[i][0], grid[i][1], grid[i][2]);
		fix(grid[0][i], grid[1][i], grid[2][i]);
	}
}

inline void printGrid(){
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			printf("%d ", grid[i][j]);
		}
		printf("\n");
	}
}

inline bool filledSquare(int x, int y){
	if(x < 0 || x > 2 || y < 0 || y > 2) return false;
	return grid[x][y] != INV;
}

inline bool isValidGrid(){
	for (int i = 0; i < 3; ++i) {
		// Row check
		if(grid[i][2] - grid[i][1] != grid[i][1] - grid[i][0])
			return false;

		// Col check
		if(grid[2][i] - grid[1][i] != grid[1][i] - grid[0][i])
			return false;
	}

	return true;
}

inline void addundo(vector<p> &undo, int x, int y){
	undo.push_back(make_pair(x, y));
}

inline void undo(vector<p> &undo){
	for(auto pa : undo)
		grid[pa.first][pa.second] = INV;
}

inline void fillRowOrCol(bool fillRow, vector<p> &sets){
	for (int i = 0; i < 2; ++i) {
		int val = grid[sets[i].first][sets[i].second];

		if(fillRow){
			for(int j = 0; j < 3; j++)
				grid[sets[i].first][j] = val;
		}
		else{
			for(int j = 0; j < 3; j++)
				grid[j][sets[i].second] = val;
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			cin >> buf;

			if(buf[0] == 'X'){
				grid[i][j] = INV;
				totunset++;
			}
			else{
				int tot = 0, sz = buf.length();
				bool neg = false;
				for(int i = 0; i < sz; i++){
					if(buf[i] == '-'){
						neg = true;
						continue;
					}
					tot *= 10;
					tot += (int)(buf[i] - '0');
				}
				if(neg)
					tot = -tot;

				grid[i][j] = tot;
			}
		}
	}

	if(totunset <= 3){
		for(int i = 0; i < 10; i++) fixGrid();
		printGrid();
	}
	else if(totunset == 7){
		vector<p> sets, unsets;
		for (int i = 0; i < 3; ++i){
			for (int j = 0; j < 3; ++j){
				if(grid[i][j] != INV)
					sets.push_back(make_pair(i, j));
				else
					addundo(unsets, i, j);
			}
		}


		bool fillRow = sets[0].first != sets[1].first; // Rows are different

		fillRowOrCol(fillRow, sets);
		fixGrid();

		if(fillRow && !isValidGrid()){
			undo(unsets);
			fillRowOrCol(false, sets);
			fixGrid();
		}

		printGrid();
	}
	else if(totunset == 8){
		int num = INV;
		for (int i = 0; i < 3; i++)
			for(int j = 0; j < 3; j++)
				num = min(num, grid[i][j]);

		printf("%d %d %d\n%d %d %d\n%d %d %d\n", num, num, num, num, num, num, num, num, num);
	}
	else if(totunset == 9)
		printf("8 9 10\n16 18 20\n24 27 30\n");
	else{ // Totunset is 4, 5, or 6
		// Fill in as much as possible
		for(int i = 0; i < 10; i++) fixGrid();

		// Search for best possible square to fill in
		while(!isValidGrid()){
			assert(fillptr < 9);
			const int* nextf = FILL_ORDER[fillptr++];
			while(filledSquare(nextf[0], nextf[1])) nextf = FILL_ORDER[fillptr++];
			grid[nextf[0]][nextf[1]] = 0;
			for(int i = 0; i < 10; i++) fixGrid();
		}

		printGrid();
	}
}
