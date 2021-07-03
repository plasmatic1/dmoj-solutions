// ./cco-21-p2-weird-numeral-system.yml
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

const pair<int, ll> BAD = {INF, LLINF};
const int MK = 1e6+1, SHF = 5e6+1;
int K, Q, D, M;
vector<int> md[MK];

unordered_map<ll, pair<int, ll>> par;
pair<int, ll> par2[SHF*2+5];

bool has(ll n) {
    if (abs(n) <= SHF) return par2[n+SHF] != BAD;
    return par.count(n);
}
void save(ll n, int d, ll p) {
    if (abs(n) <= SHF) par2[n+SHF] = {d, p};
    par[n] = {d, p};
}
pair<int, ll> get(ll n) {
    if (abs(n) <= SHF) return par2[n+SHF];
    return par[n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> K >> Q >> D >> M;
    for (auto i = 0; i < D; i++) {
        int x; cin >> x;
        md[((x%K)+K)%K].pb(x);
    }

    while (Q--) {
        ll n; cin >> n;

        par.clear();
        fill(par2, par2+SHF*2+5, BAD);

        ll st = n ? n : LLINF;
        queue<ll> q; q.push(st); save(st, -1, -1);
        while (!q.empty()) {
            auto n = q.front(); q.pop();
            if (n == 0) break;
            ll tv = n == LLINF ? 0 : n;
            for (auto d : md[((tv%K)+K)%K]) {
                ll alt = (tv-d)/K;
                if (!has(alt)) {
                    save(alt, d, n);
                    q.push(alt);
                }
            }
        }

        if (has(0)) {
            vector<int> ans;
            for (ll cur = 0; cur != st; cur = get(cur).second)
                ans.push_back(get(cur).first);
            for (auto i = 0; i < SZ(ans); i++) cout << ans[i] << " \n"[i == SZ(ans)-1];
        }
        else
            cout << ("IMPOSSIBLE") << '\n';
    }

    return 0;
}