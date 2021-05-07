#include "cave.h"
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

int tryCombination(int S[]);
void answer(int S[], int D[]);

const int MN = 5001;
void exploreCave(int N) {
    int D[N], S[N], fixedPos[N], lg = __lg(N);
    bool fix[N]; memset(fix, false, sizeof fix); memset(fixedPos, -1, sizeof fixedPos);
    for (auto i = 0; i < N; i++) {
        // assume pos=1 is open pos
        int sp = 0;
        for (auto j = lg; j >= 0; j--) {
            int tryS[N];
            for (auto k = 0; k < N; k++) {
                if (fix[k]) tryS[k] = fixedPos[k];
                else tryS[k] = ((k >> j) & 1);
            }
            int res = tryCombination(tryS);

            if (res == -1 || res > i) // flipping on all set bit j == door is open, and set the bit if possible
                sp |= 1 << j;
        }

        // check the correct position of the switch that governs door i
        int tryS[N], rightPos = 1; memset(tryS, 0, sizeof tryS);
        for (auto j = 0; j < N; j++) {
            if (fix[j]) tryS[j] = fixedPos[j];
            else tryS[j] = 1;
        }
        int res = tryCombination(tryS);
        if (res != -1 && res <= i) { // oh no, pos=1 is not right!
            rightPos = 0;
            sp ^= (1 << (lg+1)) - 1;
        }

        // assign
        S[sp] = rightPos;
        D[sp] = i;
        fix[sp] = true;
        fixedPos[sp] = rightPos;
    }

    answer(S, D);
}