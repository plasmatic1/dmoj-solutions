//============================================================================
// Name        : DrHenriAndIonization.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 200001;
int n, tot = 0,
		a[MAX], b[MAX];
vector<int> as, bs;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}

	for (int i = 0; i < n; ++i) {
		cin >> b[i];
	}

	for (int i = 0; i < n; ++i) {
		if(a[i] <= b[i]){
			as.push_back(i);
		}
		else{
			bs.push_back(i);
		}
	}

	int asize = as.size(), bsize = bs.size();

	if(bsize % 2 == 0){ // Leave the list as is and sum the values
		for (int i : as) {
			tot += a[i];
		}

		for (int i : bs) {
			tot += b[i];
		}
	}
	else{ // oh fuck angies coming
		int mind = INT_MIN, minia = -1, minib = -1;

		for (int i : as) {
			int dif = a[i] - b[i];

			if(dif > mind){
				mind = dif;
				minia = i;
			}
		}

		mind = INT_MAX;

		for(int i : bs){
			int dif = a[i] - b[i];

			if(dif < mind){
				mind = dif;
				minib = i;
			}
		}

		// Sum up values after min diff is found

		if(minia == -1){ // Means as is empty
			tot = a[minib];
		}
		else{
			tot = min(a[minia] + a[minib], b[minia] + b[minib]);

			for(int i : as){
				if(i != minia){
					tot += a[i];
				}
			}
		}

		for (int i : bs) {
			if(i != minib){
				tot += b[i];
			}
		}
	}

	printf("%d\n", tot);
}
