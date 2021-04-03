// ./coci-20-contest-3-3-sateliti.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const ll mod = (1LL << 61) - 1, base = 131;
ll mulmod(ll a, ll b) {
    return __int128(a) * b % mod;
}

const int MN = 2001;
int N, M;
string grid[MN];

ll pw[MN*MN];
ll ghsh(ll *hs, int l, int r) {
    return (hs[r] - mulmod(hs[l-1], pw[r-l+1]) + mod) % mod;
}

// rowHs -> cumulative hash value for each row, colHs[i][j] = hash(grid[0][i..i+M] + grid[1][i..i+M] + ... + grid[j][i..i+M])
ll rowHs[MN][MN], colHs[MN][MN];

ll subgridHash(int i, int j, int ncells) {
    int completeRows = ncells / M, start = i + completeRows, left = ncells % M;
    ll res = (colHs[j][start] - mulmod(colHs[j][i], pw[completeRows * M]) + mod) % mod;
    res = (mulmod(res, pw[left]) + ghsh(rowHs[start], j+1, j+left)) % mod;

    return res;
}

char kth(int i, int j, int ncells) {
    i += ncells / M;
    ncells %= M;
    return grid[i][j + ncells];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    pw[0] = 1;
    for (auto i = 1; i < MN*MN; i++) pw[i] = mulmod(pw[i-1], base);

    cin >> N >> M;
    for (auto i = 0; i < N; i++) {
        cin >> grid[i];
        grid[i] += grid[i];
    }
    for (auto i = N; i < 2*N; i++)
        grid[i] = grid[i-N];

    // calculate hash uwu
    for (auto i = 0; i < 2*N; i++)
        for (auto j = 0; j < 2*M; j++)
            rowHs[i][j+1] = (mulmod(rowHs[i][j], base) + grid[i][j]) % mod;
    for (auto i = 0; i < M; i++)
        for (auto j = 0; j < 2*N; j++)
            colHs[i][j+1] = (mulmod(colHs[i][j], pw[M]) + ghsh(rowHs[j], i+1, i+M));

    int br = 0, bc = 0;
    for (auto i = 0; i < N; i++) {
        for (auto j = 0; j < M; j++) {
            int l = 0, r = N*M+1;
            while (l + 1 < r) {
                int mid = (l + r) / 2;
                if (subgridHash(br, bc, mid) == subgridHash(i, j, mid)) l = mid;
                else r = mid;
            }
            if (l < N*M) {
                if (kth(i, j, l) < kth(br, bc, l)) {
                    br = i;
                    bc = j;
                }
            }
        }
    }

    for (auto i = br; i < br+N; i++) {
        for (auto j = bc; j < bc+M; j++)
            cout << grid[i][j];
        cout << '\n';
    }

    return 0;
}