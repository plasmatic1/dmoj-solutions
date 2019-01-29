/*
I swear the fucking solution is literally mine but with actual knowledge of how to fucking dynamic programming FUCK
*/

////=======================Test case 9===========Test case 9=================================Test case 9=========
// Name        : Test case 9
// Author      : Test case 9
// Version     :Test case 9
// Copyright   : Test case 9
// Description : Test case 9
//===============Test case 9==========================Test case 9================Test case 9===========Test case 9========

#include <algorithm>
#include <climits>
#include <cstdio>
#include <iostream>

using namespace std;

const int MAX = 1000;
int squares[MAX], dist[MAX][MAX + 1], n, buf;

//My code already works with the correct solution lol
int dp(int start, int last_jump) {
   if(start < 0 || start >= n){
	   return INT_MAX;
   }

   if(start == n - 1){
	  return squares[start];
   }

   if(dist[start][last_jump] != -1){
	   return dist[start][last_jump];
   }

   dist[start][last_jump] = squares[start] +
		   min(dp(start - last_jump, last_jump), dp(start + last_jump + 1, last_jump + 1));
   return dist[start][last_jump];
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> squares[i];
	}

	for (int i = 0; i < n; ++i) {
		fill(dist[i], dist[i] + n + 1, -1);
	}
	dist[0][0] = 0;

	printf("%d\n", dp(1, 1));
	return 0;
}
