#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 2001;
int N;
bool adj[MN][MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;

    for (int i = 2; i <= N; ++i) {
        string tmp;
        cin >> tmp;
        for (int j = 1; j < i; ++j) {
            bool t = tmp[j - 1] == 'R';
            adj[i][j] = adj[j][i] = t;
        }
    }

    for (int i = 1; i <= N; ++i) {
        deque<int> dq[2];

        vector<int> ord;
        for (int j = 0; j < N - 1; ++j) {
            int v = (i + j) % N + 1;
            ord.push_back(v);
        }
        ord.push_back(i);
        for (int x : ord) {
            if (dq[0].empty())
                dq[0].push_back(x);
            else if (dq[1].empty())
                dq[1].push_back(x);
            else if (adj[dq[0].back()][x] == 0) 
                dq[0].push_back(x);
            else if (adj[dq[1].back()][x] == 1)
                dq[1].push_back(x);
            else {
                bool use = adj[dq[0].back()][dq[1].back()];
                dq[use].push_back(dq[!use].back());
                dq[!use].pop_back();
                dq[use].push_back(x);
            }
        }

        cout << N << '\n';
        if (!dq[1].empty() && dq[1].back() == i) swap(dq[0], dq[1]);
        for (int j = 0; j < 2; j++) {
            while (!dq[j].empty()) {
                cout << dq[j].back() << ' ';
                dq[j].pop_back();
            }
        }
        cout << '\n';
    }

    return 0;
}