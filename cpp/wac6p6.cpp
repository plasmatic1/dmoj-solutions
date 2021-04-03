// ./wesleys-anger-contest-6-problem-6-santas-candy-factory.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using pic = pair<int, char>;

int A, B, C, N;

#ifdef LOCAL
string s;
char curcandy, id[2];
int cnt[2];

void place(int k) { assert(1 <= k && k <= 2); k--;
    assert(curcandy);
    assert(curcandy == id[k] || id[k] == 0);
    cnt[k]++;
    curcandy = 0;
}
void empty(int k) { assert(1 <= k && k <= 2); k--;
    id[k] = 0;
    cnt[k] = 0;
}
void discard() {
    assert(curcandy);
    curcandy = 0;
}
char get() { assert(!curcandy); curcandy = s.back(); s.pop_back(); return curcandy; }

#else
void place(int k) { cout << "PLACE " << k << '\n'; cout.flush(); }
void empty(int k) { cout << "EMPTY " << k << '\n'; cout.flush(); }
void discard() { cout << "DISCARD\n"; cout.flush(); }
char get() { char c; cin >> c; return c; }
#endif

void solve() {
    cin >> A >> B >> C;
#ifdef LOCAL
    curcandy = 0;
    cin >> s;
    printf("solving: %s, a=%d b=%d c=%d\n", s.c_str(), A,B,C);
    reverse(s.begin(), s.end());
#endif
    N = A+B+C;
    {
        int _[3] = {A, B, C};
        sort(_, _+3);
        A = _[0];
        B = _[1];
        C = _[2];
    }

    char id[2] = {0, 0};
    int cnt[2] = {0, 0};
    auto tryplace = [&] (char c, bool dry) { // dry == dry-run
        for (auto i = 0; i < 2; i++) {
            if (id[i] == c) {
                if (!dry) {
                    id[i] = c;
                    cnt[i]++;
                    place(i+1);
                }
                return true;
            }
        }
        for (auto i = 0; i < 2; i++) {
            if (id[i] == 0) {
                if (!dry) {
                    id[i] = c;
                    cnt[i]++;
                    place(i+1);
                }
                return true;
            }
        }
        if (!dry) discard();
        return false;
    };

    // Strat 1, A+B>=42
    // Strat 2, B<=28
    if (A+B >= 43) {
        for (auto i = 0; i < N; i++) {
            tryplace(get(), false);
        }
    }
    else if (B <= 28) {
        map<char, int> fre;
        auto mfre = [&] () {
            pic res{-1, 'z'};
            for (auto p : fre) res = max(res, {p.second, p.first});
            return res;
        };

        for (auto i = 0; i < N; i++) {
            char c = get();
            fre[c]++;
            // printf("i=%d c=%c STATE: %c=%d %c=%d\n", i,c,id[0],cnt[0],id[1],cnt[1]);
            // fflush(stdout);

            auto popular = mfre();
            if (popular.first > B && !tryplace(popular.second, true)) {
                // printf("|E STATE: %c=%d %c=%d foundPopular=(%c, %d)\n", id[0],cnt[0],id[1],cnt[1],popular.second,popular.first);
                // fflush(stdout);
                empty(1);
                id[0] = 0;
                cnt[0] = 0;
            }
            tryplace(c, false);
        }
        assert(cnt[0] + cnt[1] >= 40);
    }
    else {
        map<char, int> fre;

        for (auto i = 0; i < N; i++) {
            char c = get();
            fre[c]++;
            // printf("i=%d c=%c STATE: %c=%d %c=%d\n", i,c,id[0],cnt[0],id[1],cnt[1]);
            // fflush(stdout);

            for (auto p : fre) {
                if (p.second > A && !tryplace(p.first, true)) {
                    // printf("|E STATE: %c=%d %c=%d foundPopular=(%c, %d)\n", id[0],cnt[0],id[1],cnt[1],popular.second,popular.first);
                    // fflush(stdout);
                    for (auto j = 0; j < 2; j++) {
                        if (fre[id[j]] <= A) {
                            empty(j+1);
                            id[j] = 0;
                            cnt[j] = 0;
                            break;
                        }
                    }
                    break;
                }
            }
            tryplace(c, false);
        }
    }

#ifdef LOCAL
    if (!id[0]) id[0] = '*';
    if (!id[1]) id[1] = '*';
    printf("END STATE: %c=%d %c=%d\n", id[0],cnt[0],id[1],cnt[1]);
    assert(cnt[0] + cnt[1] >= 40);
#endif
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}