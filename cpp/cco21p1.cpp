#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;

const int MN = 1e5 + 1;
int N, K, Q,
    A[MN], P[MN];

int bit[MN];
void add(int x, int v) {
    for (; x < MN; x += x & -x)
        bit[x] += v;
}
int query(int x) {
    int sum = 0;
    for (; x; x -= x & -x)
        sum += bit[x];
    return sum;
}

vector<int> idx[MN];
map<pii, ll> sto; // num of pairs (i,j) s.t. a.first after a.second

ll C2(ll k) { return k*(k-1)/2; }
ll tot(ll f1, ll f2) { return C2(f1+f2) - C2(f1) - C2(f2); }
ll get(int a, int b) {
    ll ctot = tot(idx[a].size(), idx[b].size());
    if (sto.count({a, b})) return sto[{a, b}];
    else if (sto.count({b, a})) return ctot-sto[{b, a}];

    ll res = 0;
    if (idx[a].size() < idx[b].size()) {
        auto &v = idx[b];
        for (auto x : idx[a]) {
            res += lower_bound(v.begin(), v.end(), x)-v.begin();
        }
    }
    else {
        auto &v = idx[a];
        for (auto x : idx[b]) {
            res += v.end() - upper_bound(v.begin(), v.end(), x);
        }
    }

    return sto[{a, b}] = res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K >> Q;
    ll invc = 0;
    for (auto i = 1; i <= N; i++) {
        cin >> A[i];
        invc += query(K) - query(A[i]);
        add(A[i], 1);

        idx[A[i]].push_back(i);
    }
    iota(P+1, P+N+1, 1);

    while (Q--) {
        int x; cin >> x;

        ll ch = tot(idx[P[x]].size(), idx[P[x+1]].size()) - 2*get(P[x], P[x+1]);
        invc += ch;
        cout << invc << '\n';

        swap(P[x], P[x+1]);
    }

    return 0;
}