//============================================================================
// Name        : coci16c1p2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct p{
	int x, y;
};

// Scan and Debug
void scan(){}
template<typename F, typename... R> void scan(F &f,R&... r){cin>>f;scan(r...);}
int di_; string dnms_, co_ = ",";
void debug_(){cout<<endl;}
template<typename F, typename... R> void debug_(F &f, R&... r){string s;while(dnms_[di_] != ',')s+=dnms_[di_++];di_++;cout<<s<<": "<<f<<",";debug_(r...);}
#define debug(...) dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__)

const int MAX = 100001;
int n;
char grid[10][MAX];
deque<p> nxt;
p par[10][MAX], adjs[2];
bool vis[10][MAX];

inline void makeadj(p &cur){
	int sz = 0;

	if(cur.x == 0)
		adjs[sz++] = {cur.x, cur.y + 1};
	else
		adjs[sz++] = {cur.x - 1, cur.y + 1};

	if(cur.x == 9)
		adjs[sz++] = {cur.x, cur.y + 1};
	else
		adjs[sz++] = {cur.x + 1, cur.y + 1};
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	scan(n);

	for(int i = 0; i < 10; i++)
		scan(grid[10 - i - 1]);

	nxt.push_back({0, 0});
	vis[0][0] = true;
	par[0][0] = {-1, -1};

	while(!nxt.empty()){
		p cur = nxt.front();
		nxt.pop_front();

		makeadj(cur);
		for(p adj : adjs){
			if(adj.y >= n || vis[adj.x][adj.y] || grid[adj.x][adj.y] == 'X')
				continue;

			vis[adj.x][adj.y] = true;
			par[adj.x][adj.y] = cur;
			nxt.push_back(adj);
		}
	}

	// Reconstruct path

	int endX = -1;
	for(int i = 0; i < 10; i++){
		if(vis[i][n - 1]){
			endX = i;
			break;
		}
	}

	vector<p> path;
	p cur = {endX, n - 1};

	while(cur.x != -1 && cur.y != -1){
		path.push_back(cur);
		cur = par[cur.x][cur.y];
	}
	reverse(path.begin(), path.end());

	int sz = path.size();
	bool up[sz];
	memset(up, false, sizeof up);

	for(int i = 1; i < sz; i++){
		if(path[i].x == 9 && path[i - 1].x == 9)
			up[i] = true;
		else if(path[i].x > path[i - 1].x)
			up[i] = true;
	}

	// Streak counting
	vector<p> streaks; // x = time, y = duration
	int last = -1;
	for(int i = 1; i < sz; i++){
		if(up[i])
			if(last == -1)
				last = i;
		if(!up[i]){
			if(last != -1)
				streaks.push_back({last - 1, i - last});
			last = -1;
		}
	}


	if(last != -1)
		streaks.push_back({last - 1, n - last});

	sz = streaks.size();
	printf("%d\n", sz);
	for(p streak : streaks)
		printf("%d %d\n", streak.x, streak.y);
}
