//============================================================================
// Name        : valentines19s1.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 10001, MN = 21;
int n, m, ba;
unordered_map<string, int> conv;
string buf;
deque<int> choices[MAX];
string backconv[MN];
vector<int> votes[MN];
bool eliminated[MN];

int majority(){
	int tot = 0, best = 0, besti = -1;
	for (int i = 0; i < n; ++i) {
		if(eliminated[i]) continue;

		int ccnt = votes[i].size();
		tot += ccnt;

		if(ccnt > best){
			best = ccnt;
			besti = i;
		}
	}

	assert(tot > 0);
	if(best == tot) return besti;
	return -1;
}

void countvotes(){
	for (int i = 0; i < n; ++i)
		votes[i].clear();

	for (int i = 0; i < m; ++i) {
		if(!choices[i].empty()){
			int want = choices[i].front();

			while(want != -1 && eliminated[want]){
				choices[i].pop_front();
				if(!choices[i].empty())
					want = choices[i].front();
				else
					want = -1;
			}

			if(want != -1)
				votes[want].push_back(i);
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	int counter = 0;
	for (int i = 0; i < n; ++i) {
		cin >> buf;
		backconv[counter] = buf;
		conv[buf] = counter++;
	}

	for (int i = 0; i < m; ++i) {
		cin >> ba;

		for (int j = 0; j < ba; ++j) {
			cin >> buf;
			choices[i].push_back(conv[buf]);
		}
	}

	countvotes();
	int maj = majority();
	while(maj == -1){
//		for (int i = 0; i < n; ++i) {
//			printf("%d: ", i);
//			for(int vo : votes[i]) printf("%d, ", vo);
//			printf("\n");
//		}

		int minv = INT_MAX, mini = -1;
		for (int i = 0; i < n; ++i) {
			if(eliminated[i]) continue;

			int ccnt = votes[i].size();
			if(ccnt < minv){
				minv = ccnt;
				mini = i;
			}
		}

//		printf("pop val=%d\n", mini);

		for(int voter : votes[mini])
			if(!choices[voter].empty())
				choices[voter].pop_front();
		eliminated[mini] = true;

		countvotes();
		maj = majority();
	}

	printf("%s\n", backconv[maj].c_str());
}
