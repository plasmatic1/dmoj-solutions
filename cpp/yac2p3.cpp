// ./p3-maximum-damage.yml
#include <bits/stdc++.h>
#define DEBUG 0
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
#if __cplusplus == 201703L // CPP17 only things
template <typename T> using opt_ref = optional<reference_wrapper<T>>; // for some templates
#endif
using ll = long long; using ull = unsigned long long; using ld = long double;
using pii = pair<int, int>; using pll = pair<long long, long long>;
#ifdef __GNUG__
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
#endif
// More utilities
int SZ(string &v) { return v.length(); }
template <typename C> int SZ(C &v) { return v.size(); }
template <typename C> void UNIQUE(vector<C> &v) { sort(v.begin(), v.end()); v.resize(unique(v.begin(), v.end()) - v.begin()); }
template <typename T, typename U> void maxa(T &a, U b) { a = max(a, b); }
template <typename T, typename U> void mina(T &a, U b) { a = min(a, b); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 3e6 + 1, MV = 1e6 + 1, ML = 20; // log2(MV)
int N, K;

int jmp[MV];
int cnt[MV][ML], cntTot[MV];

int getTake(int &a, int &b) {
    int tk = min(a, b);
    a -= tk;
    b -= tk;
    return tk;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    iota(jmp, jmp+MV, 0);
    for (auto i = 2; i < MV; i++) {
        if (jmp[i] == i) {
            for (auto j = i+i; j < MV; j += i)
                jmp[j] = i;
        }
    }

    cin >> N >> K;
    for (auto i = 0; i < N; i++) {
        int x; cin >> x;
        int pre = 1, ccnt = 0;
        for (auto c = x; c != 1; c /= jmp[c]) {
            if (jmp[c] != pre) {
                if (pre != 1) {
                    cnt[pre][ccnt]++;
                    cntTot[pre] += ccnt;
                }
                ccnt = 1;
                pre = jmp[c];
            }
            else
                ccnt++;
        }
        if (pre != 1) {
            cnt[pre][ccnt]++;
            cntTot[pre] += ccnt;
        }
    }

    int ans = 0;
    for (auto i = 1; i < MV; i++) {
        if (cntTot[i] > 0) {
            while (1) {
                int left = K;

                int tkPrev = getTake(left, cnt[i][ML-1]);
                for (auto j = ML-2; j >= 1; j--) {
                    if (left == 0) {
                        cnt[i][j] += tkPrev;
                        break;
                    }
                    int tk = getTake(left, cnt[i][j]);
                    cnt[i][j] += tkPrev;
                    tkPrev = tk;
                }

                if (left == 0) ans++;
                else break;
            }
        }
    }
    cout << (ans) << '\n';

    return 0;
}