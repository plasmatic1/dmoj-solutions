// ./riddle-troll.yml
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

ostream& operator<<(ostream& out, const pii o) {
    out << "(fs=" << o.fs << ", sn=" << o.sn << ")";
    return out;
}

int pri[256];
string s;

int ptr = 0;

int parseNum() {
    bool n = false;
    if (s[ptr] == '-') {
        n = true;
        ptr++;
    }
    int k = 0;
    while (isdigit(s[ptr])) {
        k = k * 10 + (s[ptr]-'0');
        ptr++;
    }
    return n ? -k : k;
}

int parse() {
    int opt = ptr;
    vector<pair<bool, int>> vs; // type=0->num, type=1->op
    bool num = true;
    while (s[ptr] != ')') {
        if (num) {
            if (s[ptr] == '(') {
                ptr++;
                vs.eb(0, parse());
            }
            else
                vs.eb(0, parseNum());
        }
        else {
            vs.eb(1, s[ptr]);
            ptr++;
        }

        num ^= 1;
    }
    ptr++; // very end, skip the last bracket
    assert(SZ(vs) % 2 == 1);


    int maxPri;
    do {
        maxPri = -1;
        for (auto [tp, c] : vs) {
            if (tp == 1)
                maxa(maxPri, pri[c]);
        }

        if (maxPri != -1) {
            int i = 0;
            while (i+2 < SZ(vs)) {
                if (pri[vs[i+1].sn] < maxPri)
                    i += 2;
                else {
                    int a = vs[i].sn, b = vs[i+2].sn, ret = -1;
                    switch (vs[i+1].sn) {
                        case '+':
                            ret = a+b;
                            break;
                        case '-':
                            ret = a-b;
                            break;
                        case '*':
                            ret = a*b;
                            break;
                        case '/':
                            if (b == 0) {
                                cout << ("attack troll with sword") << '\n';
                                exit(0);
                            }
                            ret = a/b;
                            break;
                        default:
                            assert(0);
                            break;
                    }

                    vs.erase(vs.begin()+i);
                    vs.erase(vs.begin()+i);
                    vs.erase(vs.begin()+i);
                    vs.insert(vs.begin()+i, pii(0, ret));
                }
            }
        }
    } while (maxPri != -1);

    assert(vs[0].fs == 0);
    return vs[0].sn;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int a, b, c, d; cin >> a >> b >> c >> d >> s;
    pri['+'] = a; pri['-'] = b; pri['*'] = c; pri['/'] = d;
    s += ")";

    cout << (parse()) << '\n';

    return 0;
}