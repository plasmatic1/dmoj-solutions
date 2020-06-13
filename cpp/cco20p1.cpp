#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

using pii = pair<int, int>;
const int MN = 1e5 + 1;
int N;
ll L, R, Y;

vector<pii> amt;
map<int, int> ch;

void norm(ll &x) {
    x = max(x, L);
    x = min(x, R);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> N >> L >> R >> Y;
    ch[L] = ch[R + 1] = 0;
    for (int i = 0; i < N; ++i) {
        ll x, v, h;
        cin >> x >> v >> h;

        ll gv = gcd(v, h);
        v /= gv;
        h /= gv;
        
        ll lhs, rhs;
        if (Y % v == 0) {
            ll dif = (Y / v) * h;
            lhs = x - dif + 1;
            rhs = x + dif - 1;
        }
        else {
            ll dif = (Y * h) / v;
            lhs = x - dif;
            rhs = x + dif;
        }
        
        norm(lhs);
        norm(rhs);
        ch[lhs]++;
        ch[rhs + 1]--;
    }

    vector<pii> use(ch.begin(), ch.end());
    int sz = use.size(), curAmt = 0;
    for (int i = 0; i < sz - 1; ++i) {
        int dif = use[i + 1].first - use[i].first;
        curAmt += use[i].second;
        amt.emplace_back(curAmt, dif);
    }
    sort(amt.begin(), amt.end());

    int ptr = 0, cnt = 0;
    sz = amt.size();
    for (int i = 0; i <= N; i++) {
        while (ptr < sz && amt[ptr].first <= i) {
            cnt += amt[ptr].second;
            ptr++;
        }
        cout << cnt << '\n';
    }

    return 0;
}