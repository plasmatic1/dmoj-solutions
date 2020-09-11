// slots.cpp : Defines the entry point for the console application.
//

#include <iostream>

using namespace std;

int main()
{
	int qamount, a, b, c, gp = 0;

	cin >> qamount;
	cin >> a;
	cin >> b;
	cin >> c;

	while (qamount > 0) {
		if (qamount == 0)
			continue;

		qamount--;
		a++;
		gp++;

		if (a == 35) {
			qamount += 30;
			a = 0;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////

		if (qamount == 0)
			continue;

		qamount--;
		b++;
		gp++;

		if (b == 100) {
			qamount += 60;
			b = 0;
		}

		//////////////////////////////////////////////////////////////////////////////////////////////

		if (qamount == 0)
			continue;

		qamount--;
		c++;
		gp++;

		if (c == 10) {
			qamount += 9;
			c = 0;
		}
	}

	cout << "Martha plays " << gp << " times before going broke." << endl;

	//cin.get();
	//cin.get();

    return 0;
}

