// ./dmopc-20-contest-7-p1-bob-and-balance.yml
// going through personal issues rn but gotta do dmopc first :)
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
// template <typename T> using opt_ref = optional<reference_wrapper<T>>; // for some templates
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

const int MN = 1e6+1;
int N;
map<int, int> fre;
map<int, vector<int>> ind;

int getind(int k) {
    auto &v = ind[k];
    assert(!v.empty());
    int res = v.back(); v.pop_back();
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N; N *= 2;
    for (auto i = 0; i < N; i++) {
        int x; cin >> x;
        fre[x]++;
        ind[x].pb(i+1);
    }
    priority_queue<pii> pq;
    for (auto [k, v] : fre)
        pq.emplace(v, k);

    int ans = 0;
    vector<pii> res;
    for (auto i = 0; i < N/2; i++) {
        auto [f1, v1] = pq.top(); pq.pop();
        // cout<<"i="<<(i)<<", "; cout << endl; // db i
        if (!pq.empty()) {
            ans++;
            auto [f2, v2] = pq.top(); pq.pop();
            // cout<<"f1="<<(f1)<<", "; cout<<"v1="<<(v1)<<", "; cout<<"f2="<<(f2)<<", "; cout<<"v2="<<(v2)<<", "; cout << endl; // db f1,v1,f2,v2
            f1--; f2--;
            int a = getind(v1), b = getind(v2);
            res.eb(a, b);

            if (f2) pq.emplace(f2, v2);
        }
        else {
            // cout<<"f1="<<(f1)<<", "; cout<<"v1="<<(v1)<<", "; cout << endl; // db f1,v1
            int a = getind(v1), b = getind(v1);
            res.eb(a, b);
            f1 -= 2;
        }

        if (f1) pq.emplace(f1, v1);
    }

    cout << (ans) << '\n';
    for (auto [a, b] : res) 
        cout << (a) << ' ' << (b) << '\n';

    return 0;
}