// ./p2-folding-clothes.yml
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

ostream& operator<<(ostream& out, const pii o) {
    out << "(fs=" << o.fs << ", sn=" << o.sn << ")";
    return out;
}

const int MN = 2001;
int N;
pii A[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (auto i = 0; i < N; i++) {
        cin >> A[i].fs;
        A[i].sn = i;
    }

    vector<pii> sortedVer(A, A+N), base(A, A+N), stk;
    sort(all(sortedVer));
    reverse(all(sortedVer));

    int skip = 0;
    vector<int> ops;
    for (auto cur : sortedVer) {
        int op = SZ(base)-skip;
        ops.pb(SZ(base)-skip);
        stk.insert(stk.begin(), base.begin(), base.end()-skip);
        base.erase(base.begin(), base.end()-skip);

        // cout<<"op="<<(op)<<", "; cout << endl; // db op
        // cout << "base=["; for (auto __x:base)cout<<__x<<", "; cout<<"], "; cout << "stk=["; for (auto __x:stk)cout<<__x<<", "; cout<<"], "; cout << endl; // db I:base,I:stk

        int idx = -1;
        for (auto i = 0; i < SZ(stk); i++) {
            if (stk[i] == cur) {
                idx = i;
                break;
            }
        }

        op = -(idx+1);
        ops.pb(-(idx+1));
        base.insert(base.begin(), stk.begin(), stk.begin()+idx+1);
        stk.erase(stk.begin(), stk.begin()+idx+1);

        // cout<<"op="<<(op)<<", "; cout << endl; // db op
        // cout << "base=["; for (auto __x:base)cout<<__x<<", "; cout<<"], "; cout << "stk=["; for (auto __x:stk)cout<<__x<<", "; cout<<"], "; cout << endl; // db I:base,I:stk

        skip++;
    }

    vector<int> oops;
    for (auto k : ops) if (k) oops.pb(k);
    cout << (SZ(oops)) << '\n';
    for (auto k : oops)
        cout << (k) << '\n';

    return 0;
}