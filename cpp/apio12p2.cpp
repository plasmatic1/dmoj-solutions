// ./apio-12-p2-guard.yml
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

struct Seg {
    int l, r, k;
};
istream& operator>>(istream &in, Seg &o) {
    in >> o.l >> o.r >> o.k;
    return in;
}

const int MN = 1e5 + 10;
int N, M, K;
Seg segs[MN];

// dp stuff
int bad[MN], dp[MN], par[MN];
vector<int> need[MN];
set<int> init;

void runDp(int l, int r) {
    for (auto i = l+1; i <= r; i++) dp[i] = INF;
    dp[l] = par[l] = 0;

    int req = l - 1;
    deque<int> dq; dq.pb(l); // increasing q
    for (auto i = l + 1; i <= r; i++) {
        for (auto x : need[i - 1])
            maxa(req, x);
        while (!dq.empty() && dq.front() < req)
            dq.pop_front();

        // cout<<"j="<<(j)<<", "; cout << "dq=["; for (auto __x:dq)cout<<__x<<", "; cout<<"], "; cout<<"req="<<(req)<<", "; cout << endl; // db j,I:dq,req
        // cout << "need[j-1]=["; for (auto __x:need[j-1])cout<<__x<<", "; cout<<"], "; cout << endl; // db I:need[j-1]

        if (bad[i] == 0 && !dq.empty()) {
            int alt = dp[dq.front()] + 1;
            if (alt < dp[i]) {
                dp[i] = alt;
                par[i] = dq.front();
            }
        }
        while (!dq.empty() && dp[i] < dp[dq.back()])
            dq.pop_back();
        dq.pb(i);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (K) >> (M);
    for (auto i = 0; i < M; i++) {
        cin >> (segs[i]);
        Seg &s = segs[i]; 
        // cout<<"s.l="<<(s.l)<<", "; cout<<"s.r="<<(s.r)<<", "; cout<<"s.k="<<(s.k)<<", "; cout << endl; // db s.l,s.r,s.k
        if (s.k) {
            need[s.r].pb(s.l);
            // if (s.l <= 6 && s.r >= 6) {
            //     cout<<"s.l="<<(s.l)<<", "; cout<<"s.r="<<(s.r)<<", "; cout << endl; // db s.l,s.r
            // }
        }
        else {
            bad[s.l]++;
            bad[s.r + 1]--;
        }
    }
    partial_sum(bad, bad + N + 2, bad);

    int rem = 0;
    for (auto i = 1; i <= N; i++)
        rem += bad[i] == 0;

    runDp(0, N + 1);
    int initCost = dp[N + 1] - 1;
    for (int c = par[N + 1]; c; c = par[c])
        init.insert(c);
    init.insert(0); init.insert(N + 1);

    if (rem == K) {
        for (auto i = 1; i <= N; i++)
            if (!bad[i])
                cout << (i) << '\n';
        return 0;
    }

    // for slow/fasting
    if (initCost > K || rem < K) {
        cout << ("nogud") << '\n';
        return 0;
    }

    // cout << "init=["; for (auto x:init)cout<<x<<", "; cout<<"], "; cout << endl; // db I:init
    
    int goextra = 10;

    vector<int> ans;
    for (auto i : init) {
        if (i > N || i < 1) continue;
        auto nxt = init.upper_bound(i), pre = --init.find(i);
        int sub1 = 1;
        for (auto j = 0; j < goextra; j++) {
            if (*nxt <= N) nxt++, sub1++;
            if (*pre >= 1) pre--, sub1++;
        }
        int l = *pre, r = *nxt;

        bad[i]++; runDp(l, r); bad[i]--;
        int newCost = initCost - sub1 + (dp[r] - 1);
        // cout<<"i="<<(i)<<", "; cout<<"newCost="<<(newCost)<<", "; cout<<"rem-1="<<(rem-1)<<", "; cout << endl; // db i,newCost,rem-1
        // cout<<"i="<<(i)<<", "; cout<<"initCost="<<(initCost)<<", "; cout<<"K="<<(K)<<", "; cout<<"newCost="<<(newCost)<<", "; cout<<"rem="<<(rem)<<", "; cout << endl; // db i,initCost,K,newCost,rem
        if (newCost > K || rem - 1 < K)
            ans.pb(i);
    }

    if (ans.empty())
        cout << (-1) << '\n';
    else {
        for (auto x : ans)
            cout << (x) << '\n';
    }

    return 0;
}