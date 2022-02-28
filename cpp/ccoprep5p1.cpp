//============================================================================
// Name        : CityGame.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
//#define DEBUG

using namespace std;

const int MAX = 1000;

typedef pair<int, int> p;

int n, w, h, maxx = INT_MIN, hor[MAX][MAX], hor0[MAX][MAX], ver[MAX][MAX], ver0[MAX][MAX],
	lft[MAX], rht[MAX]; //Could use 0 for max but eh
char buf, grid[MAX][MAX], io_buf[1];

int main(){
	scanf("%d", &n);

	for (int z = 0; z < n; ++z) {
		scanf(" %d %d", &w, &h);

		for (int j = 0; j < w; ++j) {
			for (int l = 0; l < h; ++l) {
				scanf("%s", io_buf);
				grid[j][l] = io_buf[0];
			}
		}

		//First horizontal check
		for (int i = 0; i < w; ++i) {
			for (int j = 0; j < h; ++j) {
				if(grid[i][j] == 'F'){
					if(j > 0){
						hor[i][j] = hor[i][j - 1] + 1;
					}
					else{
						hor[i][j] = 1;
					}
				}
				else{
					hor[i][j] = 0;
				}
			}
		}

//		//Second horizontal check (rotated)
//		for (int i = 0; i < h; ++i) {
//			for (int j = 0; j < w; ++j) {
//				if(grid[j][i] == 'F'){
//					if(j > 0){
//						hor0[j][i] = hor0[j - 1][i] + 1;
//					}
//					else{
//						hor0[j][i] = 1;
//					}
//				}
//				else{
//					hor0[j][i] = 0;
//				}
//			}
//		}

		//First vertical check
		for (int i = 0; i < h; ++i) {
			deque<p> deq;
			fill(lft, lft + w, -1);
			fill(rht, rht + w, w);

			deq.push_back(p(0, INT_MIN));

			for (int j = 0; j < w; ++j) {
				int val = hor[j][i];

				while(val < deq.back().second){
					p last = deq.back();

					deq.pop_back();

					lft[last.first - 1] = deq.back().first - 1;
					rht[last.first - 1] = j;
				}

				deq.push_back(p(j + 1, val));
			}

			while(deq.size() > 1){
				p last = deq.back();

				deq.pop_back();
				lft[last.first - 1] = deq.back().first - 1;
			}

			for (int j = 0; j < w; ++j) {
				int h = rht[j] - lft[j] - 1;
//				printf("%d by %d (%d)\n", h, hor[j][i], h * hor[j][i]);
				maxx = max(maxx, h * hor[j][i]);
			}
		}

//		//First vertical check
//		for (int i = 0; i < h; ++i) {
//			int cmin = -1, last = 0;
//
////			printf(" -- begin i = %d\n", i);
//
//			for (int j = 0; j < w; ++j) {
//				cmin = min(cmin, hor[j][i]);
//				int alta = cmin * (j - last + 1), altb = hor[j][i];
//
////				printf("j(%d) cmin %d, last %d, alta %d, altb %d\n", j, cmin, last, alta, altb);
//
//				if(alta > altb){
//					ver[j][i] = alta;
//				}
//				else{
//					ver[j][i] = altb;
//					last = j;
//					cmin = hor[j][i];
//				}
//
//				maxx = max(ver[j][i], maxx);
//			}
//		}

//		//Second vertical check
//		for (int i = 0; i < w; ++i) {
//			int cmin = -1, last = 0;
//
//			for (int j = 0; j < h; ++j) {
//				cmin = min(cmin, hor0[i][j]);
//				int alta = cmin * (j - last + 1), altb = hor0[i][j];
//
//				if(alta > altb){
//					ver0[i][j] = alta;
//				}
//				else{
//					ver0[i][j] = altb;
//					last = j;
//					cmin = hor0[i][j];
//				}
//
//				maxx = max(ver0[i][j], maxx);
//			}
//		}

		//Begin debug
#ifdef DEBUG

		printf("hor: [\n");
		for(int i = 0; i < w; i++){
			printf("%d : ", i);
			for(int j = 0; j < h; j++){
				printf("%d, ", hor[i][j]);
			}
			printf("\n");
		}
		printf("]\n");

		printf("hor0: [\n");
		for(int i = 0; i < w; i++){
			printf("%d : ", i);
			for(int j = 0; j < h; j++){
				printf("%d, ", hor0[i][j]);
			}
			printf("\n");
		}
		printf("]\n");

		printf("ver: [\n");
		for(int i = 0; i < w; i++){
			printf("%d : ", i);
			for(int j = 0; j < h; j++){
				printf("%d, ", ver[i][j]);
			}
			printf("\n");
		}
		printf("]\n");

		printf("ver0: [\n");
		for(int i = 0; i < w; i++){
			printf("%d : ", i);
			for(int j = 0; j < h; j++){
				printf("%d, ", ver0[i][j]);
			}
			printf("\n");
		}
		printf("]\n");

#endif

		//End debug
		if(maxx == INT_MIN){
			printf("0\n");
		}
		else{
			printf("%d\n", maxx * 3);
		}
		maxx = INT_MIN;
	}
}