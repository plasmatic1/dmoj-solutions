#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLING = 0x3f3f3f3f3f3f3f3f;

// 998244353

const int MN = 2e5 + 1;
string s, t;
int N, M,
    cnt[26], cnt2[26];

int ulet(char c) {
    return c - 'a';
}

const int P = 2, PR[P] = {31, 43}, MD[P] = {1000000007, 998244353};
ll hs[P][MN], pows[P][MN];

void init() {
    for (int i = 0; i < P; i++) {
        pows[i][0] = 1LL;
        for (int j = 1; j <= M; j++) {
            hs[i][j] = (hs[i][j - 1] * PR[i] + ulet(t[j - 1])) % MD[i];
            pows[i][j] = (pows[i][j - 1] * PR[i]) % MD[i];
        }
    }
}

ll fpow(ll x, ll y, ll mod) {
    if (!y) return 1LL;
    return (fpow((x * x) % mod, y >> 1, mod) * ((y & 1) ? x : 1LL)) % mod;
}
ll mdiv(ll x, ll y, ll mod) {
    return (x * fpow(y, mod - 2, mod)) % mod;
}

ll getsubstr(int modid, int L, int R) {
    int dif = R - L + 1;
    ll ret = hs[modid][R] - (pows[modid][dif] * hs[modid][L - 1]) % MD[modid];
    ret %= MD[modid];
    ret += MD[modid];
    ret %= MD[modid];
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> s >> t;
    N = s.length();
    M = t.length();

    if (N > M) {
        cout << "0\n";
        return 0;
    }

    init();

    for (int i = 0; i < N; i++)
        cnt[ulet(s[i])]++;
    for (int i = 0; i < N - 1; i++)
        cnt2[ulet(t[i])]++;
    
    // map<pair<ll, ll>, int> used;
    // unordered_set<string> has;
    set<pair<ll, ll>> used;
    ll tot = 0;
    for (int i = N - 1; i < M; i++) {
        int let = ulet(t[i]);
        cnt2[let]++;

        pair<ll, ll> curHash = {getsubstr(0, i - N + 1 + 1, i + 1), getsubstr(1, i - N + 1 + 1, i + 1)};
        auto ptr = used.find(curHash);
        if (ptr != used.end()) {
            cnt2[ulet(t[i - N + 1])]--;
            continue;
            // if (t.substr(ptr->second - N + 1, N) == t.substr(i - N + 1, N))
        }
        // used[curHash] = i;
        used.insert(curHash);

        // auto ss = t.substr(i - N + 1, N);
        // if (has.find(ss) != has.end()) {
        //     cnt2[ulet(t[i - N + 1])]--;
        //     continue;
        // }
        // has.insert(ss);


        bool wk = true;
        for (int j = 0; j < 26; j++) {
            if (cnt[j] != cnt2[j]) {
                // printf("i=%d j=%d c1=%d c2=%d\n", i, j, cnt[j], cnt2[j]);
                wk = false;
                break;
            }
        }

        // printf("i=%d wk=%d\n", i, wk);
        // printf("cnt=");
        // for (int j = 0; j < 26; j++)
        //     printf("%d ", cnt2[j]);
        // printf("\n");
        tot += wk;

        cnt2[ulet(t[i - N + 1])]--;
    }

    cout << tot << endl;

    return 0;
}