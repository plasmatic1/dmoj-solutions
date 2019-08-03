//============================================================================
// Name        : quiz51.cpp
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

struct p{
	int x, y;
};

const int MAX = 501;
int n,
	grid[MAX][MAX];
deque<p> nxt;
bool vis[MAX][MAX];
p adjs[4];

inline void makeadj(p v){
	adjs[0] = {v.x - 1, v.y};
	adjs[1] = {v.x + 1, v.y};
	adjs[2] = {v.x, v.y - 1};
	adjs[3] = {v.x, v.y + 1};
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	scan(n);

	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			scan(grid[i][j]);

	if(grid[0][0]){
		printf("no\n");
		return 0;
	}

	vis[0][0] = true;
	nxt.push_back({0, 0});

	while(!nxt.empty()){
		p cur = nxt.front();
		nxt.pop_front();

		makeadj(cur);
		for(p adj : adjs){
			if(adj.x < 0 || adj.x >= n || adj.y < 0 || adj.y >= n || grid[adj.x][adj.y] ||
					vis[adj.x][adj.y]){
				continue;
			}

			vis[adj.x][adj.y] = true;
			nxt.push_back({adj.x, adj.y});
		}
	}

	if(vis[n - 1][n - 1])
		printf("yes\n");
	else
		printf("no\n");
}