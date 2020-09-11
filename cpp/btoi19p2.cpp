// boi-2019-p2-nautilus.yml
#include "bits/stdc++.h"
using namespace std;

// Defines
#define pb push_back
#define mpr make_pair
#define mtp make_tuple
#define all(x) (x).begin(), (x).end()
// Basic type definitions
using ll = long long; using ull = unsigned long long; using ld = long double;
using pii = pair<int, int>; using pll = pair<long long, long long>;
// PBDS order statistic tree
#include <ext/pb_ds/assoc_container.hpp> // Common file 
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds; 
template <typename T, class comp = less<T>> using os_tree = tree<T, null_type, comp, rb_tree_tag, tree_order_statistics_node_update>;
template <typename K, typename V, class comp = less<K>> using treemap = tree<K, V, comp, rb_tree_tag, tree_order_statistics_node_update>;
// HashSet
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
const ll RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash { ll operator()(ll x) const { return x ^ RANDOM; } };
template <typename T, class Hash> using hashset = gp_hash_table<T, null_type, Hash>;
template <typename K, typename V, class Hash> using hashmap = gp_hash_table<K, V, Hash>;
// More utilities
template <typename C> int SZ(C &v) { return v.size(); }
template <typename T, typename U> void maxa(T &a, U b) { a = max(a, b); }
template <typename T, typename U> void mina(T &a, U b) { a = min(a, b); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MR = 501, MN = 5001;
int R, C, N;
bitset<MR> can[MR], good[MR];
string ins;

void bcopy(bitset<MR> f[MR], bitset<MR> t[MR]) {
    copy(f, f + R, t);
}

// up, down, left, right
void bmove(bitset<MR> b[MR], int dir) {
    if (dir == 0) {
        for (auto i = 0; i < R - 1; i++)
            b[i] = b[i + 1];
        b[R - 1].reset();
    }
    else if (dir == 1) {
        for (auto i = R - 1; i > 0; i--)
            b[i] = b[i - 1];
        b[0].reset();
    }
    else if (dir == 3) { // Right == Left shift, Left == Right shift
        for (auto i = 0; i < R; i++) {
            b[i] <<= 1;
            b[i][C] = false;
        }
    }
    else {
        for (auto i = 0; i < R; i++)
            b[i] >>= 1;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Init dirmap
    map<char, int> dirMap;
    for (auto i = 0; i < 4; i++)
        dirMap["NSWE"[i]] = i;

    // Input
    cin >> (R) >> (C) >> (N);
    for (auto i = 0; i < R; i++) {
        string tmp;
        cin >> tmp;
        for (auto j = 0; j < C; j++)
            good[i][j] = tmp[j] == '.';
    }
    cin >> (ins);

    // Go in reverse
    bcopy(good, can);
    for (auto i = 0; i < N; i++) {
        char c = ins[i];
        if (c == '?') {
            bitset<MR> tmp[MR];
            for (auto j = 0; j < 4; j++) {
                bitset<MR> ttmp[MR];
                bcopy(can, ttmp);
                bmove(ttmp, j);
                for (auto k = 0; k < R; k++)
                    tmp[k] |= ttmp[k];
            }
            bcopy(tmp, can);
        }
        else
            bmove(can, dirMap[c]);

        for (auto j = 0; j < R; j++)
            can[j] &= good[j];
    }

    // Get ans
    int ans = 0;
    for (auto i = 0; i < R; i++)
        ans += can[i].count();
    cout << (ans) << '\n';

    return 0;
}