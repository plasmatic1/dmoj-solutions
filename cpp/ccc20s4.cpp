#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLING = 0x3f3f3f3f3f3f3f3f;

const int MN = 1e6 + 1, MN2 = MN * 2;
int N;
string s;

// I've never wanted to die so much in my life
int bit[3][MN2];
void add(int bit[MN2], int x, int v) {
    x++;bit[x] += v;
}
int sum(int bit[MN2], int x) {
    return bit[x];
}
int rsq(int bit[MN2], int L, int R) {
    return sum(bit, R) - sum(bit, L - 1);
}

int ulet(char c) { return c - 'A'; }

void reset() {
    for (int i = 0; i < 3; i++)
        memset(bit, 0, sizeof bit);
}

int run(string &s) {
    int N2 = N * 2;

    int cnt[3];
    fill(cnt, cnt + 3, 0);
    for (int i = 0; i < N - 1; i++) {
        int let = ulet(s[i]);
        cnt[let]++;
    }

    for (int i = 0; i < N2; i++) {
        int let = ulet(s[i]);
        add(bit[let], i, 1);
    }
    for (int i = 0; i < 3; i++) partial_sum(bit[i], bit[i] + MN2, bit[i]);

    int best = INF;
    for (int i = N - 1; i < N2; i++) {
        cnt[ulet(s[i])]++;

        int st = i - N + 1,
            alreadyInPlace1 = rsq(bit[0], st, st + cnt[0] - 1),
            alreadyInPlace2 = rsq(bit[1], st + cnt[0], st + cnt[0] + cnt[1] - 1) +
                            min(rsq(bit[1], st, st + cnt[0] - 1), rsq(bit[0], st + cnt[0], st + cnt[0] + cnt[1] - 1));
        best = min(best, cnt[0] - alreadyInPlace1 + cnt[1] - alreadyInPlace2);
        // printf("i=%d aip=%d acnt=%d\n", i, alreadyInPlace1, cnt[0]);

        cnt[ulet(s[st])]--;
    }

    return best;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> s;
    N = s.length();
    s += s;

    int best = INF;
    string perm = "ABC";
    do {
        reset();
        string t;
        for (auto ch : s) {
            // cout <<"ch="<<ch<<endl;
            if (ch == 'A') t += perm[0];
            if (ch == 'B') t += perm[1];
            if (ch == 'C') t += perm[2];
        }
        // cout<<"t="<<t<<endl; assert(0);
        best = min(best, run(t));
    } while (next_permutation(perm.begin(), perm.end()));
    
    cout << best << '\n';

    return 0;
}