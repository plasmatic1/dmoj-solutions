// ./ioi-11-p6-parrots.yml
#include "bits/stdc++.h"
using namespace std;

// Defines
#define fs first
#define sn second
#define pb push_back
#define eb emplace_back
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
int SZ(string &v) { return v.length(); }
template <typename C> int SZ(C &v) { return v.size(); }
template <typename C> void UNIQUE(vector<C> &v) { sort(v.begin(), v.end()); v.resize(unique(v.begin(), v.end()) - v.begin()); }
template <typename T, typename U> void maxa(T &a, U b) { a = max(a, b); }
template <typename T, typename U> void mina(T &a, U b) { a = min(a, b); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

/*

Stars/Bars per index:
- 4 (values) boxes per index
- 5 (items) items per index

Blocksize: 3 indices
- 12 boxes per index
- 15 items per index

Item Rep:
- Original: <8 bits><8 bits><8 bits> -> first to third bytes
- Encoded: <4 bits>*(12 times) -> 48 bits(storable in long long)

Note: We can actually just use 12 items per index instead of 15
*/

void send(int a);
void output(int b);

const ll B48 = (1LL << 48) - 1;
const int MB = 512, MN = 16777216;
ll code[MN], code2[256], code3[256];
bitset<MB> bb;
bool initd = false;

int ccnt[12];

ll getFreq(ll q) {
    int res = 0;
    while (q) res += q & 15, q >>= 4;
    return res;
}

void rec(int boxno, int itemleft, ll code[], int &found, int lim) {
    if (found == lim) return;
    if (boxno == -1) {
        ll enc = 0;
        for (auto i = 12-1; i >= 0; i--)
            enc = (enc << 4LL) | ccnt[i];
        code[found++] = enc | (getFreq(enc) << 48LL);
        return;
    }
    if (boxno == 0) {
        ccnt[0] = itemleft;
        rec(-1, 0, code, found, lim);
        return;
    }
    for (auto i = 0; i <= itemleft; i++) {
        ccnt[boxno] = i;
        rec(boxno - 1, itemleft - i, code, found, lim);
    }
}

void init() {
    int f1 = 0, f2 = 0, f3 = 0;
    for (auto i = 0; i <= 15; i++)
        rec(11, i, code, f1, MN);
    fill(ccnt, ccnt + 12, 0);
    for (auto i = 0; i <= 4; i++) // when at least 4 of the windows are maxed
        rec(3, i, code2, f2, 70);
    fill(ccnt, ccnt + 12, 0);
    for (auto i = 0; i <= 7; i++) // when there are less than 4 maxed windows
        rec(3, i, code3, f3, 256);
}

void encode(int N, int M[]) {
    if (!initd) {
        init();
        initd = true;
    }
    bool imax = N == 64;
    if (imax) N--;

    auto encodeSetCode = [&] (int startNum, ll encoded) {
        for (auto i = 0; i < 12; i++) {
            int cnt = encoded & 15;
            while (cnt--) send(startNum + i);
            encoded >>= 4LL;
        }
    };

    // encode for N<=63
    vector<int> cntMax;
    for (int i = 0; i < N; i += 3) {
        int idx = 0;
        for (auto j = i; j < min(i+3,N); j++)
            idx |= M[j] << (8 * (j - i));
        if ((code[idx] >> 48) == 15) cntMax.pb(i);
        encodeSetCode(i * 4, code[idx] & B48);
    }

    // encode N=64
    if (imax) {
        if (SZ(cntMax) >= 4) {
            send(cntMax[M[63] / 70] * 4);
            encodeSetCode(252, code2[M[63] % 70] & B48);
        }
        else
            encodeSetCode(252, code3[M[63]] & B48);
    }
}

void decode(int N, int L, int X[]) {
    if (!initd) {
        init();
        initd = true;
    }
    bool imax = N == 64;
    if (imax) N--;
    
    // get freq array
    vector<int> cnt(256);
    for (auto i = 0; i < L; i++) cnt[X[i]]++;

    auto decodeSetCode = [&] (int startPos, int maxUp) -> ll {
        ll res = 0;
        for (auto i = maxUp-1; i >= 0; i--)
            res = (res << 4LL) | cnt[startPos + i];
        return res | (getFreq(res) << 48LL);
    };

    // decode for N<=63
    int maxCnt = 0, overIdx = -1;
    for (int i = 0; i < N; i += 3) {
        // only when N=64
        int blockCnt = 0;
        for (auto j = 0; j < 12; j++) blockCnt += cnt[i * 4 + j];
        maxCnt += blockCnt == 15;
        if (blockCnt > 15) {
            overIdx = maxCnt;
            cnt[i * 4]--;
        }

        ll encoded = decodeSetCode(i * 4, 12);
        int idx = lower_bound(code, code + MN, encoded) - code;
        for (auto j = i; j < min(i+3,N); j++) {
            output(idx & 255);
            idx >>= 8;
        }
    }

    // decode N=64
    if (imax) {
        ll encoded = decodeSetCode(252, 4);
        if (overIdx != -1) {
            int idx = lower_bound(code2, code2 + 70, encoded) - code2;
            output(idx + 70 * overIdx);
        }
        else {
            int idx = lower_bound(code3, code3 + 256, encoded) - code3;
            output(idx);
        }
    }
}

#ifdef LOCAL
const int __N = 640;
int L = 0, E[__N];
void send(int a) { 
    if (a >= 256) {
        cout<<"a="<<(a)<<", "; cout << endl; // db a
        assert(a < 256);
    }
    E[L++] = a;
}
void output(int b) { cout << b << ' '; }
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    srand(6969);
    int N; cin >> N;
    int M[N];
    for (auto i = 0; i < N; i++) cin >> (M[i]);
    encode(N, M);
    random_shuffle(E, E + L);
    decode(N, L, E);

    return 0;
}
#endif