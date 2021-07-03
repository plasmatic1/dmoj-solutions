// ./dmopc-20-contest-7-p2-alice-and-tiles.yml
// I'm damaged and hurt
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
// template <typename T> using opt_ref = optional<reference_wrapper<T>>; // for some templates
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

using T = tuple<int, int, int, int>;
const int MN = 2e5 + 1, ADJ[8][2] = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};
int N;
vector<pii> sto, ans, pts;
vector<T> es;

const int ADJ4[4][2] = {{-2, 0}, {0, 2}, {2, 0}, {0, -2}},
      ADJ8[8][2] = {{-2, 0}, {-2, 2}, {0, 2}, {2, 2}, {2, 0}, {2, -2}, {0, -2}, {-2, -2}};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (auto i = 0; i < N; i++) {
        int x, y; cin >> x >> y;
        pts.eb(x, y);
    }
    sort(all(pts));
    auto contains = [&] (int a, int b) {
        auto ptr = lower_bound(all(pts), pii{a, b});
        return ptr != pts.end() && ptr->fs == a && ptr->sn == b;
    };

    for (auto i = 0; i < N; i++) {
        auto [x, y] = pts[i];

        int p = ((x/2) + (y/2)) % 2;
        vector<pii> cur;
        if (p) { // octopus
            cur.eb(x-1, y);
            cur.eb(x-1, y+1);
            cur.eb(x, y+2);
            cur.eb(x+1, y+2);
            cur.eb(x+2, y+1);
            cur.eb(x+2, y);
            cur.eb(x+1, y-1);
            cur.eb(x, y-1);

            for (auto i = 0; i < 8; i++) {
                if (!contains(x+ADJ8[i][0], y+ADJ8[i][1])) {
                    auto &[a, b] = cur[i];
                    auto &[c, d] = cur[(i+1)%8];
                    es.eb(a, b, c, d);
                }
            }
        }
        else { // squircle
            cur.eb(x, y);
            cur.eb(x, y+1);
            cur.eb(x+1, y+1);
            cur.eb(x+1, y);

            for (auto i = 0; i < 4; i++) {
                if (!contains(x+ADJ4[i][0], y+ADJ4[i][1])) {
                    auto &[a, b] = cur[i];
                    auto &[c, d] = cur[(i+1)%4];
                    es.eb(a, b, c, d);
                }
            }
        }

        sto.insert(sto.end(), all(cur));
    }

    // for (auto [a, b] : sto) {
    //     cout<<"a="<<(a)<<", "; cout<<"b="<<(b)<<", "; cout << endl; // db a,b
    // }
    sort(all(sto));
    for (auto i = 0; i < SZ(sto); ) {
        int j = i;
        while (j < SZ(sto) && sto[i] == sto[j]) j++;
        if (j-i < 3)
            ans.pb(sto[i]);
        i = j;
    }
    cout << (SZ(ans)) << '\n';

    sort(all(ans));
    auto getidx = [&] (int x, int y) {
        auto ptr = lower_bound(all(ans), pii{x, y});
        if (ptr == ans.end()) return -1;
        if (ptr->fs != x || ptr->sn != y) return -1;
        return (int)(ptr-ans.begin());
        // return ptr == ans.end() ? -1 : ptr-ans.begin();
    };

    vector<pii> esid;
    for (auto [x1, y1, x2, y2] : es) {
        int i1 = getidx(x1, y1), i2 = getidx(x2, y2);
        if (i1 != -1 && i2 != -1) {
            esid.eb(i1, i2);
            // cout<<"i1="<<(i1)<<", "; cout<<"x1="<<(x1)<<", "; cout<<"y1="<<(y1)<<", "; cout<<"i2="<<(i2)<<", "; cout<<"x2="<<(x2)<<", "; cout<<"y2="<<(y2)<<", "; cout << endl; // db i1,x1,y1,i2,x2,y2
        }
    }
    UNIQUE(esid);
    auto hasedge = [&] (int a, int b) {
        auto ptr = lower_bound(all(esid), pii{a, b});
        return ptr != esid.end() && ptr->fs == a && ptr->sn == b;
    };

    // int its=30;
    pii st = *min_element(all(ans)); int px = -1, py = -1;
    for (auto c = st; ; ) {
        auto &[x, y] = c;
        cout << (x) << ' ' << (y) << '\n';
        // cout.flush(); assert(its--);

        int i1 = getidx(x, y);
        if (c == st) {
            for (auto d : ADJ) {
                int xx = x+d[0], yy = y+d[1];
                if (getidx(xx, yy) != -1) {
                    px = x;
                    py = y;
                    x = xx;
                    y = yy;
                    break;
                }
            }
        }
        else {
            bool nofound = true;
            for (auto d : ADJ) {
                int xx = x+d[0], yy = y+d[1], i2 = getidx(xx, yy);
                // cout<<"xx="<<(xx)<<", "; cout<<"yy="<<(yy)<<", "; cout<<"i1="<<(i1)<<", "; cout<<"i2="<<(i2)<<", "; cout << endl; // db xx,yy,i1,i2
                if (i2 != -1 && (xx != px || yy != py) && hasedge(i1, i2)) {
                    nofound = false;
                    px = x;
                    py = y;
                    x = xx;
                    y = yy;
                    break;
                }
            }
            if (nofound) break;
        }
        // cout<<"[ch]: "; cout<<"x="<<(x)<<", "; cout<<"y="<<(y)<<", "; cout << endl; // db l:ch,x,y

        if (c == st) break;
    }

    return 0;
}