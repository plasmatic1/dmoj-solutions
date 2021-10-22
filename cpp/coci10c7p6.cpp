// ./coci-10-contest-7-6-upit.yml
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

struct Block {
    vector<ll> v;
    ll sum;
    ll lset, linc, linca;

    Block() : sum(0), lset(-1), linc(-1), linca(-1) {}
};

#ifdef LOCAL
const int MN = 1e5+1, BS = 2;
#else
const int MN = 1e5+1, BS = 300;
#endif
int N, Q;
vector<Block*> bs;

void resolve(Block* b) {
    if (b->lset != -1)
        for (auto &x : b->v) x = b->lset;
    if (b->linc != -1)
        for (auto &x : b->v) x += b->linc;
    if (b->linca != -1) {
        ll cur = -b->linca;
        for (auto &x : b->v) x += (cur += b->linca);
    }
    b->lset = b->linc = b->linca = -1;
}

// indexed like vector
void insert(Block *b, int idx, ll k) {
    resolve(b);
    b->v.insert(b->v.begin()+idx, k);
    b->sum += k;
}

void rebuild(bool force) {
    bool bad = force;
    for (auto b : bs)
        bad |= SZ(b->v) > 2*BS;
    if (!bad) return;

    vector<ll> tot;
    for (auto b : bs) {
        resolve(b);
        for (auto &x : b->v)
            tot.pb(x);
        delete b;
    }
    bs.clear();

    for (auto &x : tot) {
        if (bs.empty() || SZ(bs.back()->v) >= BS) {
            bs.pb(new Block);
        }
        insert(bs.back(), SZ(bs.back()->v), x);
    }
}

void loop(int l, int r, function<void(Block*, int, int, bool)> f) {
    int cur = 0;
    for (auto b : bs) {
        int nxt = cur+SZ(b->v);
        if (!(l > nxt-1) && !(r < cur)) {
            f(b, cur, nxt-1, l <= cur && nxt-1 <= r);
        }

        cur = nxt;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> N >> Q;
    
    bs.pb(new Block);
    for (auto i = 0; i < N; i++) {
        int x; cin >> x;
        insert(bs.back(), i, x);
    }
    rebuild(true);

    while (Q--) {
        int T; cin >> T;

        if (T == 1) {
            int L, R, x; cin >> L >> R >> x;
            L--; R--;

            loop(L, R, [&] (auto b, int l, int r, bool fullContain) {
                if (fullContain) {
                    b->linc = b->linca = -1;
                    b->lset = x;
                    b->sum = ll(x)*(r-l+1);
                }
                else {
                    resolve(b);

                    for (auto i = l; i <= r; i++) {
                        if (L <= i && i <= R) {
                            b->sum += x - b->v[i-l];
                            b->v[i-l] = x;
                        }
                    }
                }
            });
        }
        else if (T == 2) {
            int L, R, x; cin >> L >> R >> x;
            L--; R--;

            loop(L, R, [&] (auto b, int l, int r, bool fullContain) {
                int sz = r-l+1, st = l-L+1;
                if (fullContain) {
                    if (b->linc == -1) b->linc = 0;
                    if (b->linca == -1) b->linca = 0;
                    b->linc += ll(x)*(st);
                    b->linca += x;
                    b->sum += ll(x)*(sz)*(sz-1)/2 + ll(x)*st*sz;
                }
                else {
                    resolve(b);

                    ll cur = st*x;
                    for (auto i = l; i <= r; i++) {
                        if (L <= i && i <= R) {
                            b->sum += cur;
                            b->v[i-l] += cur;
                        }
                        cur += x;
                    }
                }
            });
        }
        else if (T == 3) {
            int i, x; cin >> i >> x;
            i--;

            for (auto b : bs) {
                int sz = SZ(b->v);
                if (i <= sz) {
                    insert(b, i, x);
                    break;
                }
                i -= sz;
            }
        }
        else {
            int L, R; cin >> L >> R;
            L--; R--;

            ll ans = 0;
            loop(L, R, [&] (auto b, int l, int r, bool fullContain) {
                if (fullContain) ans += b->sum;
                else {
                    resolve(b);

                    for (auto i = l; i <= r; i++) {
                        if (L <= i && i <= R) {
                            ans += b->v[i-l];
                        }
                    }
                }
            });

            cout << (ans) << '\n';
        }

        rebuild(false);
    }

    return 0;
}