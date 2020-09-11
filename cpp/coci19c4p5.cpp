// ./coci-19-contest-4-5-nivelle.yml
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

using SA = pair<pll, pii>;
ostream& operator<<(ostream& out, const pii o) {
    out << "(fs=" << o.fs << ", sn=" << o.sn << ")";
    return out;
}
ostream& operator<<(ostream& out, const SA o) {
    out << "(fs=" << o.fs << ", sn=" << o.sn << ")";
    return out;
}

bool cmp(const SA &a, const SA &b) {
    return a.fs.fs * b.fs.sn < b.fs.fs * a.fs.sn;
}

const int MN = 1e5 + 1;
int N;
string s;

int cnt[26];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (s);

    SA ans{{INF, 1}, {-1, -1}};
    for (auto i = 1; i <= 26; i++) {
        int cntDistinct = 0, r = 0;
        for (auto l = 0; l < N; l++) {
            while (r < N && cntDistinct <= i) {
                int c = s[r] - 'a';
                cnt[c]++;
                if (cnt[c] == 1) cntDistinct++;
                r++;
            }
            if (cntDistinct > i) {
                r--;
                int c = s[r] - 'a';
                cntDistinct--;
                cnt[c]--;
            }

            ans = min(ans, mpr(mpr((ll)i, (ll)r - l), mpr(l, r - 1)), cmp);

            // if (i<=5){
            //     cout<<"i="<<(i)<<", "; cout<<"l="<<(l)<<", "; cout<<"r="<<(r)<<", "; cout<<"ans="<<(ans)<<", "; cout << endl; // db i,l,r,ans
            // }

            int c = s[l] - 'a';
            cnt[c]--;
            if (cnt[c] == 0) cntDistinct--;
        }
    }

    cout << (ans.sn.fs+1) << ' ' << (ans.sn.sn+1) << '\n';

    return 0;
}