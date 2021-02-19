// ./mock-ccc-21-s3-lexicographically-smallest-permutation-subsequence.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;

const int MN = 2e5 + 1;
int N, K,
    A[MN];

pii lst[MN];
vector<int> fst[MN]; int idxOfLst[MN];

int lstptr = 0, fstptr = 0, startIdx = -1;
priority_queue<int> pq;
priority_queue<pii> fpq; // (fst, num) fst IS min, num NO preference 
bool done[MN]; //, doneNum[MN];

void advancefst() {
    while (!fpq.empty() && -fpq.top().first <= lst[lstptr].first) {
        auto c = fpq.top(); fpq.pop();
        pq.push(-c.second);
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K;
    for (int i = 0; i < N; i++) { cin >> A[i]; A[i]--; lst[A[i]] = {i, A[i]}; }
    for (int i = N-1; i >= 0; i--) { fst[A[i]].push_back(i); }
    sort(lst, lst + K);
    lst[K] = {INF, -1};

    // set things up
    for (int i = 0; i < K; i++) {
        idxOfLst[lst[i].second] = i;
        fpq.emplace(-fst[i].back(), i);
    }

    // greedy
    advancefst();
    int doneCnt = 0;
    while (!pq.empty()) {
        int c = -pq.top(); pq.pop();

        while (fst[c].back() < startIdx)
            fst[c].pop_back();
        if (fst[c].back() > lst[lstptr].first) {
            fpq.emplace(-fst[c].back(), c);
            continue;
        }
        
        doneCnt++;
        cout << (c+1) << " \n"[doneCnt == K];
        startIdx = fst[c].back();

        done[idxOfLst[c]] = true;
        while (done[lstptr]) {
            lstptr++;
        }
        advancefst();
    }

    return 0;
}