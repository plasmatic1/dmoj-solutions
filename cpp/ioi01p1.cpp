//============================================================================
// Name        : MobilePhones.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
//#define DEBUG

//1024 + 1 for 1 based indexing

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 1025;

int n, input, buf, buf2, buf3, buf4, totaltree[MAX][MAX];

void addd(int x, int y, int z){
	for(int cx = x; cx <= n; cx += cx & -cx){
		for(int cy = y; cy <= n; cy += cy & -cy){
			totaltree[cx][cy] += z;
		}
	}
}

int summ(int x, int y){
	//Attempt with x- and y
	int summ = 0;

	for(int cx = x; cx > 0; cx -= cx & -cx){
		for(int cy = y; cy > 0; cy -= cy & -cy){
			summ += totaltree[cx][cy];
		}
	}

	return summ;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> input;

	while(input != 3){
		if(input == 0){
			cin >> n;

			//I don't think any initialization is needed for this portion at least
		}
		else if(input == 1){
			cin >> buf >> buf2 >> buf3;
			buf++; buf2++;

			addd(buf, buf2, buf3);
		}
		else if(input == 2){
			cin >> buf >> buf2 >> buf3 >> buf4; //x1 y1, x2 y2
			buf++; buf2++; buf3++; buf4++;

#ifdef DEBUG
			printf("tree: [\n");
			for(int i = 1; i <= n; i++){
				printf("%d : ", i);
				for(int j = 1; j <= n; j++){
					printf("%lld, ", totaltree[i][j]);
				}
				printf("\n");
			}
			printf("]\n");

			printf("x2,y2: %lld, x1,y1: %lld, x1,y2: %lld, x2,y1: %lld\n", sum(buf3, buf4),	 sum(buf, buf2), sum(buf, buf4), sum(buf3, buf2));
#endif

//			if(buf >= 2 && buf2 >= 2)
				printf("%d\n", summ(buf3, buf4) + summ(buf - 1, buf2 - 1) - summ(buf - 1, buf4) - summ(buf3, buf2 - 1));
//			else
//				printf("%lld\n", summ(buf3, buf4));
		}

		cin >> input;
	}

	return 0;
}
