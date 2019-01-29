//============================================================================
// Name        : Salactites.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 251;
int n, q,
	bx, by, bz, bx1, by1, bz1;

ll totaltree[MAX][MAX][MAX], allv = 0;
int arr[MAX][MAX][MAX];
char bins;

void add(int x, int y, int z, int v){
	for(int cx = x; cx <= n; cx += cx & -cx){
		for(int cy = y; cy <= n; cy += cy & -cy){
			for(int cz = z; cz <= n; cz += cz & -cz){
				totaltree[cx][cy][cz] += v;
			}
		}
	}
}

void change(int x, int y, int z, int v){
	add(x, y, z, v - arr[x][y][z]);
	arr[x][y][z] = v;
}


ll sum(int x, int y, int z){
	ll summ = 0;

	for(int cx = x; cx > 0; cx -= cx & -cx){
		for(int cy = y; cy > 0; cy -= cy & -cy){
			for(int cz = z; cz > 0; cz -= cz & -cz){
				summ += totaltree[cx][cy][cz];
			}
		}
	}

	return summ;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> q;

	for (int i = 0; i < q; ++i) {
		cin >> bins >> bx >> by >> bz >> bx1;

		if(bins == 'C'){
			change(bx, by, bz, bx1);
		}
		else{
			//bins is 'S'
			cin >> by1 >> bz1;
			bx--;
			by--;
			bz--;

			allv += sum(bx1, by1, bz1)
					- sum(bx1, by1, bz) - sum(bx1, by, bz1) - sum(bx, by1, bz1)
					+ sum(bx1, by, bz) + sum(bx, by1, bz) + sum(bx, by, bz1)
					- sum(bx, by, bz);
		}
	}

	printf("%lld\n", allv);
}
