// Which Alien (CCC1 L1).cpp : Defines the entry point for the console application.

#include <iostream>

using namespace std;

int main()
{
	int antennae, eyes;
	cin >> antennae;
	cin >> eyes;

	if (antennae >= 3 && eyes <= 4)
		cout << "TroyMartian" << endl;
	if (antennae <= 6 && eyes >= 2)
		cout << "VladSaturnian" << endl;
	if (antennae <= 2 && eyes <= 3) {
		cout << "GraemeMercurian" << endl;
	}

    return 0;
}

