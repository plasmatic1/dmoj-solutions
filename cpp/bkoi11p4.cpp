// ./balkan-oi-11-p4-compare.yml
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

#ifdef LOCAL
// const int A = 2023, B = 1230, expect = -1;
const int A = 2023, B = 3, expect = -1;
bitset<10241> mem;
int opsSet = 0, opsGet = 0;
void bit_set(int addr) { mem[addr] = true; opsSet++; }
int bit_get(int addr) { opsGet++; return mem[addr]; }
#else
void bit_set(int addr);
int bit_get(int addr);
#endif

// bruh
void sb(int a) { bit_set(a + 1); }
int gb(int a) { return bit_get(a + 1); }

// utils
int topbits(int v, int bc) { return v >> (12 - bc); }
int bitno(int v, int idx) { return (v >> (11 - idx)) & 1; }

int shf[6];

void remember(int val) {
    int cshf = 0, cp = 1;
    for (auto i = 2, ctr = 0; i <= 12; i += 2, ctr++) {
        sb(cshf + topbits(val, i));
        shf[ctr] = cshf;
        cshf += (cp *= 4);
    }
}

int compare(int val) {
    assert(shf[1] > 0);

    // binary search for LCP
    int l = -1, r = 6;
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        assert(mid != 6);
        if (!gb(shf[mid] + topbits(val, mid * 2 + 2)))
            r = mid;
        else
            l = mid;
    }

    if (r == 6) return 0; // same number
    // r -> first block number that does not match (0..5)

    // case bash for comparison
    int atVal = (bitno(val, r * 2) << 1) | bitno(val, r * 2 + 1);
    if (atVal == 3) return 1;
    else if (atVal == 0) return -1;
    else if (atVal == 1) {
        if (gb(shf[r] + (topbits(val, r * 2) << 2))) return 1; // val at block is 0
        else return -1; // val at block is {2, 3}
    }
    else {
        if (gb(shf[r] + ((topbits(val, r * 2) << 2) | 3))) return -1; // val at block is 3
        else return 1; // val at block is {0, 1}
    }
}

#ifdef LOCAL
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout<<"A="<<(A)<<", "; cout<<"B="<<(B)<<", "; cout << endl; // db A,B
    cout<<"[remember]: "; cout << endl; // db l:remember
    remember(A);
    cout<<"[compare]: "; cout << endl; // db l:compare
    int out = compare(B);

    cout<<"[answer]: "; cout<<"expect="<<(expect)<<", "; cout<<"out="<<(out)<<", "; cout << endl; // db l:answer,expect,out
    cout<<"opsSet="<<(opsSet)<<", "; cout<<"opsGet="<<(opsGet)<<", "; cout << endl; // db opsSet,opsGet

    return 0;
}
#endif