// Calorie Counter (CCOntest 1 L1).cpp : Defines the entry point for the console application.
//

#include <iostream>

using namespace std;

int main()
{
	int c1, c2, c3, c4, sum;
	sum = 0;
	cin >> c1;
	cin >> c2;
	cin >> c3;
	cin >> c4;

	switch (c1) {
	case 1:
		sum += 461;
		break;
	case 2:
		sum += 431;
		break;
	case 3: 
		sum += 420;
		break;
	default:
		break;
	}

	switch (c2) {
	case 1:
		sum += 100;
		break;
	case 2:
		sum += 57;
		break;
	case 3:
		sum += 70;
		break;
	default:
		break;
	}

	switch (c3) {
	case 1:
		sum += 130;
		break;
	case 2:
		sum += 160;
		break;
	case 3:
		sum += 118;
		break;
	default:
		break;
	}

	switch (c4) {
	case 1:
		sum += 167;
		break;
	case 2:
		sum += 266;
		break;
	case 3:
		sum += 75;
		break;
	default:
		break;
	}

	cout << "Your total Calorie count is " << sum << "." << endl;

    return 0;
}

