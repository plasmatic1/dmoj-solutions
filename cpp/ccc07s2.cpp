//============================================================================
// Name        : Boxes.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <algorithm>
#include <cstdio>
#include <functional>

using namespace std;

struct box{
	int x, y, z;

	box() : x(0), y(0), z(0){
		//
	}

	box(int x0, int y0, int z0) : x(x0), y(y0), z(z0){
		//
	}

	int vol(){
		return x * y * z;
	}

	friend bool operator<(box &a, box &b){
		return a.vol() < b.vol();
	}
};

bool fits(box &box, int x, int y, int z){
	if(box.x < x){
		return false;
	}
	if(box.y < y){
		return false;
	}
	if(box.z < z){
		return false;
	}
	return true;
}

bool fits2(box &box, int x, int y, int z){
	return fits(box, x, y, z) || fits(box, z, y, x) || fits(box, y, x, z) || fits(box, x, z, y) || fits(box, y, z, x) || fits(box, z, x, y);
}

//bool fits(box &box, int x, int y, int z){
//	if(box.x < x || box.y )
//
//}

int main() {
	int n, o;
	scanf("%d", &n);
	box bs[n];
	for(int i = 0; i < n; i++){
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		bs[i] = box(a, b, c);
	}

	sort(bs, bs + n);

	scanf("%d", &o);
	for(int i = 0; i < o; i++){
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		bool fit = false;
		for(box box : bs){
			if(fits2(box, a, b, c)){
				fit = true;
				printf("%d\n", box.vol());
				break;
			}
		}
		if(!fit){
			printf("Item does not fit.\n");
		}
	}
	return 0;
}
