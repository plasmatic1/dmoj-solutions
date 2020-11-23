// ./summer-institute-17-contest-1-p4-clips-of-video.yml
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

struct suf {
    int idx, r1, r2;
    bool operator<(const suf &o) const {
        return r1 == o.r1 ? r2 < o.r2 : r1 < o.r1;
    }
};

const int MN = 1e5 + 1;
int N, M;
string A, B;

// SA
suf sa[MN];
int crnk[MN];
char getc(int idx, int col) {
    int cidx = sa[idx].idx + col;
    if (cidx >= N) return '$';
    return A[cidx];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (A) >> (B);
    N = SZ(A);
    M = SZ(B);

    // suffix... array?
    for (auto i = 0; i < N; i++)
        sa[i] = {i, A[i] - 'a', i + 1 < N ? A[i + 1] - 'a' : -1};
    sort(sa, sa + N);
    for (int i = 2; i <= N; i *= 2) {
        int ctr = 0;
        suf pre{-1, -INF, -INF};
        for (auto j = 0; j < N; j++) {
            if (sa[j].r1 != pre.r1 || sa[j].r2 != pre.r2) {
                pre = sa[j];
                ctr++;
            }
            sa[j].r1 = ctr;
            crnk[sa[j].idx] = ctr;
        }
        for (auto j = 0; j < N; j++)
            sa[j].r2 = sa[j].idx + i < N ? crnk[sa[j].idx + i] : -1;
        sort(sa, sa + N);
    }

    // oh my god
    int ans = 0;
    for (auto i = 0; i < M; ) {
        ans++;
        int lb = 0, rb = N - 1, pre = i, col = 0;
        while (lb <= rb) {
            // bsearch for new bounds
            int l = lb - 1, r = rb;
            while (l + 1 < r) {
                int mid = (l + r) / 2;
                if (getc(mid, col) >= B[i])
                    r = mid;
                else
                    l = mid;
            }
            int nlb = r;

            l = lb; r = rb + 1;
            while (l + 1 < r) {
                int mid = (l + r) / 2;
                if (getc(mid, col) > B[i])
                    r = mid;
                else
                    l = mid;
            }
            int nrb = l;

            // set variables
            lb = nlb; rb = nrb;
            if (getc(lb, col) != B[i]) break;
            col++; i++;
        }
        if (i == pre) {
            cout << (-1) << '\n';
            return 0;
        }
    }
    cout << (ans) << '\n';

    return 0;
}