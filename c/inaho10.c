#include <stdio.h>
int n;
double ret;
int main(){
	scanf("%d", &n);
	printf("Q %.20f\n", 1e-10);
	scanf("%lf", &ret);
	printf("A %d\n", (int)round(ret * 1e10));
}