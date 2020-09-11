#include <stdio.h>
#include <stdbool.h>

#define SZ 3
#define MN (SZ * 6000000)
int N, Q;
unsigned char st[MN];

void setp(int x, int p) {
    int a = x * SZ;
    st[a] = p & 255;
    st[a + 1] = (p >> 8) & 255;
    st[a + 2] = p >> 16; // no need to add mask
}

int getp(int x) {
    int a = x * SZ;
    return st[a] | ((int)(st[a + 1]) << 8) | ((int)(st[a + 2] & 127) << 16);
}

void setuse(int x, bool b) {
    int a = x * SZ + 2;
    st[a] += (b ? 1 : -1) * 128;
}

bool getuse(int x) {
    int a = x * SZ + 2;
    return st[a] >> 7;
}

int main(){
    scanf("%d%d", &N, &Q);
    
    int p;
    for (int i = 2; i <= N; i++) {
        scanf("%d", &p);
        setp(i - 1, p - 1);
    }
    
    int x, y, tmp;
    bool found;
    while (Q--) {
        scanf("%d%d", &x, &y); x--; y--;
        tmp = x, found = false;
        while (x) { setuse(x, true); x = getp(x); }
        while (y) {
            if (getuse(y)) {
                printf("%d\n", y + 1);
                found = true;
                break;
            }
            y = getp(y);
        }
        while (tmp) { setuse(tmp, false); tmp = getp(tmp); }
        if (!found)
            printf("1\n");
    }

    return 0;
}