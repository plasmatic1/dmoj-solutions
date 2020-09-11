// SnakesNLadders CCC 1 L2.cpp : Defines the entry point for the console application.
//

#include <iostream>

using namespace std;

int increment(int *x, int amt);

int main()
{
	int space = 1, inc = 0, cond = 0;

	for (;;) {
		cin >> inc;
		cond = increment(&space, inc);

		if (cond == -1) {
			cout << "You Quit!" << endl;
			break;
		}

		cout << "You are now on square " << space << endl;

		if (space == 100) {
			cout << "You Win!" << endl;
			break;
		}
	}

	return 0;
}

int increment(int *x, int amt) {
	if (amt < 2 || amt > 12)
		return -1;

	if ((*x + amt) > 100)
		amt = 0;

	*x += amt;

	if (*x == 54)
		*x = 19;
	else if (*x == 90)
		*x = 48;
	else if (*x == 99)
		*x = 77;
	else if (*x == 9)
		*x = 34;
	else if (*x == 40)
		*x = 64;
	else if (*x == 67)
		*x = 86;
}

