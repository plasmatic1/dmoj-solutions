// ./p6-cozy-cottages.yml
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

const int MN = 1e6 + 1;
int N, K,
    A[MN];

int cnt[MN], endLocOf[MN],
    finalPos[MN]; // idx i stores A[(i-K)%N], so 1s don't move and >1s move left each step
bool done[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K;

    vector<int> nolocs, zlocs;
    for (auto i = 0; i < N; i++) {
        cin >> A[i];
        if (A[i] > 1)
            nolocs.pb(i);
        if (A[i] == 0)
            zlocs.pb(i);
    }

    // we compute number of times each "A[i] > 1" fills in a 0
    deque<int> dq;
    auto f = [&] () {
        for (auto i = N-1; i >= 0; i--) {
            if (A[i] == 0) {
                while (!dq.empty() && cnt[dq[0]%N] + 1 >= A[dq[0]%N])
                    dq.pop_front();

                if (!dq.empty() && !done[i] && dq[0]-i <= K) {
                    int idx = dq[0]%N;
                    cnt[idx]++;
                    endLocOf[idx] = i;
                    done[i] = true;
                }
            }
            else if (A[i] > 1)
                dq.push_front(i);
        }
    };
    f(); // do it once
    for (auto &x : dq) x += N;
    f(); // do it again for wrap-around

    // compute finalPos values
    // some values may overwrite others, so we do this in a specific order

    // first any value that was initially > 1 is set to 1
    for (auto i : nolocs)
        finalPos[i] = 1;
    // any value set to 0 or 1 is just either 0 or 1
    for (auto i = 0; i < N; i++) {
        if (A[i] == 0) finalPos[i] = done[i];
        else if (A[i] == 1) finalPos[i] = 1;
    }
    // any value > 1 is first done by values that ended up becoming 1
    for (auto i = 0; i < N; i++) {
        if (A[i] > 1 && A[i] - cnt[i] == 1)
            finalPos[endLocOf[i]] = A[i] - cnt[i];
    }
    // other values > 1 are set after since they may overwrite them
    for (auto i = 0; i < N; i++) {
        if (A[i] > 1 && A[i] - cnt[i] > 1) {
            int newPos = ((i - K) % N + N) % N;
            finalPos[newPos] = A[i] - cnt[i];
        }
    }

    // output values, note that finalPos is shifted by K
    for (auto i = 0; i < N; i++) {
        int actual = ((i - K) % N + N) % N;
        cout << finalPos[actual] << " \n"[i == N-1];
    }

    return 0;
}