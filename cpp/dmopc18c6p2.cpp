//============================================================================
// Name        : dmopc18c6p2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

string a[4], b[4], tmp[3];
unordered_map<string, int> cnta, cntb;
bool isSame = false, isMirror = false;

inline bool sameAs(){
	bool flag = true;

	for(int i = 0; i < 3; i++)
		flag &= a[i + 1] == tmp[i];

	return flag;
}

inline bool reverseAs(){
	bool flag = true;

	for(int i = 0; i < 3; i++)
		flag &= tmp[i] == a[3 - i];

	return flag;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	for (int i = 0; i < 4; ++i)
		cin >> a[i], cnta[a[i]]++;
	for (int i = 0; i < 4; ++i)
		cin >> b[i], cntb[b[i]]++;

	for(auto entry : cnta){
		if(entry.second != cntb[entry.first]){
			printf("NO\n");
			return 0;
		}
	}

	for (int i = 0; i < 4; ++i) {
		// Check bottom 3
		vector<string> bot;
		for(int j = 0; j < 4; j++)
			if(j != i)
				bot.push_back(b[j]);

		if(i % 2)
			reverse(bot.begin(), bot.end());

		// Start from 0, 1, or 2
		for (int j = 0; j < 3; ++j) {
			for (int k = 0; k < 3; ++k)
				tmp[(k + j) % 3] = bot[k];

//			printf("i=%d j=%d\n", i, j);
//			printf("tmp: ");
//			for(int k = 0; k < 3; k++)
//				printf("%s, ", tmp[k].c_str());
//			printf("\n");

			isSame |= sameAs();
			isMirror |= reverseAs();
		}
	}

//	printf("s=%d, m=%d\n", isSame, isMirror);

	if(isMirror && !isSame)
		printf("YES\n");
	else
		printf("NO\n");
}