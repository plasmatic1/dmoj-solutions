// ./cco-04-p5-jengaism.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 10000;
int N, mxn = 18;
bool have[MN][3];

bool bad(int r) {
    if (r == mxn) return false;
    int cnt = have[r][0] + have[r][1] + have[r][2];
    if (cnt < 1) return true;
    if (cnt == 1 && (have[r][0] || have[r][2])) return true;
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scanf("%d", &N);
    for (auto i = 1; i <= mxn; i++) 
        have[i][0] = have[i][1] = have[i][2] = true;
    for (auto i = 0; i < N; i++) {
        int ar, br; char ac, bc;
        scanf("%d%c%d%c", &ar, &ac, &br, &bc);
        ac -= 'A'; bc -= 'A';

        have[ar][(int)ac] = false;
        if (bad(ar)){
            printf("The tower collapses after removing %d%c\n", ar, ac+'A');
            return 0;
        }

        have[br][(int)bc] = true;
        mxn = max(mxn, br);
        if (bad(br)){
            printf("The tower collapses after placing %d%c\n", ar, ac+'A');
            return 0;
        }
    }
    printf("The tower never collapses\n");

    return 0;
}