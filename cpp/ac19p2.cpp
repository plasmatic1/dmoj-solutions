// https://dmoj.ca/problem/ac19p3

#include <bits/stdc++.h>
using namespace std;
int main() {
    int N, L;
    cin >> N >> L;
    cin.ignore();


    string s;
    getline(cin, s);
    string chars = "abcdefghijklmnopqrstuvwxyz";
    map<char, int> ind;
    for(int i = 0; i < 26; i++) ind[chars[i]] = i;

    for(char x: s) {
        if(x == ' ') {
            cout << " ";
            continue;
        }

        int cute = ind[x];
        cute += L;
        cute %= 26;

        cout << chars[cute];
    }
    cout << endl;
}