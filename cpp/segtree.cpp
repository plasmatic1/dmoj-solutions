// https://wcipeg.com/problem/segtree

#include <bits/stdc++.h>
using namespace std;

struct SparseSeg {
    // Seg Parameters
    using Data = int; // Data type
    static inline Data Merge(Data a, Data b) { return min(a, b); } // Merge function
    static const Data DEFAULT = 0x3f3f3f3f; // Default value (used in query func)

    struct SegNode {
        SegNode *l, *r;
        Data value;

        SegNode() : l(nullptr), r(nullptr), value(0) {}
        ~SegNode() {
            delete l;
            delete r;
            l = r = nullptr;
        }

        Data update(SegNode *&rt, int l, int r, int q, Data v) {
            if (!rt) rt = new SegNode;
            if (l == q && r == q) return rt->value = v;
            if (l > q || r < q) return rt->value;
            int mid = (l + r) >> 1;
            return rt->value = Merge(update(rt->l, l, mid, q, v), update(rt->r, mid + 1, r, q, v));
        }

        Data query(SegNode *&rt, int l, int r, int ql, int qr) {
            if (!rt) return DEFAULT;
            if (l >= ql && r <= qr) return rt->value;
            if (l > qr || r < ql) return DEFAULT;
            int mid = (l + r) >> 1;
            return Merge(query(rt->l, l, mid, ql, qr), query(rt->r, mid + 1, r, ql, qr));
        }
    };

    // Just Some Driver Code
    int N;
    SegNode *root;

    inline void init(int N0) { N = N0; root = nullptr; } // Initializes the DS
    inline void reset() { delete root; root = nullptr; } // Resets the DS
    inline void update(int q, Data v) { root->update(root, 1, N, q, v); }
    inline Data query(int l, int r) { return root->query(root, 1, N, l, r); }
};

int N, Q;
SparseSeg seg;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;
    seg.init(N);

    for (int i = 1; i <= N; i++) {
        int X; cin >> X;
        seg.update(i, X);
    }

    while (Q--) {
        char T; int A; int B;
        cin >> T >> A >> B;

        if (T == 'Q') {
            A++; B++;
            cout << seg.query(A, B) << '\n';
        }
        else {
            A++;
            seg.update(A, B);
        }
    }

    return 0;
}
