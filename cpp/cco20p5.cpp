#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

using pii = pair<int, int>;

const int MN = 500001, TREEN = 1048576, TREEM = TREEN * 2 + 10, NO_ANS = 1000010;
int Q;

vector<pii> segs[MN << 2];
void addSegment(int i, int l, int r, int ql, int qr, const pii &seg) {
    if (r < ql || l > qr) return;
    if (l >= ql && r <= qr) return void(segs[i].push_back(seg));
    int mid = (l + r) / 2;
    addSegment(i * 2, l, mid, ql, qr, seg);
    addSegment(i * 2 + 1, mid + 1, r, ql, qr, seg);
}

struct change {
    int qid, idx, val;
};

vector<pair<int, pii>> maxL, minR;
vector<pii> ans0;
int mint[TREEM], maxt[TREEM];
vector<change> mintch, maxtch;

template <typename T> void revVar(vector<pair<int, T>> &dq, int to) {
    while (!dq.empty() && dq.back().first > to)
        dq.pop_back();
}
void revDS(vector<change> &dq, int ds[TREEM], int to) {
    while (!dq.empty() && dq.back().qid > to) {
        ds[dq.back().idx] = dq.back().val;
        dq.pop_back();
    }
}
void undo(int to) {
    revVar(ans0, to); revVar(maxL, to); revVar(minR, to);
    revDS(mintch, mint, to); revDS(maxtch, maxt, to);
}

int query(int seg[TREEM], int L, int R) {
    R++;
    int res = INF;
    for (L += TREEN, R += TREEN; L < R; L >>= 1, R >>= 1) {
        if (L & 1) {
            res = min(res, seg[L]);
            L++;
        }
        if (R & 1) {
            R--;
            res = min(res, seg[R]);
        }
    }
    return res;
}
void update(int seg[TREEM], vector<change> &chs, int cqid, int pos, int x) {
    for (int i = pos + TREEN; i; i >>= 1) {
        if (x < seg[i]) {
            chs.push_back({cqid, i, seg[i]});
            seg[i] = x;
        }
    }
}

bool betterMinR(const pii &a, const pii &b) {
    return a.second == b.second ? a.first > b.first : a.second < b.second;
}
bool betterMaxL(const pii &a, const pii &b) {
    return a.first == b.first ? a.second < b.second : a.first > b.first;
}
string pstr(const pii &p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

int cqid = 1;
void solve(int i, int l, int r) {
    // cout << "solve: i=" << i << ", l=" << l << ", r=" << r << endl;
    // cout << "d: ";
    // for (auto p : segs[i]) {
    //     cout << p.first << ' ' << p.second << ", ";
    // }

    int qid = cqid++;
    for (auto p : segs[i]) {
        if (betterMinR(p, minR.back().second))
            minR.emplace_back(qid, p);
        if (betterMaxL(p, maxL.back().second))
            maxL.emplace_back(qid, p);
        
        int tans = min(query(mint, p.second, 1000000) - p.first, p.second + query(maxt, 1, p.first)); // max tree stores negatives so min==max
        // cout << pstr(p) << ": " << tans << ", q1=" << query(mint, p.second, 1000000) << ", q2=" << query(maxt, 1, p.first) << endl;
        if (tans < ans0.back().second)
            ans0.emplace_back(qid, tans);
        update(mint, mintch, qid, p.first, p.second);
        update(maxt, maxtch, qid, p.second, -p.first);
    }
    
    if (l == r) {
        // cout << "maxL=" << pstr(maxL.back().second) << ", minR=" << pstr(minR.back().second) << ", ans0=" << ans0.back().second << endl;
        if (ans0.back().second == NO_ANS)
            cout << (maxL.back().second.second - minR.back().second.first) << '\n';
        else
            cout << ans0.back().second << '\n';
        undo(qid - 1);
        return;
    }
    int mid = (l + r) / 2;
    solve(i * 2, l, mid);
    solve(i * 2 + 1, mid + 1, r);

    undo(qid - 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> Q;

    // build segments
    map<pii, int> cnt, init;
    for (int i = 1; i <= Q; ++i) {
        char T;
        int l, r;
        cin >> T >> l >> r;

        auto p = make_pair(l, r);
        if (T == 'A') {
            if (!cnt[p])
                init[p] = i;
            cnt[p]++;
        }
        else {
            if (cnt[p] == 1) {
                addSegment(1, 1, Q, init[p], i - 1, p);
            }
            cnt[p]--;
        }
    }
    for (auto &pp : cnt) {
        if (pp.second > 0) {
            addSegment(1, 1, Q, init[pp.first], Q, pp.first);
        }
    }

    // solve
    ans0.emplace_back(0, NO_ANS);
    maxL.emplace_back(0, make_pair(-INF, -INF));
    minR.emplace_back(0, make_pair(INF, INF));
    fill(mint, mint + TREEM, INF);
    fill(maxt, maxt + TREEM, INF);
    solve(1, 1, Q);

    return 0;
}