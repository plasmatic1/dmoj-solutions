// ./joi-18-spring-camp-day-1-p1-construction-of-highway.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;

const int MN = 1e5 + 1;
int N, 
    C[MN], A[MN], B[MN];

// coord comp
vector<int> rnk;

// HLD
int par[MN], dep[MN], head[MN], heavy[MN], pos[MN], cpos = 0;
vector<int> seq, g[MN];
int dfs(int c, int p) {
    par[c] = p;
    int sz = 1, heavysz = -1;
    for (auto to : g[c]) {
        if (to != p) {
            dep[to] = dep[c]+1;
            int chsz = dfs(to, c);
            if (chsz > heavysz) {
                heavysz = chsz;
                heavy[c] = to;
            }
            sz += chsz;
        }
    }

    return sz;
}
void buildHld(int c, int chead) {
    pos[c] = ++cpos;
    seq.push_back(c);
    head[c] = chead;
    if (heavy[c]) buildHld(heavy[c], chead);
    for (auto to : g[c])
        if (to != par[c] && to != heavy[c])
            buildHld(to, to);
}

// list of changes
vector<pii> ch[MN];
// BIT
int qid[MN], cqid = 0;
ll bit[MN];
void reset() { cqid++; }
void ensure(int k) {
    if (qid[k] != cqid) {
        qid[k] = cqid;
        bit[k] = 0;
    }
}
void add(int x, ll v) {
    for (; x < MN; x += x & -x) {
        ensure(x);
        bit[x] += v;
    }
}
ll sum(int x) {
    ll res = 0;
    for (; x; x -= x & -x) {
        ensure(x);
        res += bit[x];
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (auto i = 1; i <= N; i++) {
        cin >> C[i];
        rnk.push_back(C[i]);
    }
    sort(rnk.begin(), rnk.end());
    rnk.resize(unique(rnk.begin(), rnk.end()) - rnk.begin());
    for (auto i = 1; i <= N; i++)
        C[i] = lower_bound(rnk.begin(), rnk.end(), C[i]) - rnk.begin() + 1;

    for (auto i = 1; i <= N-1; i++) {
        int a, b; cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
        A[i] = a; B[i] = b;
    }
    dfs(1, -1);
    buildHld(1, 1);

    // push inf
    for (auto i = 1; i <= N; i++) {
        if (i == head[i])
            ch[i].emplace_back(-1, INF);
    }
    for (auto it = seq.rbegin(); it != seq.rend(); it++)
        ch[head[*it]].emplace_back(C[*it], pos[*it]);

    // solve
    for (auto i = 1; i <= N-1; i++) {
        int u = A[i];
        vector<pii> vals;
        while (u != -1) {
            vector<pii> cvals;

            int pre = pos[head[u]]-1;
            auto &chs = ch[head[u]];
            while (!chs.empty()) {
                auto [v, i] = chs.back();
                if (i == INF) break;

                int fre = min(pos[u], i) - pre;
                cvals.emplace_back(fre, v);

                if (i > pos[u]) break;
                chs.pop_back();
                pre = i;
            }
            vals.insert(vals.end(), cvals.rbegin(), cvals.rend());

            // add new change
            chs.emplace_back(C[B[i]], pos[u]);

            u = par[head[u]];
        }

        ll ans = 0;
        for (auto [cnt, v] : vals) {
            ans += ll(cnt)*sum(v-1);
            add(v, cnt);
        }
        cout << ans << '\n';
        reset();
    }

    return 0;
}