// ./special-relativity.yml
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
// More utidriies
int SZ(string &v) { return v.length(); }
template <typename C> int SZ(C &v) { return v.size(); }
template <typename C> void UNIQUE(vector<C> &v) { sort(v.begin(), v.end()); v.resize(unique(v.begin(), v.end()) - v.begin()); }
template <typename T, typename U> void maxa(T &a, U b) { a = max(a, b); }
template <typename T, typename U> void mina(T &a, U b) { a = min(a, b); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

using pt = complex<ld>;
#define x real
#define y imag

istream& operator>>(istream &in, pt &o) {
    ld cx, cy; in >> cx >> cy;
    o = {cx, cy};
    return in;
}

const int MN = 4001;
int N, M;
ld C;
pt lit[MN], dri[MN], drid[MN];

ld ftime[MN][MN];

ld dist(const pt &a, const pt &b) {
    return sqrt(norm(b-a));
}

/*
 * pts:
 *
 * light (lx, ly)
 * dinit (x, y)
 * ddest (dx, dy)
 *
 * RATIO
 *
 * len(dinit,ddest)/len(light, ddest) = RATIO
 *
 * (SPEED*TIME) / len(light, ddest) = RATIO
 * SPEED*TIME/RATIO = len(light, ddest)
 * (SPEED*TIME/RATIO)^2 = (len(light, ddest))^2
 *
 * (SPEED*t/RATIO)^2 = speed^2/ratio^2
 *
 * (lx - (x+t*dx))^2 + (ly - (y+t*dy)) ^2
 *
 * ( (lx-x) - dx*t )^2 = (lx-x)^2 + dx^2 * t^2 - 2*(lx-x)*dx*t
 *
 * (lx-x)^2 + dx^2 * t^2 -2*(lx-x)*dx*t
 * (ly-y)^2 + dy^2 * t^2 -2*(ly-y)*dx*t
 * - (SPEED/RATIO)^2 * t^2
 */

pair<ld, ld> solveQuad(ld a, ld b, ld c) {
    ld disc = sqrtl(b*b - 4*a*c);
    return {(-b - disc) / (2*a), (-b + disc) / (2*a)};
}

ld sq(ld x) { return x*x; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> C;
    for (auto i = 0; i < N; i++)
        cin >> lit[i];
    for (auto i = 0; i < M; i++)
        cin >> dri[i] >> drid[i];

    for (auto i = 0; i < M; i++) { // driver
        for (auto j = 0; j < N; j++) { // light
            ld lx = lit[j].x(), ly = lit[j].y(), x = dri[i].x(), y = dri[i].y(), dx = drid[i].x(), dy = drid[i].y();

            ld a = sq(dx) + sq(dy) - sq(C);
            ld b = -2*(lx-x)*dx -2*(ly-y)*dy;
            ld c = sq(lx-x) + sq(ly-y);

            auto [x1, x2] = solveQuad(a, b, c);
            ftime[i][j] = max(x1, x2);
        }
    }

    ld ans = 0;
    for (auto i = 0; i < N; i++) {
        vector<ld> times;
        for (auto j = 0; j < M; j++)
            times.pb(ftime[j][i]);
        sort(all(times));

        ld acc = 0;
        for (auto j = 0; j < M; j++) {
            ans += j*times[j] - acc;
            acc += times[j];
        }
    }

    cout << fixed << setprecision(15) << (ans) << '\n';

    return 0;
}