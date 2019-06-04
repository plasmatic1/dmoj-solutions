//============================================================================
// Name        : gfssoc2s5.cpp
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
template<typename F, typename... R> void debug_(F f,R... r){while(dnms_[di_] != ',')cout<<dnms_[di_++];di_++;cout<<": "<<f<<",";debug_(r...);}
#define debug(...) dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__)

const int MAX = 500001, MOD = 1000000007;
int n, m, ba, bb,
    loot[MAX], to[MAX], toLoot[MAX], ord[MAX], low[MAX];
vector<int> matrix[MAX], matrix2[MAX];
bool vis[MAX], inStk[MAX];
stack<int> stk;

int curOrd = -1;
void tarjan(int cur) {
    stk.push(cur);
    vis[cur] = inStk[cur] = true;
    ord[cur] = low[cur] = ++curOrd;

    for (int adj : matrix[cur]) {
        if (!vis[adj]) {
            tarjan(adj);
            low[cur] = min(low[cur], low[adj]);
        }
        else if (inStk[adj])
            low[cur] = min(low[cur], ord[adj]);
    }

    // If root of SCC
    if (low[cur] == ord[cur]) {
        int st = -1, v = -1;
        do {
            v = stk.top(); stk.pop(); inStk[v] = false;

            if (st == -1)
                st = v;
            to[v] = st;
        }
        while (v != cur);
    }
}

int dpTot[MAX][2], dpCnt[MAX][2];

pair<int, int> rec(int cur, bool tookPar) {
    int &retTot = dpTot[cur][tookPar], &retCnt = dpCnt[cur][tookPar];
    if (cur == to[n]) return make_pair(tookPar ? 0 : toLoot[to[n]], 1);
    if (retTot != -1) return make_pair(retTot, retCnt);
    retTot = 0; // Retcnt is already 0

    int best = 0, bestWays = 1;
    for (int adj : matrix2[cur]) {
        auto noTake = rec(adj, false), take = rec(adj, true);
        take.first += toLoot[cur];

        if (noTake.first > best) {
            best = noTake.first;
            bestWays = noTake.second;
        }
        else if (noTake.first == best)
            bestWays = (bestWays + noTake.second) % MOD;

        if (!tookPar) {
            if (take.first > best) {
                best = take.first;
                bestWays = take.second;
            }
            else if (take.first == best)
                bestWays = (bestWays + take.second) % MOD;
        }
    }
    retTot = best; retCnt = bestWays;

//    debug(cur, tookPar, retTot, retCnt);

    return make_pair(retTot, retCnt);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

    scan(n, m);

    for (int i = 1; i <= n; i++)
        scan(loot[i]);

    for (int i = 0; i < m; i++) {
        scan(ba, bb);
        matrix[ba].push_back(bb);
    }

    // Do Tarjan
    iota(to + 1, to + n + 1, 1);
    for (int i = 1; i <= n; i++)
        if (!vis[i])
            tarjan(i);

    for (int i = 1; i <= n; i++)
        toLoot[to[i]] += loot[i];

    for (int i = 1; i <= n; i++)
    	for (int adj : matrix[i])
    		if (to[i] != to[adj])
    			matrix2[to[i]].push_back(to[adj]);
    for (int i = 1; i <= n; i++) {
    	sort(matrix2[i].begin(), matrix2[i].end());
    	matrix2[i].resize(unique(matrix2[i].begin(), matrix2[i].end()) - matrix2[i].begin());
    }

//    printf("to: [");
//	for (int i = 0; i < n + 1; i++)
//		printf("%d, ", to[i]);
//	printf("]\n");
//	printf("toLoot: [");
//	for (int i = 0; i < n+1; i++)
//		printf("%d, ", toLoot[i]);
//	printf("]\n");

    // Do DP
    memset(dpTot, -1, sizeof dpTot);
    auto ret = rec(to[1], false);
    cout << ret.first << " " << ret.second << "\n";

    return 0;
}