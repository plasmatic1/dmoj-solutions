//============================================================================
// Name        : valentines19j1.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

int n, buf;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> buf;

		if(buf >= 4000)
			printf("Rainbow Master\n");
		else if(buf >= 3000)
			printf("Target\n");
		else if(buf >= 2200)
			printf("Grandmaster\n");
		else if(buf >= 1800)
			printf("Master\n");
		else if(buf >= 1500)
			printf("Candidate Master\n");
		else if(buf >= 1200)
			printf("Expert\n");
		else if(buf >= 1000)
			printf("Amateur\n");
		else
			printf("Newbie\n");
	}
}
