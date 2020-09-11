// hidden_palindrome.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool isPalindrome(string);

int main()
{
	string word;
	cin >> word;

	int len = 0;

	for (int i = 0; i < word.length(); i++) {
		for (int j = 1; j <= ((int)word.length() - i); j++) {
			string sub = word.substr(i, j);

			if (isPalindrome(sub) && ((int)sub.length()) > len)
				len = (int)sub.length();
		}
	}

	cout << len << endl;

    return 0;
}

bool isPalindrome(string word) {
	string wordd = word.substr(0, word.length());
	reverse(wordd.begin(), wordd.end());

	return wordd == word;
}