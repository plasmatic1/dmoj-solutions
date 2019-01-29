//============================================================================
// Name        : MusicalChairs.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 1000001;

int n, k, buf, child[MAX], ccount;
bool emptys[MAX];
stack<int> cchild;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> k;

    fill(child, child + n + 1, -1);

	for (int i = 0; i < k; ++i) {
		cin >> buf;
		emptys[buf] = true;
	}

	int filled = k + 1, ccount = filled;
	for (int i = 1; i <= filled; ++i) {
		cin >> buf;
		child[buf] = i;
	}

	for (int i = 1; i <= n; ++i) {
        if(child[i] != -1){
            cchild.push(child[i]);
        }

        if(emptys[i] && !cchild.empty()){
            cchild.pop();
            ccount--;
            emptys[i] = false;
        }

        if(ccount <= 1 && !cchild.empty()){
            printf("%d\n", cchild.top());
            return 0;
        }
	}

    for (int i = 1; i <= n; ++i) {
        if(emptys[i] && !cchild.empty()){
            cchild.pop();
            ccount--;
            emptys[i] = false;
        }

        if(ccount <= 1 && !cchild.empty()){
            printf("%d\n", cchild.top());
            return 0;
        }
	}
}
