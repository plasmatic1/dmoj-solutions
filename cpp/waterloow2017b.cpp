//============================================================================
// Name        : VeraAndLCS.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 2001;
int n, k,
	chars[26][MAX];
string a;

// :cheese:

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> k >> a;

	if(k > n){
		printf("WRONGANSWER\n");
		return 0;
	}

	a = " " + a;

	for (int i = 1; i <= n; ++i) {
		chars[a[i] - 'a'][i]++;

		for (int j = 0; j < 26; ++j)
			chars[j][i] += chars[j][i - 1];
	}

	// find best letter to spam with

	int best = -1, bestv = INT_MAX;

	for(int i = 0; i < 26; i++){
		int alt = chars[i][n] - chars[i][k];
//		printf("-- i=%c alt=%d\n", i+'a', alt);

		int curr = alt;
		for (int j = k; curr > 0 && j > 0; --j) {
//			printf("j=%d curr=%d\n", j, curr);
			curr--;
			if(chars[i][j] - chars[i][j - 1]){
				curr++;
				alt++;
			}
		}

		if(alt < bestv){
			best = i;
			bestv = alt;
		}
	}

	//fuck it if u cant spam

	if(bestv > k){
		printf("WRONGANSWER\n");
		return 0;
	}

//	printf("bestv=%d\n", bestv);

	// printing "output"

	int end = k - bestv;
	char let = (char)(best + 'a');
	for(int i = 1; i <= end; i++) printf("%c", a[i]);
	for(int i = end + 1; i <= n; i++) printf("%c", let);
	printf("\n");
}
