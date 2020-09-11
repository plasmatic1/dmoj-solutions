#pragma GCC optimize "Ofast"
#pragma GCC optimize "unroll-loops"
#pragma GCC target "sse,sse2,sse3,sse4,abm,avx,mmx,popcnt"
// ./maximum-independent-subset.yml
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

const int BIG = 3e7;

template <typename T> struct Ranks {
    T ranks[BIG];
    int sz = 0;
    void init() {
        // sort(ranks.begin(), ranks.end());
        sz = unique(ranks, ranks + sz) - ranks;
    }
    void add(T v) { ranks[sz++] = v; }
    int size() { return sz; }
};

struct Seg {
    ll l, r;
    bool operator<(const Seg &o) const {
        return l < o.l;
    }
    Seg even() {
        Seg res{l, r};
        while (res.l & 1) res.l++;
        while (res.r & 1) res.r--;
        res.l /= 2; res.r /= 2;
        return res;
    }
    Seg odd() {
        Seg res{l, r};
        while (!(res.l & 1)) res.l++;
        while (!(res.r & 1)) res.r--;
        res.l = (res.l + 1) / 2; res.r = (res.r + 1) / 2;
        return res;
    }
    bool empty() { return l > r; }
};
istream& operator>>(istream &in, Seg &o) {
    in >> o.l >> o.r;
    return in;
}
ostream& operator<<(ostream& out, const Seg o) {
    out << "(l=" << o.l << ", r=" << o.r << ")";
    return out;
}

const int MN = 1e5 + 1, LG = 60;
int N;
Seg tmp[MN];
vector<Seg> segs[LG];
Ranks<ll> r;
ll psum[BIG];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N);
    for (auto i = 0; i < N; i++)
        cin >> (tmp[i]);
    sort(tmp, tmp + N);
    for (auto i = 0; i < LG; i++) {
        int csz = SZ(r);
        for (auto j = 0; j < N; j++) {
            Seg &s = tmp[j];
            if (s.empty()) continue;
            Seg os = s.odd(); os.r++;
            segs[i].pb(os);
            r.add(os.l); r.add(os.r);
            s = s.even();
            // cout<<"i="<<(i)<<", "; cout<<"j="<<(j)<<", "; cout<<"s="<<(s)<<", "; cout<<"os="<<(os)<<", "; cout << endl; // db i,j,s,os
        }
        // if (i<5) {
        //     cout<<"csz="<<(csz)<<", "; cout << "r.ranks=["; for (auto x:r.ranks)cout<<x<<", "; cout<<"], "; cout << endl; // db csz,I:r.ranks
        // }
        inplace_merge(r.ranks, r.ranks + csz, r.ranks + SZ(r));
    }
    // sort(all(r.ranks));
    r.init();

    int psz = SZ(r);
    for (auto i = 0; i < LG; i++) {
        int ptr = 0;
        for (auto &s : segs[i]) {
            ll bit = 1LL << i;
            while (r.ranks[ptr] < s.l) ptr++;
            psum[ptr] ^= bit;
            while (r.ranks[ptr] < s.r) ptr++;
            psum[ptr] ^= bit;
        }
    }
    for (auto i = 1; i < psz; i++)
        psum[i] ^= psum[i - 1];

    int ptr=0,qsz=0,dq[LG];

    ll ans = 0;
    for (auto i = 0; i < psz - 1; i++) {
        ll sz = r.ranks[i + 1] - r.ranks[i], pv = psum[i];
        // cout<<"i="<<(i)<<", "; cout<<"r.ranks[i]="<<(r.ranks[i])<<", "; cout<<"r.ranks[i+1]="<<(r.ranks[i+1])<<", ";  // db i,r.ranks[i],r.ranks[i+1],pv
        // cout<<"pv="<<(bitset<3>(pv))<<", "; cout << endl; // db b:3:pv
        
        // deque<int> dq;
        for (auto j = 0; j < LG; j++)
            if ((pv >> j) & 1)
                dq[qsz++] = j;
        int canUse = 0;
        while (ptr < qsz) {
            int tp = dq[ptr++];
            canUse++;
            if (ptr < qsz && dq[ptr] == tp + 1)
                ptr++;
        }
        qsz = ptr = 0;

        ans += sz * canUse;
    }
    
    cout << (ans) << '\n';

    return 0;
}