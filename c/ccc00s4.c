//============================================================================
// Name        : Golf.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>
#include <string.h>

#define ML 5281
#define min(a, b) (((a) < (b)) ? (a) : (b))

int d, n, buf,
	dp[ML];

int main(){
	scanf("%d %d", &d, &n);

	memset(dp, 0x3f, sizeof(dp));
	dp[0] = 0;

	for (int i = 0; i < n; ++i) {
		scanf("%d", &buf);

		for (int j = buf; j <= d; ++j) 
			dp[j] = min(dp[j], dp[j - buf] + 1);
	}

	// Output

	if(dp[d] == 0x3f3f3f3f)
		printf("Roberta acknowledges defeat.\n");
	else
		printf("Roberta wins in %d strokes.\n", dp[d]);
}