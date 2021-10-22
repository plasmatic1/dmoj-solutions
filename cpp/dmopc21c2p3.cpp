// ./p3-divisions.yml
#define DEBUG 0
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

mt19937 mt(26022021);
uniform_int_distribution<int> dis(0, 1);
int randbit() { return dis(mt); }

const int MN = 1001;
int N;

#ifdef LOCAL
ll A[MN], ptr = 0, guessc = 0;

int game(ll x, ll y) {
    int res = 0;
    while (x != y) {
        if (y > x) swap(x, y);
        x >>= 1;
        res++;
    }
    return res;
}

int guess(ll k) {
    guessc++;
    if (ptr >= N) {
        cout << ("already done???") << '\n';
        cout.flush();
        exit(0);
    }
    int times = game(A[ptr], k);
    if (times == 0) {
        ptr++;
        cout << ("NEXT TO") << ' ' << (ptr) << '\n';
    }
    return times;
}

#else

int guess(ll k) {
    cout << k << '\n'; cout.flush();
    int ret; cin >> ret; assert(ret != -1);
    return ret;
}

#endif

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
#ifdef LOCAL
    for (auto i = 0; i < N; i++) {
        cin >> A[i];
        if (DEBUG) { cout<<"i="<<(i)<<", "; cout<<"A[i]="<<(bitset<5>(A[i]))<<", "; cout << endl; } //__RAW_DEBUG_LINE__:db i,b:5:A[i]
    }
#endif

    for (auto _ = 0; _ < N; _++) {
        ll bitc = guess(0);
        if (bitc <= 0) continue; // x_i = 0

        if (DEBUG) { cout<<"bitc="<<(bitc)<<", "; cout << endl; } //__RAW_DEBUG_LINE__:db bitc

        bool done = false;
        ll curb = (1LL << bitc)-1;
        int cor = 1; //, control = 1;

        for (auto i = 0; i < bitc-1; i++) {
            if (randbit())
                curb ^= 1LL << i;
        }
        if (DEBUG) { cout<<"curb="<<(bitset<62>(curb))<<", "; cout << endl; } //__RAW_DEBUG_LINE__:db b:62:curb

        // int its = 20;
        while (cor < bitc) {
            int g = guess(curb), idx = g/2-1;
            if (g == 0) {
                done = true;
                break;
            }

            curb ^= 1LL << idx;
            cor = bitc - idx;

            // if (DEBUG) { cout<<"g="<<(g)<<", "; cout<<"curb="<<(bitset<5>(curb))<<", "; cout<<"cor="<<(cor)<<", "; cout<<"control="<<(control)<<", "; cout << endl; } //__RAW_DEBUG_LINE__:db g,b:5:curb,cor,control
            //
            // int c0 = 0, c1 = 0;
            // for (auto i = 0; i < cor; i++) {
            //     if (curb & (1LL << (bitc-i-1)))
            //         c1++;
            //     else
            //         c0++;
            // }
            // if (control == 1 && c0 > c1) control = 0;
            // else control = 1;
            //
            // for (auto i = 0; i < bitc-cor; i++) {
            //     if (((curb >> i) & 1) != control)
            //         curb ^= 1LL << i;
            // }
            //
            // if (DEBUG) { cout<<"curb="<<(bitset<5>(curb))<<", "; cout << endl; } //__RAW_DEBUG_LINE__:db b:5:curb
            // assert(its--);
        }

        if (done) continue;
        assert(guess(curb) == 0);
    }

#ifdef LOCAL
    cout << ("DONE") << '\n';
    cout << ("GUESSC") << ' ' << (guessc) << '\n';
#endif

    return 0;
}