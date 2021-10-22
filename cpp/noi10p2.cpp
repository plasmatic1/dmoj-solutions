// ./p2-super-piano.yml
#include <bits/stdc++.h>
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

const int MN = 5e5 + 1;
int N, K, L, R,
    psum[MN];

struct Comp {
    using Data = int;
    Data merge(Data a, Data b) {
        int v1 = psum[a-1], v2 = psum[b-1];
        if (v1 < v2) return a;
        else if (v1 > v2) return b;
        return min(a, b);
    }
};
template <class Comp> struct SparseTable {
    using Data = typename Comp::Data; Comp C;
    vector<vector<Data>> tb;
    int N, lg;
    template <typename It> void init(It st, It end) {
        N = end-st; lg = __lg(N);
        tb.assign(lg+1, vector<Data>(N+1));
        copy(st, end, tb[0].begin()+1);
        for (auto i = 1; i <= lg; i++) {
            int jmp = 1 << (i-1), end = N - (1<<i) + 1;
            for (auto j = 1; j <= end; j++)
                tb[i][j] = C.merge(tb[i-1][j], tb[i-1][j+jmp]);
        }
    }
    Data query(int l, int r) {
        int bit = __lg(r-l+1);
        return C.merge(tb[bit][l], tb[bit][r-(1<<bit)+1]);
    }
};

SparseTable<Comp> st;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K >> L >> R;
    for (auto i = 1; i <= N; i++) {
        cin >> psum[i];
        psum[i] += psum[i-1];
    }
    {
        vector<int> tmp(N); iota(all(tmp), 1);
        st.init(all(tmp));
    }

    using T = tuple<int, int, int, int>;
    priority_queue<T> pq;

    auto addSeg = [&] (int l, int r, int rp) {
        if (l > r) return;
        pq.emplace(psum[rp] - psum[st.query(l, r)-1], l, r, rp);
    };

    for (auto i = L; i <= N; i++)
        addSeg(max(1, i-R+1), i-L+1, i);
    int left = K;
    ll ans = 0;
    while (!pq.empty()) {
        auto [w, l, r, rp] = pq.top(); pq.pop();
        // cout<<"w="<<(w)<<", "; cout<<"l="<<(l)<<", "; cout<<"r="<<(r)<<", "; cout<<"rp="<<(rp)<<", "; cout<<"st.query(l,r)="<<(st.query(l,r))<<", "; cout << endl; // db w,l,r,rp,st.query(l,r)
        ans += w;
        if (--left == 0) break;

        int best = st.query(l, r);
        addSeg(l, best-1, rp);
        addSeg(best+1, r, rp);
    }

    cout << (ans) << '\n';

    return 0;
}