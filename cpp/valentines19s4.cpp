//============================================================================
// Name        : valentines19s4.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct t{
	int l, r, i;

	bool operator<(const t &o) const {
		if(l == o.l)
			return r < o.r;
		return l < o.l;
	}
};

const int MAX = 100001;
int n, k;
t tasks[MAX];
vector<t> discarded, used;

int runfor(vector<int> &ret){
	vector<t> tasksfor[n + 1];

	int dptr = 0, dsz = discarded.size();
	for(t task : used){
		while(dptr < dsz && discarded[dptr].l <= task.r){
			if(discarded[dptr].r <= task.r)
				tasksfor[task.i].push_back(discarded[dptr]);
			dptr++;
		}
	}

	for(t task : used){
		vector<t> &ava = tasksfor[task.i]; // ava = available
		int asz = ava.size();
		if(asz <= 1) continue;

		int lastMax = -1, best = 0;
		for (int i = 0; i < asz; ++i) {
			if(ava[i].l > lastMax){
				lastMax = ava[i].r;
				best++;
			}
			else if(ava[i].r < lastMax)
				lastMax = ava[i].r;
		}

		ret.push_back(best);
	}

	sort(ret.begin(), ret.end());
	return (int)ret.size();
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> k;

	for (int i = 0; i < n; ++i)
		cin >> tasks[i].l >> tasks[i].r;
	sort(tasks, tasks + n);

	for(int i = 0; i < n; i++)
		tasks[i].i = i;

	int currR = 0, gbest = 0;
	for (int i = 0; i < n; ++i) {
		if(tasks[i].l > currR){
			currR = tasks[i].r;
			gbest++;
			used.push_back(tasks[i]);
		}
		else
			discarded.push_back(tasks[i]);
	}

	vector<t> tmpused = used;
	used.clear();
	int lastR = -2, usz = tmpused.size();
	for (int i = 0; i < usz; ++i) {
		int nextL = -1;
		if(i + 1 < usz) nextL = tmpused[i + 1].l - 1;
		else nextL = INT_MAX;

		used.push_back({lastR + 1, nextL, tmpused[i].i});

		lastR = tmpused[i].r;
	}

	if(k == 1){
		vector<int> rets;
		runfor(rets);
		if(rets.empty())
			rets.push_back(1);
		int rsz = rets.size();

		printf("%d\n", gbest - 1 + rets[rsz - 1]);
	}
	else{
		vector<int> retssep;
		runfor(retssep);
		while(retssep.size() < 2)
			retssep.push_back(1);
		int rsz = retssep.size();

		used.clear();
		lastR = -2;
		usz = tmpused.size();
		for (int i = 1; i < usz; ++i) {
			int nextL = -1;
			if(i + 1 < usz) nextL = tmpused[i + 1].l - 1;
			else nextL = INT_MAX;

			used.push_back({lastR + 1, nextL, tmpused[i].i});

			lastR = tmpused[i - 1].r;
		}

		vector<int> retscomb;
		runfor(retscomb);
		if(retscomb.empty())
			retscomb.push_back(2);
		int rsz2 = retscomb.size();

		printf("%d\n", gbest - 2 +
				max(retssep[rsz - 1] + retssep[rsz - 2], retscomb[rsz2 - 1]));
	}
}
