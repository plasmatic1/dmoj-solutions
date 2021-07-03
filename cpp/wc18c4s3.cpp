// ./wc-18-contest-4-s3-dance-royale.yml
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

const int MN = 3e5 + 1;
int N, M,
    D[MN], X[MN], cnt[MN];
vector<int> rg[MN], zloc;

ll C2(ll k) { return k*(k-1)/2; }

int dis[MN];
vector<int> player, see;
void dfs(int c) {
    see.pb(c);
    for (auto i = 0; i < cnt[c]; i++)
        player.pb(dis[c]);
    for (auto to : rg[c]) {
        if (dis[to] == -1) {
            dis[to] = dis[c]+1;
            dfs(to);
        }
    }
}

ll ans = 0;
void addCnt(vector<int> &v) {
    sort(all(v));
    for (int i = 0; i < SZ(v); ) {
        int j = i;
        while (j < SZ(v) && v[i] == v[j]) j++;
        ans += C2(j-i);
        i = j;
    }
}

int tmpdis[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    for (auto i = 1; i <= N; i++) {
        cin >> D[i];
        rg[D[i]].pb(i);
    }
    for (auto i = 1; i <= M; i++) {
        cin >> X[i];
        cnt[X[i]]++;
    }

    memset(dis, -1, sizeof dis);
    memset(tmpdis, -1, sizeof tmpdis);
    zloc = rg[0];

    for (auto x : zloc) {
        assert(dis[x] == -1);
        see.clear();
        player.clear();
        dis[x] = 0;
        dfs(x);
        addCnt(player);
    }
    for (auto i = 1; i <= N; i++) {
        if (dis[i] == -1) {
            int pre = -1, cycLen = -INF, st = -1;
            for (auto c = i; ; c = D[c]) {
                if (tmpdis[c] != -1) {
                    cycLen = pre+1-tmpdis[c];
                    st = c;
                    break;
                }
                tmpdis[c] = pre+1;
                pre++;
            }

            see.clear();
            player.clear();
            dis[st] = 0;
            dfs(st);


            for (auto &d : player) d %= cycLen;
            addCnt(player);
        }
    }

    cout << (ans) << '\n';

    return 0;
}