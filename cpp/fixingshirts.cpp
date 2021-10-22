// ./fixing-shirts.yml
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
template <typename K, typename V, class comp = less<K>> using treeMP = tree<K, V, comp, rb_tree_tag, tree_order_statistics_node_update>;
// HashSet
#include <ext/pb_ds/assoc_container.hpp>
template <typename T, class Hash> using hashset = gp_hash_table<T, null_type, Hash>;
template <typename K, typename V, class Hash> using hashMP = gp_hash_table<K, V, Hash>;
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

template <typename K, typename V> using MP = hashMP<K, V, chash>;

const int MN = 1e6+1;
int N, M,
    s1[MN], c1[MN], s2[MN], c2[MN];
bool done1[MN], done2[MN];

bool extract(vector<int> &v) {
    while (!v.empty() && done2[v.back()])
        v.pop_back();
    if (!v.empty()) {
        done2[v.back()] = true;
        v.pop_back();
        return true;
    }
    return false;
}

ll comb(int a, int b) {
    return ll(a)<<32LL | b;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    MP<ll, vector<int>> ps;
    int takeOut = 0;
    for (auto i = 0; i < N; i++) {
        char s; int c; cin >> s >> c;
        s1[i] = s == 'L';
        c1[i] = c;
        ps[comb(s1[i], c1[i])].pb(i);
    }
    for (auto i = 0; i < M; i++) {
        char s; int c; cin >> s >> c;
        s2[i] = s == 'L';
        c2[i] = c;

        ll p = comb(s2[i], c2[i]);
        if (ps.find(p) != ps.end()) {
            auto &v = ps[p];
            if (!v.empty()) {
                done1[v.back()] = true;
                v.pop_back();
                done2[i] = true;
                takeOut++;
            }
        }
    }

    int smallP = 0, smallS = 0;
    for (auto i = 0; i < N; i++) smallP += !done1[i] && s1[i] == 0;
    for (auto i = 0; i < M; i++) smallS += !done2[i] && s2[i] == 0;

    // assume we can assign all small shirts
    if (smallP > smallS) {
        for (auto i = 0; i < N; i++) s1[i] ^= 1;
        for (auto i = 0; i < M; i++) s2[i] ^= 1;
        smallP = N-takeOut-smallP;
        smallS = M-takeOut-smallS;
        // cout<<"[flip]: "; cout << endl; // db l:flip
    }

    int canTake = smallS - smallP, ans = smallP;
    MP<int, int> smalls;
    for (auto i = 0; i < M; i++)
        if (!done2[i] && s2[i] == 0)
            smalls[c2[i]]++;

    int largeS = M-takeOut-smallS, largeP = N-takeOut-smallP;
    if (largeS >= largeP) {
        ans = N-takeOut;
        cout << (ans) << '\n';
        return 0;
    }
    assert(largeS < largeP);
    ans += largeS;

    // cout<<"smallS="<<(smallS)<<", "; cout<<"smallP="<<(smallP)<<", "; cout<<"largeS="<<(largeS)<<", "; cout<<"largeP="<<(largeP)<<", "; cout << endl; // db smallS,smallP,largeS,largeP
    // cout<<"ans="<<(ans)<<", "; cout << endl; // db ans

    // cout<<"canTake="<<(canTake)<<", "; cout << endl; // db canTake

    int canMatch = 0;
    for (auto i = 0; i < N; i++) {
        if (!done1[i] && s1[i] == 1) { // is large
            if (smalls.find(c1[i]) != smalls.end() && canTake > 0) {
                if (--smalls[c1[i]] == 0) smalls.erase(c1[i]);
                canMatch++;
                canTake--;
            }
        }
    }

    // cout<<"canMatch="<<(canMatch)<<", "; cout<<"largeP-largeS="<<(largeP-largeS)<<", "; cout << endl; // db canMatch,largeP-largeS
    mina(canMatch, largeP-largeS);
    ans += canMatch;
    ans += 2 * (largeP-largeS - canMatch);

    cout << (ans) << '\n';

    return 0;
}