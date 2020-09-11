// coci-19-contest-3-3-drvca.yml
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
template <typename T, typename U> void maxa(T &a, U b) { a = max(a, b); }
template <typename T, typename U> void mina(T &a, U b) { a = min(a, b); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 1e5 + 1;
int N, 
    val[MN];

bool check(vector<int> &v) {
    if (SZ(v) <= 1) return true;
    int d = v[1] - v[0];
    for (auto i = 0; i < SZ(v) - 1; i++)
        if (v[i + 1] - v[i] != d) return false;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N);

    for (auto i = 0; i < N; i++)
        cin >> (val[i]);
    sort(val, val + N);

    if (N == 2) {
        cout << (1) << '\n';
        cout << (val[0]) << '\n';
        cout << (1) << '\n';
        cout << (val[1]) << '\n';
        return 0;
    }

    for (auto i = 0; i < 8; i++) {
        vector<int> vs[2], ids[2];        
        for (auto j = 0; j < 3; j++)
            ids[(i >> j) & 1].pb(j);
        vector<bool> done(N, false);

        if (SZ(ids[1]) > 1) swap(ids[0], ids[1]);

        for (auto k = 0; k < 2; k++) {
            if (SZ(ids[k]) > 1) {
                int d = val[ids[k][1]] - val[ids[k][0]], cur = val[ids[k][0]];
                for (auto l = 0; l < N; l++) {
                    if (val[l] == cur) {
                        cur += d;
                        done[l] = true;
                        vs[k].pb(val[l]);
                    }
                }
            }
            else {
                for (auto l = 0; l < N; l++)
                    if (!done[l])
                        vs[k].pb(val[l]);
                // cout<<"k="<<(k)<<", "; cout << "vs[k]=["; for (auto x:vs[k])cout<<x<<", "; cout<<"], "; cout << "vs[!k]=["; for (auto x:vs[!k])cout<<x<<", "; cout<<"], "; cout << endl; // db k,I:vs[k],I:vs[!k]
            }
        }

        for (auto k = 0; k < 2; k++) {
            if (vs[k].empty()) {
                vs[k].pb(vs[!k].back());
                vs[!k].pop_back();
            }
        }

        multiset<int> diff;
        set<int> v1;
        for (auto i = 0; i < SZ(vs[1]) - 1; i++) {
            diff.insert(vs[1][i + 1] - vs[1][i]);
            v1.insert(vs[1][i]);
        }
        v1.insert(vs[1].back());
        v1.insert(-INF);
        v1.insert(INF);

        while (SZ(vs[0]) > 1 && !diff.empty() && *diff.begin() != *(--diff.end())) {
            auto ptr = v1.lower_bound(vs[0].back()), nxt = ptr, pre = ptr;
            pre--;
            if (*pre != -INF && *nxt != INF) {
                diff.erase(diff.find(*nxt - *pre));
                diff.insert(vs[0].back() - *pre);
                diff.insert(*nxt - vs[0].back());
            }
            else{
                if (*pre != -INF) {
                    diff.insert(vs[0].back() - *pre);
                }
                if (*nxt != INF) {
                    diff.insert(*nxt - vs[0].back());
                }
            }
            
            v1.insert(vs[0].back());
            vs[1].pb(vs[0].back());
            vs[0].pop_back();
        }
        sort(all(vs[1]));

        if (check(vs[0]) && check(vs[1])) {
            for (auto j = 0; j < 2; j++) {
                cout << (SZ(vs[j])) << '\n';
                for (auto x : vs[j])
                    cout << x << ' ';
                cout << '\n';
            }
            return 0;
        }
    }

    cout << (-1) << '\n';

    return 0;
}