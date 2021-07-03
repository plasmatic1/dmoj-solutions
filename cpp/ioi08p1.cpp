// ./ioi-08-p1-type-printer.yml
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
#ifdef AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
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

const int MN = 25000, MNODE = MN*20 + 10;
struct trie {
    bool word, last;
    int par;
    int ch[26];
    trie() {
        word = last = false;
        for (auto i = 0; i < 26; i++) ch[i] = 0;
        par = 0;
    }
} ns[MNODE];
int ctr = 1;

int N;

int rt = 1;
void ins(int rt, string &s, int cur) {
    auto &nn = ns[rt];
    if (cur == SZ(s)) {
        nn.word = true;
        return;
    }
    auto &n = nn.ch[s[cur] - 'a'];
    if (!n) { n = ++ctr; ns[n].par = rt; }
    ins(n, s, cur+1);
}
pii mark(int rt, int dep) {
    auto &n = ns[rt];
    pii res{-INF, 0};
    if (n.word) maxa(res, pii{dep, rt});
    for (auto i = 0; i < 26; i++)
        if (n.ch[i])
            maxa(res, mark(n.ch[i], dep+1));
    return res;
}

vector<char> ops;
void dfs(int rt) {
    auto &n = ns[rt];
    if (n.word) ops.pb('P');
    for (auto i = 0; i < 26; i++) {
        if (n.ch[i] && !ns[n.ch[i]].last) {
            ops.pb('a'+i);
            dfs(n.ch[i]);
            ops.pb('-');
        }
    }
    for (auto i = 0; i < 26; i++) {
        if (n.ch[i] && ns[n.ch[i]].last) {
            ops.pb('a'+i);
            dfs(n.ch[i]);
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (auto i = 0; i < N; i++) {
        string s; cin >> s;
        ins(rt, s, 0);
    }
    int end = mark(rt, 0).second;
    while (end) {
        ns[end].last = true;
        end = ns[end].par;
    }
    dfs(rt);

    cout << (SZ(ops)) << '\n';
    for (auto c : ops) cout << c << '\n';

    return 0;
}