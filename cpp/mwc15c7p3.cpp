#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
 * Dear Reader,
 *
 * I'm writing this in response to CCC 2019.  Despite all the training I had gone through and high hopes and
 * encouragement from friends I tied with many others for a dismal score of 33.
 * Obviously, setting a cutoff that low would mean much too many people making CCO.
 *
 * I was excluded.
 *
 * After that, I developed depression.  I lost my will to do anything in life.
 *
 * Despite having worked so hard, I ended up choking at the worst possible time- right in the middle of the
 * CCC.  My heart goes out to everyone else who has or will suffer from the same fate.  To whom it may concern,
 * yes, I'm talking to you
 *
 * Moral of the story: If you train hard and practice well, but choke on the CCC and not make CCO, then your
 * hard work was just for nothing.
 *
 * ...
 *
 * What happens next is for you to decide
 *
 *  Read this if you want to feel better: https://dmoj.ca/problem/tle17c7p3/editorial
 *
 * ------------------------------------------------------------------------------------------------
 *
 * == vector<string> of Lost Souls: ==
 *
 * - Andrew Qi Tang, Erindale SS - 37/75
 * - Zeyu Chen, Colonel By SS - 37/75
 * - Andrew ? (not sure about last name), ?? - 36/75
 * - Aaron Tang, Churchill Heights PS - 37/75
 * - David Tsukernik, Stephen Lewis SS - 30/75
 * - Jonathan Sumabat, Thornhill SS - 27/75 (or was it 30?)
 * - Leon Dong, Bayview SS - 34/75
 * - Eric Pei, Don Mills CI - 41/75
 * -
 *
 * And many more... (sorry if I forgot you!)
 *
 * ~ M
 */

const int MAX = 20, MD = 101, INF = 0x3f3f3f3f;
int n, m, s, l, r, ii, beg = 0, tot = 0,
	dist[1 << MAX];
string buf;
bool vis[1 << MAX];
deque<int> nxt;

inline int left(int mask){
	return ((mask << 1) & ~(1 << n)) + (mask >> (n - 1));
}

inline int right(int mask){
	return (mask >> 1) + ((mask & 1) << (n - 1));
}

inline int swap(int mask, int i){
	return mask ^ (1 << i);
}

inline int inv(int mask){
	return ~mask & ((1 << n) - 1);
}

inline void attemptadd(int adj, int alt){
	if(alt > m) return;

	if(alt < dist[adj]){
		if(!vis[adj])
			nxt.push_back(adj);
		vis[adj] = true;
		dist[adj] = alt;
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> m >> s >> l >> r >> ii >> buf;

	for (int i = 0; i < n; ++i) {
		beg <<= 1;
		beg += buf[i] == 'B';
	}

	memset(dist, 0x3f, sizeof dist);
	dist[beg] = 0;
	vis[beg] = true;
	nxt.push_back(beg);

	while(!nxt.empty()){
		int v = nxt.front(), w = dist[v];
		nxt.pop_front();
		vis[v] = false;

		for (int i = 0; i < n; ++i)
			attemptadd(swap(v, i), w + s);

		attemptadd(left(v), w + l);
		attemptadd(right(v), w + r);
		attemptadd(inv(v), w + ii);
	}

	int msub = 1 << n;
	for (int i = 0; i < msub; ++i)
		tot += dist[i] <= m;

	printf("%d\n", tot);
}
