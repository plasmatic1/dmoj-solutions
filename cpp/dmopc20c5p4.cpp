// ./dmopc-20-contest-5-p4-slacking-off.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

// PBDS order statistic tree
#include <ext/pb_ds/assoc_container.hpp> // Common file 
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds; 
template <typename T, class comp = less<T>> using os_tree = tree<T, null_type, comp, rb_tree_tag, tree_order_statistics_node_update>;
template <typename K, typename V, class comp = less<K>> using treemap = tree<K, V, comp, rb_tree_tag, tree_order_statistics_node_update>;
// HashSet
#include <ext/pb_ds/assoc_container.hpp>
template <typename T, class Hash> using hashset = gp_hash_table<T, null_type, Hash>;
template <typename K, typename V, class Hash> using hashmap = gp_hash_table<K, V, Hash>;
const ll RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash { ll operator()(ll x) const { return x ^ RANDOM; } };

// using i128 = __int128;
// const i128 PR = 9223372036854775783;

// Hashing stuff
const ll MODS[2] = {1000000007, 1000000009}, BASE[2] = {131, 191};
ll madd(ll a, ll b, ll mod) { return (a + b) % mod; }
ll msub(ll a, ll b, ll mod) { return (a - b + mod) % mod; }
ll mmul(ll a, ll b, ll mod) { return (a * b) % mod; }
ll fpow(ll x, ll y, ll mod) {
    if (!y) return 1LL;
    return mmul(fpow(mmul(x, x, mod), y >> 1, mod), (y & 1) ? x : 1LL, mod);
}
ll mdiv(ll x, ll y, ll mod) { return mmul(x, fpow(y, mod - 2, mod), mod); }

ll comb(ll lo, ll hi) { return (hi << 32) | lo; }
ll glo(ll x) { return x & ((1LL << 32) - 1); }
ll ghi(ll x) { return x >> 32; }
// ll append1(ll hsh, int val, int i) { return madd(mmul(hsh, BASE[i], MODS[i]), val, MODS[i]); }
ll append1(ll hsh, int val, int i) { return (hsh*BASE[i]+val)%MODS[i]; }
ll append(ll hsh, int val) { return comb(append1(glo(hsh), val, 0), append1(ghi(hsh), val, 1)); } 
vector<ll> pows[2];
void init_pow(int N) {
    for (auto i = 0; i < 2; i++) {
        pows[i].resize(N + 1);
        pows[i][0] = 1LL;
        for (auto j = 1; j <= N; j++)
            pows[i][j] = mmul(pows[i][j - 1], BASE[i], MODS[i]);
    }
}
ll ghsh1(ll hr, ll hl, int sz, int i) {
    // return msub(hr, mmul(pows[i][sz], hl, MODS[i]), MODS[i]);
    ll ret = (hr-pows[i][sz]*hl)%MODS[i];
    if (ret < 0) ret += MODS[i];
    return ret;
}
ll ghsh(ll *hs, int l, int r) {
    int sz = r - l + 1;
    return comb(ghsh1(glo(hs[r]), glo(hs[l - 1]), sz, 0), ghsh1(ghi(hs[r]), ghi(hs[l - 1]), sz, 1));
}
// ll ghsh(ll *hs, int l, int r) { return 0; }
ll concat1(ll hsh, ll hsh2, int sz, int i) { return madd(mmul(hsh, pows[i][sz], MODS[i]), hsh2, MODS[i]); }
ll concat(ll hsh, ll hsh2, int sz) { return comb(concat1(glo(hsh), glo(hsh2), sz, 0), concat1(ghi(hsh), ghi(hsh2), sz, 1)); }

const int MN = 2e5 + 1;
int R, C;
string grid[MN];

ll* hsh[MN];
int lit[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_pow(MN);

    cin >> R >> C;
    for (auto i = 0; i < R; i++) cin >> grid[i];

    if (R > C) {
        string _tmp[MN];
        for (auto i = 0; i < C; i++) _tmp[i].assign(R, '$');
        for (auto i = 0; i < C; i++)
            for (auto j = 0; j < R; j++)
                _tmp[i][j] = grid[j][i];

        swap(R, C);
        swap(grid, _tmp);
    }
    assert(R<=C);

    // printf("R=%d C=%d\n", R,C);
    // for (auto i = 0; i < R; i++)
        // printf("%s\n", grid[i].c_str());

    // hashes
    for (auto i = 0; i < C; i++) {
        hsh[i] = new ll[R+1]; fill(hsh[i], hsh[i]+R+1, 0);
        for (auto j = 0; j < R; j++) {
            // hsh[i][j+1] = append(hsh[i][j], grid[j][i]);
            hsh[i][j+1] = append1(hsh[i][j], grid[j][i], 0);
        }
    }

    ll ans = 0;
    for (auto i = 0; i < R; i++) {
        for (auto j = i+1; j < R; j++) {
            // printf("--- i=%d j=%d\n", i,j);

            // get left pointer
            for (auto k = C-1; k >= 0; ) {
                int nxt = k;
                while (nxt >= 0 && grid[i][nxt] == grid[j][nxt]) nxt--;
                // printf("k=%d nxt=%d\n", k,nxt);

                if (nxt == k) {
                    lit[k] = k;
                    k = nxt-1;
                }
                else {
                    unordered_map<ll, int> fre;
                    for (auto l = nxt+1; l <= k; l++) {
                        // lit[l] = nxt+1;
                        ll hs = ghsh1(hsh[l][j+1], hsh[l][i], j-i+1, 0);
                        fre[hs]++;
                    }
                    for (auto [_, v] : fre) ans += ll(v)*(v-1)/2;
                    k = nxt;
                }
            }

            // // ava did you do this????
            // vector<pair<ll, int>> vs;
            // for (auto k = 0; k < C; k++) {
            //     // vs.emplace_back(ghsh(hsh[k], i+1, j+1), k);
            //     vs.emplace_back(ghsh1(hsh[k][j+1], hsh[k][i], j-i+1, 0), k);
            // }
            // sort(vs.begin(), vs.end());
            // for (auto L = 0; L < C; ) {
            //     int R = L;
            //     while (R < C && vs[R].first == vs[L].first) R++;
            //     R--;
            //
            //     // printf("SECT L=%d R=%d\n", L,R);
            //
            //     int ptr = R;
            //     for (auto k = R; k >= L; k--) {
            //         int idx = vs[k].second;
            //         while (ptr >= L && vs[ptr].second >= lit[idx]) ptr--;
            //         
            //         // printf("k=%d lit=%d ptr=%d\n", k,lit[k],ptr);
            //
            //         ans += k-ptr-1;
            //     }
            //
            //     L = R+1;
            // }

            // for (auto k = 0; k < C; k++) {
            //     // printf("k=%d lit=%d\n", k,lit[k]);
            //     ll hs = ghsh(hsh[k], i+1, j+1);
            //     auto &v = ind[hs];
            //     ans += v.end() - lower_bound(v.begin(), v.end(), lit[k]);
            //
            //     v.push_back(k);
            // }
        }
    }

    cout << ans << '\n';

    return 0;
}