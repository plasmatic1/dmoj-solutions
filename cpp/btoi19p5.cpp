// baltic-oi-19-p5-necklace.yml
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

// Hashing stuff
const ll MODS[2] = {1000000007, 1000000009}, BASE[2] = {131, 191};
ll madd(ll a, ll b, ll mod) { return a + b; }
ll msub(ll a, ll b, ll mod) { return a - b; }
ll mmul(ll a, ll b, ll mod) { return a * b; }
ll fpow(ll x, ll y, ll mod) {
    if (!y) return 1LL;
    return mmul(fpow(mmul(x, x, mod), y >> 1, mod), (y & 1) ? x : 1LL, mod);
}
ll mdiv(ll x, ll y, ll mod) { return mmul(x, fpow(y, mod - 2, mod), mod); }

ll comb(ll lo, ll hi) { return (hi << 32) | lo; }
ll glo(ll x) { return x & ((1LL << 32) - 1); }
ll ghi(ll x) { return x >> 32; }
ll append1(ll hsh, int val, int i) { return madd(mmul(hsh, BASE[i], MODS[i]), val, MODS[i]); }
// ll append(ll hsh, int val) { return comb(append1(glo(hsh), val, 0), append1(ghi(hsh), val, 1)); } 
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
    return msub(hr, mmul(pows[i][sz], hl, MODS[i]), MODS[i]);
}
// ll ghsh(ll *hs, int l, int r) {
//     int sz = r - l + 1;
//     return comb(ghsh1(glo(hs[r]), glo(hs[l - 1]), sz, 0), ghsh1(ghi(hs[r]), ghi(hs[l - 1]), sz, 1));
// }
ll concat1(ll hsh, ll hsh2, int sz, int i) { return madd(mmul(hsh, pows[i][sz], MODS[i]), hsh2, MODS[i]); }
ll concat(ll hsh, ll hsh2, int sz) { return comb(concat1(glo(hsh), glo(hsh2), sz, 0), concat1(ghi(hsh), ghi(hsh2), sz, 1)); }

ll append(ll hsh, int val) { return append1(hsh, val, 0); } 
ll ghsh(ll *hs, int l, int r) {
    int sz = r - l + 1;
    return ghsh1(hs[r], hs[l - 1], sz, 0);
}

ostream& operator<<(ostream& out, const pii o) {
    out << "(first=" << o.first << ", second=" << o.second << ")";
    return out;
}
ostream& operator<<(ostream& out, const pair<int,pii> o) {
    out << "(first=" << o.first << ", second=" << o.second << ")";
    return out;
}

const int MN = 3011;
int N, M,
    f[MN], g[MN];
string s, t;
ll hs[MN], ht[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_pow(MN - 1);

    cin >> (s) >> (t);
    N = s.length(); M = t.length();

    pair<int, pii> ans{0, {1, 1}};
    for (auto rev = 0; rev < 2; rev++) {
        // Build hash
        for (auto i = 1; i <= N; i++)
            hs[i] = append(hs[i - 1], s[i - 1]);
        for (auto i = 1; i <= M; i++)
            ht[i] = append(ht[i - 1], t[i - 1]);

        // Funky stuff
        /*
         * AB|CD
         * CD|AB
         *  + 
         */
        for (auto i = 0; i <= N; i++) {
            fill(f, f + M + 1, 0);
            fill(g, g + M + 1, 0);

            // Build f and g arrays
            int fBound = i, gBound = N - i;
            for (auto j = 1; j <= M; j++) {
                int l = 0, r = min(j, fBound) + 1;
                while (l + 1 < r) {
                    int mid = (l + r) / 2;
                    if (ghsh(hs, i - mid + 1, i) == ghsh(ht, j - mid + 1, j))
                        l = mid;
                    else
                        r = mid;
                }
                maxa(f[j - l + 1], l);
            }
            for (auto j = 1; j <= M; j++) {
                int l = 0, r = min(M - j + 1, gBound) + 1;
                while (l + 1 < r) {
                    int mid = (l + r) / 2;
                    if (ghsh(hs, i + 1, i + mid) == ghsh(ht, j, j + mid - 1))
                        l = mid;
                    else
                        r = mid;
                }
                maxa(g[j + l - 1], l);
            }
            for (auto j = 1; j <= M; j++)
                maxa(f[j], f[j - 1] - 1);
            for (auto j = M; j >= 1; j--)
                maxa(g[j], g[j + 1] - 1);

            // g[j - 1] ++ f[j]
            for (auto j = 1; j <= M + 1; j++) {
                int len = g[j - 1] + f[j], l1 = i - f[j] + 1, l2 = rev ? M - (j + f[j] - 1) + 1: j - g[j - 1];
                if (len > 0)
                    maxa(ans, mpr(len, mpr(l1, l2)));
            }
        }

        reverse(all(t));
    }

    // Print ans
    cout << (ans.first) << '\n';
    cout << (ans.second.first - 1) << ' ' << (ans.second.second - 1) << '\n';

    return 0;
}