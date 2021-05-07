// ./cco-12-p6-the-winds-of-war.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

struct pt {
    ll x, y;
    int half() { return x < 0 || (x == 0 && y < 0); }
    ll cross(const pt o) { // positive if A is CCW to B
        return x*o.y - y*o.x; }
    pt operator-(const pt o) const { return {x-o.x, y-o.y}; }
};
istream& operator>>(istream& in, pt &o) {
    return in >> o.x >> o.y;
}

ll shoe2(const pt a, const pt b, const pt c) { // shoelace algorithm*2
    return abs(a.x*b.y + b.x*c.y + c.x*a.y - a.y*b.x - b.y*c.x - c.y*a.x);
}

const int MN = 101;
int N,
    V[MN], dp[MN][MN], adv[MN][MN]; // adv=advantage
pt pos[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    {
        int p, t; cin >> p >> t;
        N = p+t;
        for (auto i = 1; i <= p; i++) {
            cin >> pos[i];
            V[i] = 1;
        }
        for (auto i = p+1; i <= p+t; i++) {
            cin >> pos[i];
            V[i] = -1;
        }
    }

    // find cost of every triangle
    const pt ORI = {0, 0};
    for (auto i = 1; i <= N; i++) {
        for (auto j = 1; j <= N; j++) {
            if (i == j) continue;
            for (auto k = 1; k <= N; k++) {
                if (shoe2(ORI, pos[i], pos[j]) == shoe2(ORI, pos[i], pos[k]) + shoe2(ORI, pos[j], pos[k]) + shoe2(pos[i], pos[j], pos[k]))
                    adv[i][j] += V[k]; 
            }
        }
    }
    // order points clockwise
    vector<int> ord(N); iota(ord.begin(), ord.end(), 1);
    sort(ord.begin(), ord.end(), [&] (const int a, const int b) {
        int ah = pos[a].half(), bh = pos[b].half();
        if (ah != bh) return ah > bh; // left side first
        return pos[a].cross(pos[b]) < 0;
    });
    ord.insert(ord.begin(), 0); // start with (0,0)

    memset(dp, -0x3f, sizeof dp);
    for (auto i = 1; i <= N; i++) dp[0][i] = 1;

    int ans = 0;
    for (auto _i = 0; _i < (int)ord.size(); _i++) {
        int i = ord[_i];
        for (auto _j = 0; _j < _i; _j++) {
            for (auto _k = _j+1; _k < _i; _k++) {
                int p2 = ord[_j], p1 = ord[_k];
                if ((pos[i]-pos[p1]).cross(pos[p1]-pos[p2]) > 0)
                    dp[p1][i] = max(dp[p1][i], dp[p2][p1] + adv[p1][i] - 1); // points on corners are counted twice

                ans = max(ans, dp[p1][i]);
            }
        }
    }

    cout << ans << '\n';

    return 0;
}