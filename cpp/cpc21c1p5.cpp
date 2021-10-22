// ./_sol.yml
#pragma once
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
template <typename T> using opt_ref = optional<reference_wrapper<T>>; // for some templates
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
const int MN = 2001, MV = 1e9;
using T = tuple<int, int, int, int>;
int N;

bool between(int l, int a, int b, int r) { return l <= a && b <= r; }

#ifdef LOCAL
const int QLIM = 1e5;
int ax1[MN], ax2[MN], ay1[MN], ay2[MN];
int qc=0;
int query(int x1, int x2, int y1, int y2) {
    qc++;
    assert(qc <= QLIM);
    int res = 0;
    for (auto i = 0; i < N; i++)
        res += between(x1, ax1[i], ax2[i], x2) && between(y1, ay1[i], ay2[i], y2);
    return res;
}
#else
int query(int x1, int x2, int y1, int y2) {
    if (x1 > x2 || y1 > y2) return 0;
    cout << "? " << x1 << ' ' << x2 << ' ' << y1 << ' ' << y2 << '\n'; cout.flush();
    int res; cin >> res; if (res == -1) exit(0);
    return res;
}
#endif

vector<pair<pii, int>> xr;
vector<T> rs;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    assert(1 <= N && N <= 500);
#ifdef LOCAL
    cout<<"[readin]: "; cout << endl; // db l:readin
    for (auto i = 0; i < N; i++)
        cin >> ax1[i] >> ax2[i] >> ay1[i] >> ay2[i];
#endif
    
    int pre = 0;
    while (pre < N) {
        int st;
        {
            int l = 1, r = 1e9 + 1;
            while (l+1 < r) {
                int mid = (l+r) / 2;
                if (query(mid, 1e9, 1, 1e9) > pre) l = mid;
                else r = mid;
            }
            st = l;
        }
        int newCnt = query(st, 1e9, 1, 1e9), need = newCnt-pre;

        int epre = 0;
        while (epre < need) {
            int l = 0, r = 1e9+1, lstCnt = -1;
            while (l+1 < r) {
                int mid = (l+r) / 2, cnt = query(st, mid, 1, 1e9);
                for (auto [p, c] : xr) {
                    auto [a, b] = p;
                    if (st < a && b <= mid) cnt -= c;
                }
                if (cnt <= epre) l = mid;
                else {
                    lstCnt = cnt;
                    r = mid;
                }
            }

            xr.emplace_back(pii{st, r}, lstCnt-epre);
            epre = lstCnt;
        }

        pre = newCnt;
    }
    sort(all(xr), [&] (const pair<pii, int> a, const pair<pii, int> b) {
        return a.fs.sn-a.fs.fs < b.fs.sn-b.fs.fs;
    });
    for (auto [_p, tot] : xr) {
        auto [xLeft, xRight] = _p;

        int pre = 0;
        while (pre < tot) {
            int st, newCnt = -1;
            {
                int l = 0, r = 1e9 + 1;
                while (l+1 < r) {
                    int mid = (l+r) / 2, cnt = query(xLeft, xRight, mid, 1e9);
                    for (auto [a, b, c, d] : rs) {
                        if ((a != xLeft || b != xRight) && between(xLeft, a, b, xRight))
                            cnt -= between(mid, c, d, 1e9);
                    }
                    if (cnt > pre) { 
                        newCnt = cnt;
                        l = mid;
                    }
                    else r = mid;
                }
                st = l;
            }
            int need = newCnt-pre;

            int epre = 0;
            while (epre < need) {
                int l = 0, r = 1e9+1, lstCnt = -1;
                while (l+1 < r) {
                    int mid = (l+r) / 2, cnt = query(xLeft, xRight, st, mid);
                    for (auto [a, b, c, d] : rs) {
                        if ((a != xLeft || b != xRight) && between(xLeft, a, b, xRight))
                            cnt -= between(st, c, d, mid);
                        if (a == xLeft && b == xRight) {
                            cnt -= between(st, c, d, mid) && c != st;
                        }
                    }
                    if (cnt <= epre) l = mid;
                    else {
                        lstCnt = cnt;
                        r = mid;
                    }
                }

                for (auto i = 0; i < lstCnt-epre; i++)
                    rs.emplace_back(xLeft, xRight, st, r);
                epre = lstCnt;
            }

            pre = newCnt;
        }
    }

    cout << "!\n";
    for (auto [a, b, c, d] : rs) {
        cout << (a) << ' ' << (b) << ' ' << (c) << ' ' << (d) << '\n';
    }
    cout << '\n'; cout.flush();

#ifdef LOCAL
    cout<<"[queries used]: "; cout<<"qc="<<(qc)<<", "; cout << endl; // db l:queries used,qc
#endif

    return 0;
}