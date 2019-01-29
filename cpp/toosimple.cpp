//============================================================================
// Name        : Jsfuck is like the solution to this question lmao
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <climits>
#include <cstdio>

using namespace std;

int ZERO = INT_MIN + INT_MAX, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, HUNDRED;

int main() {
	//definitions
	ZERO++;
	ONE = ++ZERO;
	ZERO--;
	TWO = ONE + ONE;
	THREE = ONE + TWO;
	FOUR = TWO * TWO;
	FIVE = FOUR + ONE;
	SIX = THREE * TWO;
	SEVEN = THREE + FOUR;
	EIGHT = FOUR + FOUR;
	NINE = FOUR + FIVE;
	TEN = FIVE * TWO;
	HUNDRED = TEN * TEN;

	//actual code
	putchar(SEVEN * TEN + TWO);
	putchar(HUNDRED + ONE);
	putchar(HUNDRED + EIGHT);
	putchar(HUNDRED + EIGHT);
	putchar(HUNDRED + TEN + ONE);
	putchar(FOUR * TEN + FOUR);
	putchar(THREE * TEN + TWO);
	putchar(EIGHT * TEN + SEVEN);
	putchar(HUNDRED + TEN + ONE);
	putchar(HUNDRED + TEN + FOUR);
	putchar(HUNDRED + EIGHT);
	putchar(HUNDRED);
	putchar(THREE * TEN + THREE);
//	putchar(ZERO);

	return ZERO;
}
