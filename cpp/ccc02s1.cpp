// Student council breakfast CCC 1 L3.cpp : Defines the entry point for the console application.
//

#include <iostream>

using namespace std;
//sexually transmitted desease

int main()
{
	int cp, cg, cr, co, total_min, tick_combos = 0, to_be_raised;

	cin >> cp >> cg >> cr >> co >> to_be_raised;

	total_min = to_be_raised;

	for (int i = 0; i <= (to_be_raised / cp); i++) {
		for (int j = 0; j <= (to_be_raised / cg); j++) {
			for (int k = 0; k <= (to_be_raised / cr); k++) {
				for (int l = 0; l <= (to_be_raised / co); l++) {
					if ((cp * i + cg * j + cr * k + co * l) == to_be_raised) {
						cout << "# of PINK is " << i << " # of GREEN is " << j << " # of RED is " << k << " # of ORANGE is " << l << endl;
						
						tick_combos++;

						if ((i + j + k + l) < total_min) {
							total_min = i + j + k + l;
						}
					}
				}
			}
		}
	}

	cout << "Total combinations is " << tick_combos << "." << endl;
	cout << "Minimum number of tickets to print is " << total_min << "." << endl;

    return 0;
}

