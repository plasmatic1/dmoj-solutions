// ./mine-and-tree.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
using ld = long double;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const ld PI = acos(-1);

struct vec {
    ld m[3];
    vec() : m() {}
};
struct mat {
    ld m[3][3];
    mat() : m() {}
    mat operator*(const mat o) const {
        mat res;
        for (auto i = 0; i < 3; i++)
            for (auto j = 0; j < 3; j++)
                for (auto k = 0; k < 3; k++)
                    res.m[i][j] += m[i][k] * o.m[k][j];
        return res;
    }
    vec operator*(const vec o) const {
        vec res;
        for (auto i = 0; i < 3; i++)
            for (auto j = 0; j < 3; j++)
                res.m[i] += m[i][j] * o.m[j];
        return res;
    }
};
struct Imat : mat {
    Imat() {
        for (auto i = 0; i < 3; i++)
            m[i][i] = 1;
    }
};
const Imat ID;

const int MN = 1e5 + 1;
int N, Q;
vector<int> g[MN];

// hld
int sz[MN], par[MN], dep[MN], pos[MN], head[MN], heavy[MN], cpos = 1;
void dfs(int c, int p) {
    sz[c] = 1;
    par[c] = p;
    for (auto to : g[c]) {
        if (to != p) {
            dep[to] = dep[c] + 1;
            dfs(to, c);
            sz[c] += sz[to];
            if (!heavy[c] || sz[to] > sz[heavy[c]]) heavy[c] = to;
        }
    }
}
void build(int c, int chead) {
    pos[c] = cpos++;
    head[c] = chead;
    if (heavy[c]) build(heavy[c], chead);
    for (auto to : g[c]) {
        if (to != par[c] && to != heavy[c]) {
            build(to, to);
        }
    }
}

// segtree
#define MID int mid = (l + r) / 2, lhs = i+1, rhs = i+(mid-l+1)*2;
mat seg[MN*2], segr[MN*2];
void update(mat seg[MN*2], bool rev, int q, mat &v, int i=1, int l=1, int r=N) {
    if (q > r || q < l) return;
    if (q == l && q == r) return void(seg[i] = v);
    MID;
    update(seg, rev, q, v, lhs, l, mid); update(seg, rev, q, v, rhs, mid+1, r);
    if (rev) seg[i] = seg[lhs] * seg[rhs];
    else seg[i] = seg[rhs] * seg[lhs];
}
mat query(mat seg[MN*2], bool rev, int ql, int qr, int i=1, int l=1, int r=N) {
    if (ql > r || qr < l) return ID;
    if (ql <= l && r <= qr) return seg[i];
    MID;
    if (rev) return query(seg, rev, ql, qr, lhs, l, mid) * query(seg, rev, ql, qr, rhs, mid+1, r);
    else return query(seg, rev, ql, qr, rhs, mid+1, r) * query(seg, rev, ql, qr, lhs, l, mid);
}

// path queries
int lca(int u, int v) {
    if (dep[head[u]] > dep[head[v]]) swap(u, v);
    while (head[u] != head[v]) {
        v = par[head[v]];
        if (dep[head[u]] > dep[head[v]]) swap(u, v);
    }
    return dep[u] < dep[v] ? u : v;
}
mat path(bool rev, int up, int down) {
    mat res = ID;
    while (head[up] != head[down]) {
        if (!rev) res = res * query(seg, 0, pos[head[down]], pos[down]);
        else res = query(segr, 1, pos[head[down]], pos[down]) * res;
        down = par[head[down]];
    }
    if (!rev) res = res * query(seg, 0, pos[up]+1, pos[down]);
    else res = query(segr, 1, pos[up]+1, pos[down]) * res;
    return res;
}

// creating matrices
mat op[MN];
void setOp(int k) {
    op[k] = ID;

    char T; cin >> T;
    if (T == 'R') {
        ld ang; cin >> ang; 
        ang *= PI / 180.;
        op[k].m[0][0] = cos(ang);
        op[k].m[0][1] = -sin(ang);
        op[k].m[1][0] = sin(ang);
        op[k].m[1][1] = cos(ang);
    }
    else if (T == 'T') {
        int x, y; cin >> x >> y;
        op[k].m[0][2] = x;
        op[k].m[1][2] = y;
    }
    else if (T == 'M') {
        int x, y; ld p; cin >> x >> y >> p;
        p /= 100.;

        mat tr1 = ID, scale = ID, tr2 = ID;
        tr1.m[0][2] = -x;
        tr1.m[1][2] = -y;
        scale.m[0][0] = p;
        scale.m[1][1] = p;
        tr2.m[0][2] = x;
        tr2.m[1][2] = y;

        op[k] = tr2 * scale * tr1;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;
    for (auto i = 1; i <= N; i++)
        setOp(i);
    for (auto i = 1; i < N; i++) {
        int a, b; cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(1, -1);
    build(1, 1);
    fill(seg, seg + sizeof(seg) / sizeof(mat), ID);
    for (auto i = 1; i <= N; i++) {
        update(seg, 0, pos[i], op[i]);
        update(segr, 1, pos[i], op[i]);
    }

    cout << fixed << setprecision(6);
    while (Q--) { 
        char T; cin >> T;
        if (T == 'U') {
            int x; cin >> x;
            setOp(x);
            update(seg, 0, pos[x], op[x]);
            update(segr, 1, pos[x], op[x]);
        }
        else {
            int u, v; ld x, y; cin >> u >> v >> x >> y;
            vec ans; ans.m[0] = x; ans.m[1] = y; ans.m[2] = 1;
            
            int lcav = lca(u, v);
            mat lhs = path(1, lcav, u), rhs = path(0, lcav, v);

            mat m = rhs * op[lcav] * lhs; // backwards!!!
            ans = m * ans;
            cout << ans.m[0] << ' ' << ans.m[1] << '\n';
        }
    }

    return 0;
}