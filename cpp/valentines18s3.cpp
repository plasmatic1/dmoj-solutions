#pragma region
#include <bits/stdc++.h>
using namespace std;
// Common Type shorteners and int128
using ll = long long; using ull = unsigned long long; using ld = long double;
using pii = pair<int, int>; using pll = pair<ll, ll>;
template <typename T> using vec = vector<T>;
template <typename K, typename V> using umap = unordered_map<K, V>; template <typename K> using uset = unordered_set<K>;
using vi = vec<int>; using vl = vec<ll>; using vpi = vec<pii>; using vpl = vec<pll>;
#ifdef __SIZEOF_INT128__
using int128 = __int128_t; using uint128 = __uint128_t;
#endif
template<typename I> string intStr(I x) { string ret; while (x > 0) { ret += (x % 10) + '0'; x /= 10; } reverse(ret.begin(), ret.end()); return ret; } // Int to string
// Shorthand Macros
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
#define mpr make_pair
#define pb push_back
#define popcount __builtin_popcount
#define clz __builtin_clz
#define ctz __builtin_ctz
// Shorthand Function Macros
#define sz(x) ((int)((x).size()))
#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for (__typeof(a) i = a; i < b; i++)
#define reprev(i, a, b) for (__typeof(a) i = a; i > b; i--)
#define repi(a, b) rep(i, a, b)
#define repj(a, b) rep(j, a, b)
#define repk(a, b) rep(k, a, b)
#define Cmplt(type) bool operator<(const type &o) const
#define Cmpgt(type) bool operator>(const type &o) const
#define Cmpfn(name, type) bool name(const type &a, const type &b)
#define Inop(type) istream& operator>>(istream& in, type &o)
#define Outop(type) ostream& operator<<(ostream& out, type o)
#define Pow2(x) (1LL << (x))
#define scn(type, ...) type __VA_ARGS__; scan(__VA_ARGS__) // scn -> Short for SCan New
// Shorthand Functions
template<typename T> inline void maxa(T& st, T v) { st = max(st, v); }
template<typename T> inline void mina(T& st, T v) { st = min(st, v); }
inline void setprec(ostream& out, int prec) { out << setprecision(prec) << fixed; }
// Out operators and printing for arrays and vectors
template <typename T> ostream& operator<<(ostream& out,vector<T> iter){out<<"[";for(auto t:iter){out<<t<<", ";}out<<"]";return out;}
template <typename T> string arrayStr(T *arr,int sz){string ret = "[";for(int i=0;i<sz;i++){ret+=to_string(arr[i])+", "; } return ret + "]";}
template <typename T> void printArray(T *arr,int sz){for(int i=0;i<sz;i++){cout<<arr[i]<<" "; } cout<<"\n";}
// I/O Operations
inline void scan(){}
template<typename F, typename... R> inline void scan(F &f,R&... r){cin>>f;scan(r...);}
template <typename F> inline void println(F t){cout<<t<<'\n';}
template<typename F, typename... R> inline void println(F f,R... r){cout<<f<<" ";println(r...);}
inline void print(){}
template<typename F, typename... R> inline void print(F f,R... r){cout<<f;print(r...);}
// Debugging
#define db(x) cout << (#x) << ": " << x << ", "
#define dblb(s) cout << "[" << s << "] "
#define dbbin(x, n) cout << (#x) << ": " << bitset<n>(x) << ", "
#define dbarr(x, n) cout << (#x) << ": " << arrayStr((x), (n)) << ", "
#define dbln cout << endl;
#pragma endregion

/*
STATE:

dp[i][j][k][l]
i -> current number
j -> longest increasing subarray len
k -> last number used
l -> current increasing subarray len


-=[ Transition to DP[i][j][k][l] ]=-

If j == 1, ALL dp[i - 1][j][k..N][1..j]
Else, ALL {
	If l == j, ALL dp[i - 1][j - 1][1..(k - 1)][l - 1]
	Else, ALL dp[i - 1][j][1..(k - 1)][l - 1]
}

*/

const int MN = 101, MOD = 1e9 + 7;
int N, K,
	dp[2][MN][MN][MN], pfx[MN][MN][MN];

ll fixMod(ll &x) { return x = ((x % MOD) + MOD) % MOD; }

inline int rsq(int i, int j0, int j1, int k0, int k1) {
	ll x = (ll)pfx[i][j1][k1] - pfx[i][j0 - 1][k1] - pfx[i][j1][k0 - 1] + pfx[i][j0 - 1][k0 - 1];
	return fixMod(x);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	scan(N, K);

	dp[0][1][1][1] = 1;
	repi(2, N + 1) {
		int pre = i & 1, cur = pre ^ 1;

		// pfx sum
		repj(1, K + 1) {
			repk(1, i + 1) {
				rep(l, 1, j + 1) {
					ll v = (ll)pfx[j][k - 1][l] + pfx[j][k][l - 1] - pfx[j][k - 1][l - 1] + dp[pre][j][k][l];
					pfx[j][k][l] = fixMod(v);
				}
			}
		}

		// do dp
		repj(1, K + 1) {
			repk(1, i + 1) {
				rep(l, 1, j + 1) {
					ll x = 0;
					if (l == 1)  // reset back to 1
						x += rsq(j, k, i, 1, j);
					else { // continue
						if (l == j)
							x += rsq(j - 1, 1, k - 1, l - 1, l - 1);
						x += rsq(j, 1, k - 1, l - 1, l - 1);
					}

					dp[cur][j][k][l] = fixMod(x);
					// db(i), db(j), db(k), db(l), db(x), dbln;
				}
			}
		}
	}

	// sum answer
	int cur = (N & 1) ^ 1;
	ll tot = 0;
	repi(1, N + 1)
		repj(1, K + 1)
			tot += dp[cur][K][i][j];
	println(tot % MOD);

	return 0;
}

//❤️