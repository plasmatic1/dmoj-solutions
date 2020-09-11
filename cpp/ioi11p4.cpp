// ./ioi-11-p4-crocodiles-underground-city.yml
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

const int MN = 1e5 + 1;
using pli = pair<ll, int>;

struct St {
    int v; ll w;
    bool operator<(const St &o) const {
        return w > o.w;
    }
};

int travel_plan(int N, int M, int R[][2], int W[], int K, int E[]) {
    vector<vector<pii>> g(N);
    for (auto i = 0; i < M; i++) {
        int a = R[i][0], b = R[i][1], c = W[i];
        g[a].eb(b, c);
        g[b].eb(a, c);
    }

    priority_queue<St> pq;
    vector<vector<ll>> dis(N, vector<ll>(2, LLINF));
    for (auto i = 0; i < K; i++) {
        dis[E[i]][0] = dis[E[i]][1] = 0;
        pq.push({E[i], 0});
    }
    vector<bool> vis(N);
    while (!pq.empty()) {
        auto c = pq.top(); pq.pop();
        if (vis[c.v] || c.w > dis[c.v][1]) continue;
        vis[c.v] = true;
        // cout<<"c.v="<<(c.v)<<", "; cout<<"c.w="<<(c.w)<<", "; cout<<"dis[c.v][0]="<<(dis[c.v][0])<<", "; cout<<"dis[c.v][1]="<<(dis[c.v][1])<<", "; cout << endl; // db c.v,c.w,dis[c.v][0],dis[c.v][1]
        for (auto to : g[c.v]) {
            ll alt = c.w + to.sn; bool please_calm_down_sir_or_madam = false;
            // cout<<"alt="<<(alt)<<", "; cout<<"to.fs="<<(to.fs)<<", "; cout<<"to.sn="<<(to.sn)<<", "; cout<<"dis[to.fs]=["; for(int __i=0; __i<(2); __i++)cout<<dis[to.fs][__i]<<", "; cout<<"], ";cout << endl; // db alt,to.fs,to.sn,A:2:dis[to.fs]
            if (alt <= dis[to.fs][0]) {
                dis[to.fs][1] = dis[to.fs][0];
                dis[to.fs][0] = alt;
                please_calm_down_sir_or_madam = true;
            }
            else if (alt < dis[to.fs][1]) {
                dis[to.fs][1] = alt;
                please_calm_down_sir_or_madam = true;
            }

            if (please_calm_down_sir_or_madam)
                pq.push({to.fs, dis[to.fs][1]});
        }
    }

    return dis[0][1];
}

#ifdef LOCAL
int R1[4][2] = {{0, 1}, {0, 2}, {3, 2}, {2, 4}}, W1[4] = {2, 3, 1, 4}, E1[3] = {1, 3, 4};
int R2[7][2] = {{0, 2}, {0, 3}, {3, 2}, {2, 1}, {0, 1}, {0, 4}, {3, 4}}, W2[7] = {4, 3, 2, 10, 100, 7, 9}, E2[2] = {1, 3};

int main() {
    cout<<"travel_plan(5, 4, R1, W1, 3, E1)="<<(travel_plan(5, 4, R1, W1, 3, E1))<<", "; cout << endl; // db travel_plan(5, 4, R1, W1, 3, E1)
    cout<<"travel_plan(5, 7, R2, W2, 2, E2)="<<(travel_plan(5, 7, R2, W2, 2, E2))<<", "; cout << endl; // db travel_plan(5, 7, R2, W2, 2, E2)

    return 0;
}
#endif