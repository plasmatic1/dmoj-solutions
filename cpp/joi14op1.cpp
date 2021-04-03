//============================================================================
// Name        : joi14p1.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#pragma GCC optimize "Ofast"
#pragma GCC optimize "unroll-loops"
#pragma GCC target "sse,sse2,sse3,sse4,abm,avx,mmx,popcnt,tune=native"

#include "factories.h"
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

const int MAX = 500001;

struct ed {
	int v, w;
};

vector<ed> matrix[MAX];
const ll INF = 0x3f3f3f3f3f3f3f3f;
int N,
	sz[MAX], par[MAX], lv[MAX];
bool blocked[MAX];
ll bestFor[MAX], dis[MAX][23];

int gsz(int cur, int par) {
	sz[cur] = 1;
	for (ed adj : matrix[cur])
		if ((adj.v ^ par) && !blocked[adj.v])
			sz[cur] += gsz(adj.v, cur);
	return sz[cur];
}

int gcentroid(int cur, int par, int half) {
	for (ed adj : matrix[cur])
		if ((adj.v ^ par) && !blocked[adj.v] && sz[adj.v] > half)
			return gcentroid(adj.v, cur, half);
	return cur;
}

struct tnxt {
	int nxt, par;
	ll dis;
};

tnxt nxt[MAX];
int nxtPtr = -1;

int decomp(int cur=0, int __par=-1) {
	gsz(cur, __par);
	if (sz[cur] == 1) {// If size is one, centroid is self
		dis[cur][++lv[cur]] = 0;
		return cur;
	}

	int centroid = gcentroid(cur, __par, sz[cur] >> 1);
	blocked[centroid] = true;

	dis[centroid][++lv[centroid]] = 0;
	nxt[++nxtPtr] = {centroid, -1, 0};
	while (nxtPtr >= 0) {
		tnxt cur = nxt[nxtPtr]; nxtPtr--;
		for (ed adj : matrix[cur.nxt]) {
			if ((adj.v ^ cur.par) && !blocked[adj.v]) {
				nxt[++nxtPtr] = {adj.v, cur.nxt, cur.dis + adj.w};
				dis[adj.v][++lv[adj.v]] = nxt[nxtPtr].dis;
			}
		}
	}

	for (ed adj : matrix[centroid])
		if (!blocked[adj.v])
			par[decomp(adj.v, centroid)] = centroid;

	return centroid;
}

// Grader Functions
void Init(int N_, int A[], int B[], int D[]) {
	N = N_;
	for (int i = 0; i < N - 1; i++) {
		matrix[A[i]].push_back({B[i], D[i]});
		matrix[B[i]].push_back({A[i], D[i]});
	}

	// Init Centroid Tree
	memset(lv, -1, sizeof lv);
	par[decomp()] = -1;
	memset(bestFor, 0x3f, sizeof bestFor);
}

int back[20000001], backSz = 0;

long long Query(int S, int X[], int T, int Y[]) {
	ll best = INF;
	backSz = 0;

	if (S < T) {
		for (int i = 0; i < S; i++) {
			for (int cur = X[i], clv = lv[cur]; clv >= 0; cur = par[cur], clv--) {
				bestFor[cur] = min(bestFor[cur], dis[X[i]][clv]);
					back[backSz++] = cur;
			}
		}

		for (int i = 0; i < T; i++)
			for (int cur = Y[i], clv = lv[cur]; clv >= 0; cur = par[cur], clv--)
				best = min(best, dis[Y[i]][clv] + bestFor[cur]);
	}
	else{
		for (int i = 0; i < T; i++) {
			for (int cur = Y[i], clv = lv[cur]; clv >= 0; cur = par[cur], clv--) {
				bestFor[cur] = min(bestFor[cur], dis[Y[i]][clv]);
					back[backSz++] = cur;
			}
		}

		for (int i = 0; i < S; i++)
			for (int cur = X[i], clv = lv[cur]; clv >= 0; cur = par[cur], clv--)
				best = min(best, dis[X[i]][clv] + bestFor[cur]);
	}

	for (int i = 0; i < backSz; i++)
		bestFor[back[i]] = INF;

	return best;
}