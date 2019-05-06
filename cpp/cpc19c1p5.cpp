//============================================================================
// Name        : cpc18c1p5.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
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
template<typename F, typename... R> void debug_(F &f, R&... r){while(dnms_[di_] != ',')cout<<dnms_[di_++];di_++;cout<<": "<<f<<",";debug_(r...);}
#define debug(...) dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__)

struct p {
	int t;
	ll st;
};

const int MK = 10001, MQ = 100001, MST = 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9;
int n, m, k, q,
	arrange[3][4];
ll beginStates[MK], endStates[MQ], adjs[4];

inline ll getState() {
	ll state = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			state = (state << 4) | arrange[i][j];
	return state;
}

inline void setState(ll state) {
	for (int i = n - 1; i >= 0; i--) {
		for (int j = m - 1; j >= 0; j--) {
			arrange[i][j] = state & 15;
			state >>= 4;
		}
	}
}

// Returns size of adj
inline int makeAdj() {
	int zx = -1, zy = -1, sz = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (arrange[i][j] == 0) {
				zx = i;
				zy = j;
			}
		}
	}

	if (zx < n - 1) { // Can switch with zx + 1
		swap(arrange[zx][zy], arrange[zx + 1][zy]);
		adjs[sz++] = getState();
		swap(arrange[zx][zy], arrange[zx + 1][zy]);
	}
	if (zx > 0) { // Can switch with zx - 1
		swap(arrange[zx][zy], arrange[zx - 1][zy]);
		adjs[sz++] = getState();
		swap(arrange[zx][zy], arrange[zx - 1][zy]);
	}
	if (zy < m - 1) { // Can switch with zy + 1
		swap(arrange[zx][zy], arrange[zx][zy + 1]);
		adjs[sz++] = getState();
		swap(arrange[zx][zy], arrange[zx][zy + 1]);
	}
	if (zy > 0) { // Can switch with zy - 1
		swap(arrange[zx][zy], arrange[zx][zy - 1]);
		adjs[sz++] = getState();
		swap(arrange[zx][zy], arrange[zx][zy - 1]);
	}

	return sz;
}

inline void bfsSubtask5() {
	unordered_map<ll, int> vis[2];
	unordered_map<ll, bool> player;
	deque<p> nxt;

	nxt.push_back({1, endStates[0]});

	nxt.push_back({0, beginStates[0]});
	player[beginStates[0]] = 0;
	if (beginStates[1] != beginStates[0]) {
		nxt.push_back({0, beginStates[1]});
		player[beginStates[1]] = 1;
	}

	vis[0][beginStates[0]] = vis[0][beginStates[1]] = vis[1][endStates[0]] = 0;

	int bestLevel[2], bestDis = 0x3f3f3f3f, winner = -1;
	bestLevel[0] = bestLevel[1] = 0x3f3f3f3f;

	while(!nxt.empty()) {
		p cur = nxt.front();
		nxt.pop_front();
		int level = vis[cur.t][cur.st], cPlayer = cur.t == 0 ? player[cur.st] : -1;

		if(level >= bestLevel[cur.t])
			continue;

		setState(cur.st);
		int sz = makeAdj();
		bool bk = false;
		for (int i = 0; i < sz; i++) {
			ll &adj = adjs[i];

			if (vis[!cur.t].find(adj) != vis[!cur.t].end()) {
				int beginDis = cur.t ? vis[!cur.t][adj] : vis[cur.t][cur.st];
				int endDis = (cur.t ? vis[cur.t][cur.st] : vis[!cur.t][adj]) + 1;
				int cDis = beginDis + endDis;

				if(cDis <= bestDis) {
					bestLevel[0] = beginDis;
					bestLevel[1] = endDis;
					bestDis = cDis;
				}
				else
					continue;

				int cWinner = -1;
				if (cur.t)
					cWinner = player[adj];
				else
					cWinner = cPlayer;

				if (cWinner == 0) {
					winner = 0;
					bk = true;
					break;
				}
				else
					winner = 1;
			}
			if (vis[cur.t].find(adj) == vis[cur.t].end()) {
				if (cur.t == 0)
					player[adj] = cPlayer;
				vis[cur.t][adj] = level + 1;
				nxt.push_back({cur.t, adj});
			}
		}

		if (bk)
			break;
	}

	printf("%d %d\n", winner + 1, bestDis);
}

// Subtask 1 to 4
unordered_map<ll, int> ranks;
int rankPtr = -1,
		player[MST], levels[MST];
deque<ll> nxt;

inline int insertState(ll state) {
	if (ranks.find(state) == ranks.end())
		return ranks[state] = ++rankPtr;
	return ranks[state];
}

inline void bfsNormal() {
	memset(levels, -1, sizeof levels);

	for (int i = 0; i < k; i++) {
		nxt.push_back(beginStates[i]);
		int rank = insertState(beginStates[i]);
		if (levels[rank] == -1) {
			player[rank] = i;
			levels[rank] = 0;
		}
	}

	while(!nxt.empty()) {
		ll cur = nxt.front();
		nxt.pop_front();
		int rank = ranks[cur], level = levels[rank], cPlayer = player[rank];

		setState(cur);
		int sz = makeAdj();
		for (int i = 0; i < sz; i++) {
			ll &adj = adjs[i];
			int adjRank = insertState(adj);

			if(levels[adjRank] == -1) {
				levels[adjRank] = level + 1;
				player[adjRank] = cPlayer;
				nxt.push_back(adj);
			}
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	scan(n, m, k, q);

	for (int i = 0; i < k; i++) {
		for (int j = 0; j < n; j++)
			for (int l = 0; l < m; l++)
				scan(arrange[j][l]);
		beginStates[i] = getState();
	}

	for (int i = 0; i < q; i++) {
		for (int j = 0; j < n; j++)
			for (int l = 0; l < m; l++)
				scan(arrange[j][l]);
		endStates[i] = getState();
	}

	if (n == 3 && m == 4) {
		if (beginStates[0] == endStates[0]) {
			printf("1 0\n");
			return 0;
		}
		else if(beginStates[1] == endStates[0]) {
			printf("2 0\n");
			return 0;
		}

		bfsSubtask5();
	}
	else {
		bfsNormal();

		for (int i = 0; i < q; i++) {
			int rank = ranks[endStates[i]];
			printf("%d %d\n", player[rank] + 1, levels[rank]);
		}
	}
}