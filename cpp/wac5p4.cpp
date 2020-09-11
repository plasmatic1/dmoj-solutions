#pragma GCC optimize "Ofast"
#pragma GCC optimize "unroll-loops"
#pragma GCC target "sse,sse2,sse3,sse4,abm,avx,mmx,popcnt"
// ./wesleys-anger-contest-5-problem-4.yml
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

const int MN = 2e5 + 1, LG = 20;
int N, Q;
vector<int> g[MN];

int firstinstances[MN], dep[MN], tb[LG][MN];
ll dept[MN];

int sptable[LG][MN * 2 + 1], path_size = 1; // The base 2 log of 100000 (Max size) is ~16.609, I used 18 to be safe
#define PUSH_EDGE(x) sptable[0][path_size++] = x

inline int dep_min(int a, int b){
	return dep[a] < dep[b] ? a : b;
}

void buildsptable(){ // Builds sparse table `sptable` from array `arr`
	// First row is same as the array

	for (int i = 1; i < LG; ++i) {
		int gap = 1 << (i - 1), maxv = path_size - (1 << i) + 1;

		for (int j = 1; j <= maxv; ++j) {
			sptable[i][j] = dep_min(sptable[i - 1][j],
					sptable[i - 1][j + gap]);
		}
	}
}

int lca(int a, int b){ // Querys the range from `a` to `b`
	// Change to RMQ Indxes
	a = firstinstances[a];
	b = firstinstances[b];

	if(a >= b){
		swap(a, b);
	}

	// Find max bit
	int delta = b - a, maxbit = 1, // Max bit begins at 1 to account for `b - maxbit + 1` when `a == b`
			maxbitind = 0; // Row of the sparse table to use

	for (int i = LG; i >= 0; --i) {
		int v = 1 << i;

		if(delta & v){
			maxbit = v;
			maxbitind = i;
			break;
		}
	}

	// Return Range
	return dep_min(sptable[maxbitind][a],
			sptable[maxbitind][b - maxbit + 1]);
}

//build path

void dfs(int curr, int lvl, ll dis, int parent){
	PUSH_EDGE(curr);
	dep[curr] = lvl;
	dept[curr] = dis;
    tb[0][curr] = parent;

	for(auto adj : g[curr]){
		if(adj != parent){
			dfs(adj, lvl + 1, dis + 1, curr);
			PUSH_EDGE(curr);
		}
	}
}

void build(){
	dfs(1, 0, 0, -1);

	for (int i = 1; i <= path_size; ++i) {
		if(!firstinstances[sptable[0][i]]){
			firstinstances[sptable[0][i]] = i;
		}
	}

	buildsptable();
}

int qdis(int a, int b) {
    return dep[a] + dep[b] - 2 * dep[lca(a, b)];
}

int kthParent(int n, int k) {
    for (auto i = 0; i < LG; i++)
        if ((k >> i) & 1)
            n = tb[i][n];
    return n;
}

int kth(int a, int b, int k) {
    // k--;
    int lcav = lca(a, b);
    if (k <= dep[a] - dep[lcav]) return kthParent(a, k);
    return kthParent(b, (dep[b] - dep[lcav]) - (k - (dep[a] - dep[lcav])));
}

int F(int a, int b, int c, int d, int mid) {
    return qdis(kth(a, b, mid), kth(c, d, mid));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (Q);

    for (auto i = 1; i < N; i++) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }

    dfs(1, 0, 0, -1);
    build();
    for (auto i = 1; i < LG; i++) {
        for (auto j = 1; j <= N; j++) {
            int pp = tb[i - 1][j];
            tb[i][j] = pp == -1 ? -1 : tb[i - 1][pp];
        }
    }

    while (Q--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        if (a == c) {
            cout << (0) << '\n';
            continue;
        }

        int l = 1, r = min(qdis(a, b), qdis(c, d));
        while (l + 1 < r) {
            int mid = (l + r) / 2;
            if (F(a, b, c, d, mid - 1) > F(a, b, c, d, mid))
                l = mid;
            else
                r = mid;
        }

        int e1 = kth(a, b, l), e2 = kth(c, d, l);
        if (e1 != e2 || e1 == b || e1 == d)
            cout << (-1) << '\n';
        else
            cout << (l) << '\n';
    }

    return 0;
}