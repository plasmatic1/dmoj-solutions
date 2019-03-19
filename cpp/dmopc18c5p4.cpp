//============================================================================
// Name        : dmopc18c5p4.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n;
string a, b, basea, baseb;

inline void base(string &begin, string &base){
	deque<int> fs;

	for (int i = 0; i < n; ++i) {
		if(begin[i] == 'F'){
			if(!fs.empty() && fs.back() % 2 != i % 2){
				fs.pop_back();
				continue;
			}

			if(!fs.empty())
				fs.push_back(fs.back() + 2);
			else
				fs.push_back(i % 2);
		}
	}

	base.resize(n);
	fill(base.begin(), base.end(), 'A');
	for(int i : fs)
		base[i] = 'F';
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> a >> b;

	base(a, basea);
	base(b, baseb);

	if(basea == baseb) printf("YES\n");
	else printf("NO\n");
}
