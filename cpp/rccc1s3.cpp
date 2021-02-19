// ./birthday-sorting.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;
#define pb push_back

const int MN = 1001, MM = MN*(MN-1)/2;
int N, M,
    A[MN];
vector<pii> g[MN], ops;

vector<int> ord, idx, val;
bool vis[MN], bad[MM];
void dfs(int c, int p) {
    idx.push_back(c);
    val.push_back(A[c]);
    for (auto to : g[c]) {
        if (to.first == p) continue;
        if (!vis[to.first]) {
            vis[to.first] = true;
            dfs(to.first, c);
        }
        else
            bad[to.second] = true;
    }
    ord.push_back(c);
}

vector<int> path;
bool explore(int c, int p, int end) {
    if (c == end) { path.push_back(end); return true; }
    bool found = false;
    for (auto to : g[c]) {
        if (bad[to.second]) continue;
        if (to.first != p)
            found |= explore(to.first, c, end);
    }
    if (found) path.push_back(c);
    return found;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    for (int i = 1; i <= N; i++) cin >> A[i];
    for (int i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        g[a].push_back({b, i});
        g[b].push_back({a, i});
    }

    for (int i = 1; i <= N; i++) {
        if (!vis[i]) {
            ord.clear();
            idx.clear();
            val.clear();
            vis[i] = true;
            dfs(i, -1);

            sort(idx.begin(), idx.end());
            sort(val.begin(), val.end());
            map<int, int> idxOf;
            for (int i = 0; i < int(idx.size()); i++)
                idxOf[idx[i]] = i;

            int ptr = 0;
            for (auto x : ord) {
                int want = val[idxOf[x]], start = -1;
                for (int i = 1; i <= N; i++) {
                    if (A[i] == want) {
                        start = i;
                        break;
                    }
                }
                assert(start != -1);

                path.clear();
                explore(start, -1, x);
                reverse(path.begin(), path.end());
                for (int j = 0; j < (int)path.size()-1; j++) {
                    swap(A[path[j]], A[path[j+1]]);
                    ops.emplace_back(path[j], path[j+1]);
                }

                ptr++;
            }
        }
    }

    cout << ops.size() << '\n';
    for (int i = 1; i <= N; i++) cout << A[i] << ' ';
    cout << '\n';
    for (auto p : ops)
        cout << p.first << ' ' << p.second << '\n';

    return 0;
}