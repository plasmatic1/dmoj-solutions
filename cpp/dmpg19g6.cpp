// ./dmpg-19-g6-pairs.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const ll MOD = 1e9 + 7;
const int MN = 2e5 + 10;

void fix(ll &x) { x %= MOD; if (x < 0) x += MOD; }

struct state {
    map<char, int> to;
    int link, len;

    bool end;
} st[MN*2];
int sz, last;
void init() {
    st[0].link = -1;
    sz = 1;
    last = 0;
}
void extend(char c) {
    int cur = sz++, p = last;
    st[cur].len = st[p].len + 1;
    st[cur].end = true;

    for (; p != -1 && !st[p].to.count(c); p = st[p].link)
        st[p].to[c] = cur;
    if (p == -1) st[cur].link = 0;
    else {
        int q = st[p].to[c];
        if (st[p].len + 1 == st[q].len) st[cur].link = q;
        else {
            int clone = sz++; st[clone] = st[q]; st[clone].len = st[p].len + 1; st[clone].end = false;
            for (; p != -1 && st[p].to[c] == q; p = st[p].link)
                st[p].to[c] = clone;
            st[cur].link = st[q].link = clone;
        }
    }

    last = cur;
}

int N;
string s;
ll ans[MN];
vector<int> g[MN*2];

/*
 * a(x-t)^2 + b(x-t) + c
 * a(x^2+t^2-2xt)+bx-bt+c
 * ax^2 + at^2 - 2atx + bx - bt + c
 * ax^2 + (b - 2at)x + (at^2 - bt + c)
 */
tuple<ll, ll, ll> shiftQuadratic(ll a, ll b, ll c, ll t) {
    ll bb = b - 2*a*t, cc = a*(t*t%MOD) - b*t + c;
    fix(bb); fix(cc);
    return {a, bb, cc};
}

ll dif[MN], difI[MN], difI2[MN];
void incQuadratic(ll a, ll b, ll c, int L, int R) { // adds ax^2 + bx + c to L..R
    difI2[L] += a;
    difI2[R+1] -= a;
    difI[L] += b;
    difI[R+1] -= b;
    dif[L] += c;
    dif[R+1] -= c;
}

// add (a+0r)^2, (a+1r)^2, (a+2r)^2, ..., to range A[L..R]
// (a+kr)^2
// = r^2k^2 + 2rak + a^2
void inc(ll a, ll r, int L, int R) {
    auto [_a, _b, _c] = shiftQuadratic(r*r%MOD, 2*r*a%MOD, a*a%MOD, L);
    incQuadratic(_a, _b, _c, L, R);
}

// think of doing this brute force-wise on a suffix trie first
pair<ll, int> dfs(int c) { // # of leaves, # of combos of children
    int p = st[c].link, plen = p == -1 ? -1 : st[p].len;

    ll cnt = 0; int add = st[c].end;
    for (auto to : g[c]) {
        auto [cnt0, add0] = dfs(to);
        cnt += cnt0;
        add += add0;
    }

    // deal with special Len=0 edge case later as SAM counts length 0 substr N times
    if (c) {
        // Brute force (for reference)
        // for (auto i = st[c].len; i > plen; i--) {
        //     cnt += add;
        //     ans[i] = (ans[i] + (cnt % MOD) * (cnt % MOD)) % MOD;
        // }

        // from cnt -> plen+1
        // Increment (cnt + add)^2, (cnt + 2*add)^2, (cnt + 3*add)^2
        ll finalCnt = cnt + add * (st[c].len - plen);
        inc(finalCnt % MOD, (MOD-add%MOD) % MOD, plen+1, st[c].len);
        cnt = finalCnt;
    }

    return {cnt, add};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> s;
    init();
    for (auto i = N-1; i >= 0; i--) extend(s[i]);

    // do DFS
    for (auto i = 1; i < sz; i++) g[st[i].link].push_back(i);
    dfs(0);

    // compute ans array (initially ans[i] = # of substr pairs such that LCP >= i)
    partial_sum(dif, dif+MN, dif);
    partial_sum(difI, difI+MN, difI);
    partial_sum(difI2, difI2+MN, difI2);
    for (auto i = 0; i <= N; i++) {
        fix(dif[i]); fix(difI[i]); fix(difI2[i]);
        ll t2 = difI2[i] * ((ll)i*i%MOD) % MOD, t1 = difI[i] * i % MOD, t0 = dif[i];
        ans[i] = (t0 + t1 + t2) % MOD;
    }
    // get final ans (i=0 case)
    ll C2 = (ll(N+1)*N/2) % MOD, cans = C2*C2 % MOD - ans[1];
    fix(cans);
    cout << cans << '\n';
    // get final ans (i>0)
    for (auto i = 1; i <= N; i++) {
        ll cans = ans[i]-ans[i+1]; fix(cans);
        cout << cans << '\n';
    }

    return 0;
}