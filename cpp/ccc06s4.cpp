//============================================================================
// Name        : Groups.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 101;
int n, grid[MAX][MAX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n;

	while(n != 0){
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				cin >> grid[i][j];
			}
		}

		// Associativity check
		bool pass = true;

		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				for (int k = 1; k <= n; ++k) {
					int val1 = grid[i][grid[j][k]], val2 = grid[grid[i][j]][k];

					if(val1 != val2){
						pass = false;
						break;
					}
				}

				if(!pass){
					break;
				}
			}

			if(!pass){
				break;
			}
		}

		if(!pass){
			printf("no\n");
			cin >> n;
			continue;
		}

		// Get identity

		int id = -1;

		for (int i = 1; i <= n; ++i) {
			bool idpass = true;

			for (int j = 1; j <= n; ++j) {
//				printf("comp id=%d %d -> values %d, %d\n", i, j, grid[j][i], grid[i][j]);

				if(grid[j][i] != j || grid[i][j] != j){
					idpass = false;
					break;
				}
			}

			if(idpass){
				id = i;
				break;
			}
		}

		if(id == -1){
			printf("no\n");
			cin >> n;
			continue;
		}

		// Inverse check with identity

		for (int i = 1; i <= n; ++i) {
			bool hasinv = false;

			for (int j = 1; j <= n; ++j) {
				if(grid[i][j] == id && grid[j][i] == id){
					hasinv = true;
					break;
				}
			}

			if(!hasinv){
				pass = false;
				break;
			}
		}

		if(pass){
			printf("yes\n");
		}
		else{
			printf("no\n");
		}

		cin >> n;
	}
}
