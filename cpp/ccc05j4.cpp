//============================================================================
// Name        : ccc05j4.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Scan and Debug
void scan(){}
template<typename F, typename... R> void scan(F &f,R&... r){cin>>f;scan(r...);}
int di_; string dnms_, co_ = ",";
void debug_(){cout<<endl;}
template<typename F, typename... R> void debug_(F f, R... r){while(dnms_[di_] != ',')cout<<dnms_[di_++];di_++;cout<<": "<<f<<",";debug_(r...);}
#define debug(...) dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__)

const int MAX = 51, MD = 201;
int c, r, badC, badR, steps;
bool bad[MAX][MAX], turn[MAX][MAX];
queue<int> dirs;

void move(int &curR, int &curC, int dir) {
	switch (dir) {
	case 0: // Right
		curC++;
		break;
	case 1: // Down
		curR++;
		break;
	case 2: // Left
		curC--;
		break;
	case 3: // Up
		curR--;
		break;
	}
}

void invertDir(int &dir) { dir = (dir + 2) % 4; }
void changeDir(int &dir, int amt) { dir = (dir + amt) % 4; }

bool badPos(int cr, int cc) { return cr < 0 || cr >= r || cc < 0 || cc >= c || bad[cr][cc]; }
bool isStuck(int cr, int cc) { return badPos(cr - 1, cc) && badPos(cr + 1, cc) && badPos(cr, cc - 1) && badPos(cr, cc + 1); }

void nextDir(int &curR, int &curC, int &dir) {
	changeDir(dir, dirs.front());
	dirs.pop();
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	dirs.push(1); dirs.push(3);
	while (dirs.size() < MD) {
		dirs.push(1); dirs.push(1); dirs.push(3);
	}

	scan(c, r, badC, badR, steps);

	// Making bad shit
	for (int i = 0; i < badR; i++) {
		for (int j = 0; j < badC; j++)
			bad[i][j] = true;
		for (int j = c - 1; j >= c - badC; j--)
			bad[i][j] = true;
	}

	for (int i = r - 1; i >= r - badR; i--) {
		for (int j = 0; j < badC; j++)
			bad[i][j] = true;
		for (int j = c - 1; j >= c - badC; j--)
			bad[i][j] = true;
	}

	int mid = c >> 1;
	for (int cr = badR, cc = badC; cc <= mid; cr++, cc++)
		turn[cr][cc] = turn[r - cr - 1][cc] = true;
	for (int cr = badR, cc = c - badC - 1; cc >= mid; cr++, cc--)
		turn[cr][cc] = turn[r - cr - 1][cc] = true; //, debug(cr, cc, r - cr, cc);

	// Walk
	int curR = 0, curC = badC, dir = 0;
	bad[curR][curC] = true;
//	debug(curR, curC, dir);

	while (steps--) {
		if (isStuck(curR, curC))
			break;

		move(curR, curC, dir);

		if (curR < 0 || curR >= r || curC < 0 || curC >= c || bad[curR][curC]) { // Have to backtrack and switch direction
			invertDir(dir);
			move(curR, curC, dir);
			invertDir(dir);

			nextDir(curR, curC, dir);
			move(curR, curC, dir);
		}
		else if (turn[curR][curC])
			nextDir(curR, curC, dir);

//		debug(curR, curC, dir, steps);
		bad[curR][curC] = true;
	}

	cout << curC + 1 << "\n" << curR + 1 << "\n";

	return 0;
}