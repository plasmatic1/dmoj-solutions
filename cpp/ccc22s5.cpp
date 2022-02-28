#include "bits/stdc++.h"
using namespace std;

using P = pair<string, string>;
using ll = long long;
using pii = pair<int, int>;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

#define SZ(v) (int(v.size()))

const int MN = 4e5 + 1;
int N, 
    C[MN];
bool done[MN];
vector<int> g[MN];

int dp[MN][4]; // 0 -> selected, 1 -> not selected
// 0 -> defer to parent, 1 -> selected but not paid, 2 -> paid, 3 -> paid but needs adj to pay
//
// done = true || 1, 2
// done = false || 0, 1, 2, 3

void dfs(int c, int p) {
    for (auto to : g[c]) {
        if (to != p) {
            dfs(to, c);
        }
    }

    if (done[c]) {
        int allChSum = 0;
        dp[c][0] = INF; // impossible
        dp[c][3] = INF; // impossible

        for (auto to : g[c]) {
            if (to != p) {
                // 1
                dp[c][1] += min(dp[to][1], dp[to][2]); 
                // 2
                allChSum += min({dp[to][0], dp[to][1], dp[to][2], dp[to][3]});

                dp[c][1] = min(dp[c][1], (int)INF);
                allChSum = min(allChSum, (int)INF);
            }
        }

        // costs computed at end
        dp[c][2] = min((int)INF, allChSum + C[c]);
    }
    else {
        int allChSum = 0, doneChSum = 0;
        // 2, (2 or 3)
        int childToEnable = INF, childToCondEnable = INF;
        for (auto to : g[c]) {
            if (to != p) {
                int curAllSum = min({dp[to][0], dp[to][1], dp[to][2], dp[to][3]}), curDoneSum = min(dp[to][1], dp[to][2]);
                // 0
                dp[c][0] += min(dp[to][1], dp[to][2]);
                // 1
                doneChSum += curDoneSum; // anything thats done
                allChSum += curAllSum;

                childToEnable = min(childToEnable, dp[to][2] - curDoneSum);
                childToCondEnable = min(childToCondEnable, dp[to][2] - curAllSum);
                // 2, 3

                doneChSum = min(doneChSum, (int)INF);
                allChSum = min(allChSum, (int)INF);
                dp[c][0] = min(dp[c][0], (int)INF);
            }
        }

        // costs computed at end
        dp[c][1] = min((int)INF, childToEnable + doneChSum);
        dp[c][2] = min((int)INF, childToCondEnable + allChSum + C[c]);
        dp[c][3] = min((int)INF, allChSum + C[c]);
    }

    // help
    // printf("c=%d done=%d dp=%d %d %d %d\n", c,done[c],dp[c][0],dp[c][1],dp[c][2],dp[c][3]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (auto i = 1; i < N; i++) {
        int a, b; cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    string s; cin >> s;
    for (auto i = 0; i < N; i++) {
        if (s[i] == 'Y')
            done[i+1] = true;
    }
    for (auto i = 1; i <= N; i++)
        cin >> C[i];

    // force leaves to be done
    // int oldN = N;
    // for (auto i = 1; i <= oldN; i++) {
    //     if (SZ(g[i]) == 1 && !done[i]) {
    //         int n = ++N;
    //         g[i].push_back(n);
    //         g[n].push_back(i);
    //         done[n] = true;
    //     }
    // }

    int fnd = -1;
    for (auto i = 1; i <= N; i++) {
        if (done[i]) {
            fnd = i;
            break;
        }
    }

    dfs(fnd, -1);

    int ans = min(dp[fnd][1], dp[fnd][2]);
    cout << ans << '\n';

    return 0;
}