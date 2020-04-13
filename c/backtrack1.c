#include <stdio.h>
// #include <assert.h>

char n, a, b;
int main(){
    a = getchar_unlocked();
    b = getchar_unlocked();
    
    // assert(b <= '0' && b <= '9');
    n = a - '0';
    if(b >= '0' && b <= '9')
        n = (n << 1) + (n << 3) + (b - '0');
    
    switch(n){
case 1:
printf("1");break;
case 2:
printf("2");break;
case 3:
printf("2");break;
case 4:
printf("4");break;
case 5:
printf("4");break;
case 6:
printf("8");break;
case 7:
printf("8");break;
case 8:
printf("16");break;
case 9:
printf("16");break;
case 10:
printf("32");break;
case 11:
printf("32");break;
case 12:
printf("64");break;
case 13:
printf("64");break;
case 14:
printf("128");break;
case 15:
printf("128");break;
case 16:
printf("256");break;
case 17:
printf("256");break;
case 18:
printf("512");break;
case 19:
printf("512");break;
case 20:
printf("1024");break;
case 21:
printf("1024");break;
case 22:
printf("2048");break;
case 23:
printf("2048");break;
case 24:
printf("4096");break;
case 25:
printf("4096");break;
case 26:
printf("8192");break;
case 27:
printf("8192");break;
case 28:
printf("16384");break;
case 29:
printf("16384");break;
case 30:
printf("32768");break;
case 31:
printf("32768");break;
case 32:
printf("65536");break;
case 33:
printf("65536");break;
case 34:
printf("131072");break;
case 35:
printf("131072");break;
case 36:
printf("262144");break;
case 37:
printf("262144");break;
case 38:
printf("524288");break;
case 39:
printf("524288");break;
case 40:
printf("1048576");break;
case 41:
printf("1048576");break;
case 42:
printf("2097152");break;
case 43:
printf("2097152");break;
case 44:
printf("4194304");break;
case 45:
printf("4194304");break;
case 46:
printf("8388608");break;
case 47:
printf("8388608");break;
case 48:
printf("16777216");break;
case 49:
printf("16777216");break;
case 50:
printf("33554432");break;
case 51:
printf("33554432");break;
case 52:
printf("67108864");break;
case 53:
printf("67108864");break;
case 54:
printf("134217728");break;
case 55:
printf("134217728");break;
case 56:
printf("268435456");break;
case 57:
printf("268435456");break;
case 58:
printf("536870912");break;
case 59:
printf("536870912");break;
case 60:
printf("1073741824");break;
case 61:
printf("1073741824");break;
case 62:
printf("2147483648");break;
case 63:
printf("2147483648");break;
}
    return 0;
}