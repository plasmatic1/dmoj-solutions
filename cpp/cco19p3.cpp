// ./cco-19-p3-winter-driving.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

ll P2(ll k) { return k*(k-1); }

const int MN = 2e5 + 1;
int N,
    sz[MN], P[MN];
ll A[MN];
vector<int> g[MN];

int gsz(int c, int p) {
    sz[c] = A[c];
    P[c] = p;
    for (auto to : g[c])
        if (to != p)
            sz[c] += gsz(to, c);
    return sz[c];
}

ll dfs(int c, int p, ll &add) {
    add += P2(A[c]);
    ll res = 0;
    for (auto to : g[c])
        if (to != p)
            res += dfs(to, c, add);
    add += A[c] * res;
    return res + A[c];
}

using T = tuple<ll, ll, ll>;
vector<T> run(vector<ll> &sub, int l, int r) {
    int sz = r-l+1;
    vector<T> res;
    for (auto i = 0; i < 1<<sz; i++) {
        ll s1 = 0, s2 = 0;
        for (auto j = 0; j < sz; j++) {
            if ((i >> j) & 1) s1 += sub[l+j];
            else s2 += sub[l+j];
        }
        res.emplace_back(s2-s1, s1, s2);
    }
    sort(res.begin(), res.end());
    return res;
}

ll check(int r) {
    ll res = 0, add = P2(A[r]);
    vector<ll> subcnt;
    for (auto to : g[r]) {
        subcnt.push_back(dfs(to, r, add));
        add += A[r] * subcnt.back();
    }
    int sz = subcnt.size(), h = sz/2;
    auto lhs = run(subcnt, 0, h-1), rhs = run(subcnt, h, sz-1);
    int rsz = rhs.size(), rptr = rsz-1;
    for (auto [d, s1, s2] : lhs) {
        while (rptr > 0 && d + get<0>(rhs[rptr]) > 0) rptr--;
        auto checkPairing = [&] (int idx) {
            auto [_, t1, t2] = rhs[idx];
            res = max(res, (s1+t1)*(s2+t2));
        };
        checkPairing(rptr);
        if (rptr < rsz-1) checkPairing(rptr+1);
    }

    return res + add;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (auto i = 1; i <= N; i++) cin >> A[i];
    for (auto i = 2; i <= N; i++) {
        int p; cin >> p;
        g[p].push_back(i);
        g[i].push_back(p);
    }

    gsz(1, -1);
    ll ans = 0, lim = sz[1]/2;
    for (auto i = 1; i <= N; i++) {
        int mxsz = sz[1] - sz[i];
        for (auto to : g[i])
            if (to != P[i])
                mxsz = max(mxsz, sz[to]);
        if (mxsz <= lim)
            ans = max(ans, check(i));
    }

    cout << ans << '\n';

    return 0;
}