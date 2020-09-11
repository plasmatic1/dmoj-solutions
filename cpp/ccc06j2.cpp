// Roll the Dice CCC 1 L2.cpp : Defines the entry point for the console application.
//

#include <iostream>

using namespace std;

int main()
{
	int a, b, total = 0;
	cin >> a;
	cin >> b;

	for (int i = 1; i <= a; i++) {
		for (int j = 1; j <= b; j++) {
			
			if ((i + j) == 10) 
				total++;
		}
	}

	if (total == 1)
		cout << "There is 1 way to get the sum 10." << endl;
	else
		cout << "There are " << total << " ways to get the sum 10." << endl;

	cin.get();
	cin.get();

    return 0;
}

