// DoubleDice CCC 1 L2.cpp : Defines the entry point for the console application.
//

#include <iostream>

using namespace std;

int main()
{
	int fp = 100, sp = 100, rnumber;

	cin >> rnumber;

	for (int i = 0; i < rnumber; i++) {
		int a, b;
		
		cin >> a >> b;

		if (a > b) {
			sp -= a;
		}
		else if (a < b) {
			fp -= b;
		}
	}

	cout << fp << endl << sp << endl;

    return 0;
}

