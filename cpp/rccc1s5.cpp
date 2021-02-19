// ./keen-multiset.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 262144, B = 4096;

const int __SH = __lg(B), __M = B-1, BCNT = MN/B;
int ghi(int x) { return x >> __SH; }
int glo(int x) { return x & __M; }
void CAP(int &c) { if (c >= MN) c = MN-1; }

int Q;

struct Block {
    int totXor, xorShf;
    bitset<B> fre;

    bool get(int k) { return fre[glo(k)]; }
    int cnt() { return fre.count() & 1; }
    void norm() {
        if (xorShf) {
            for (int i = 0; i < B; i++) {
                if (i < (i ^ xorShf)) {
                    bool b = fre[i ^ xorShf];
                    fre[i ^ xorShf] = fre[i];
                    fre[i] = b;
                }
            }
            xorShf = 0;
        }
    }
    bool empty() { return fre.count() == 0; }
    void clear() {
        totXor = xorShf = 0;
        fre.reset();
    }
} bs[BCNT];
int L(int k) { return k*B; }
int R(int k) { return k*B+B-1; }

void change(int i, int delta) {
    if (!delta) return;
    auto &b = bs[ghi(i)];
    b.totXor ^= i;
    b.fre.flip(glo(i) ^ b.xorShf);
}

void mergeBlock(int x, int y) {
    if (x == y) return; // if start==end don't

    auto &b = bs[x], &c = bs[y];
    if (b.empty()) return;
    if (c.empty())
        swap(b, c);
    else {
        // update new block
        c.norm(); b.norm();
        c.fre ^= b.fre;
        c.totXor ^= b.totXor;

        b.clear();
    }
}

int sz = 0;
pair<int, bool> chs[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N; cin >> N >> Q;
    for (int i = 0; i < N; i++) {
        int x; cin >> x;
        change(x, 1);
    }

    while (Q--) {
        int T; cin >> T;
        if (T == 1) {
            int x; cin >> x;
            assert(x < MN);
            change(x, 1);
        }
        else if (T == 2) {
            int l, r, x; cin >> l >> r >> x;
            if (l >= MN) continue;
            CAP(l); CAP(r);

            auto fullCover = [&] (int i) {
                return l <= L(i) && R(i) <= r;
            };

            // storenon-merge updates (partially covered)
            sz = 0;
            for (int i = 0; i < BCNT; i++) {
                int lk = L(i), rk = R(i);
                if (!fullCover(i) && ((lk <= l && l <= rk) || (lk <= r && r <= rk))) {
                    auto &b = bs[i];
                    for (int j = max(l, lk); j <= min(r, rk); j++) {
                        if (b.get(j ^ b.xorShf)) {
                            chs[sz++] = {j, 1};
                            change(j, 1);
                        }
                    }
                }
            }

            // do merge updates (fully covered)
            int gx = glo(x);
            for (int i = 0; i < BCNT; i++) {
                if (fullCover(i)) {
                    auto &b = bs[i];
                    
                    // update cur block before moving
                    b.xorShf ^= gx;
                    if (b.cnt()) b.totXor ^= x;

                    int oid = i ^ ghi(x);
                    // if the other block is also within range, we can just swap them
                    if (fullCover(oid) && oid != i) {
                        if (oid > i) {
                            bs[oid].xorShf ^= gx;
                            if (bs[oid].cnt()) bs[oid].totXor ^= x;
                            swap(b, bs[oid]);
                        }
                        else {
                            // otherwise, we've already swapped it so we should undo the change
                            b.xorShf ^= gx;
                            if (b.cnt()) b.totXor ^= x;
                        }
                    }
                    // merge
                    else
                        mergeBlock(i, oid);
                }
            }
            
            // apply non-merge updates
            for (int i = 0; i < sz; i++)
                change(chs[i].first ^ x, chs[i].second);
        }
        else {
            int l, r; cin >> l >> r;
            if (l >= MN) {
                cout << 0 << '\n';
                continue;
            }
            CAP(l); CAP(r);

            int ans = 0;
            for (int i = 0; i < BCNT; i++) {
                int lk = L(i), rk = R(i);
                if (l <= lk && rk <= r) ans ^= bs[i].totXor;
                else if ((lk <= l && l <= rk) || (lk <= r && r <= rk)) {
                    auto &b = bs[i];
                    for (int j = max(l, lk); j <= min(r, rk); j++)
                        if (b.get(j ^ b.xorShf))
                            ans ^= j;
                }
            }

            cout << ans << '\n';
        }
    }

    return 0;
}