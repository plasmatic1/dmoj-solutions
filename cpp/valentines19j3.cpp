//============================================================================
// Name        : valentines19j3.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 10001, CH = 201;
int n,
	order[CH];
string s;
ll tot = 0,
	dp[MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> s;
	n = s.length();

	order['o'] = 1;
	order['v'] = 2;
	order['e'] = 3;

	for(int i = 0; i < n; i++){
		if(s[i] == 'l') dp[i] = 1;
		else{
			for(int j = 0; j < i; j++)
				if(order[s[j]] == order[s[i]] - 1)
					dp[i] += dp[j];
		}

		if(s[i] == 'e')
			tot += dp[i];
	}

	printf("%lld\n", tot);
}
