// ./cco-03-p5-longest-substring.yml
// Interesting: including bits/stdc++.h uses signficantly more memory
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <cstring>
#include <deque>
#ifdef LOCAL
#include <iostream>
#endif
using namespace std;
#define pb push_back
template <typename T> int SZ(T &c) { return (int)c.size(); }

const int MV = 65536;
bool inq[MV];
deque<uint16_t> ans, dq;

int main() {
    int anslen = 0;

    uint16_t x;
    scanf("%hu", &x);
    while (x) {
        while (inq[x]) {
            inq[dq.front()] = false;
            ans.pb(dq.front());
            dq.pop_front();
        }
        inq[x] = true;
        dq.pb(x);

        while (SZ(ans) > anslen)
            ans.pop_back();

        assert(SZ(ans) <= MV);
        assert(SZ(dq) <= MV);

        if (SZ(dq) > anslen) {
            anslen = SZ(dq);
            ans.clear();
        }

        scanf("%hu", &x);
    }

    int cnt = 0;
    for (auto x : ans) {
        if (++cnt > anslen) return 0;
        printf("%hu\n", x);
    }
    for (auto x : dq) {
        if (++cnt > anslen) return 0;
        printf("%hu\n", x);
    }

    return 0;
}